#!/bin/bash

# Codex API 后端切换工具（macOS）
# 支持：DeepSeek 官方 / 并行智算云 / Codex 原版

set -u

CODEX_SWITCH_HOME="${CODEX_HOME:-$HOME/.codex}"
CONFIG_PATH="$CODEX_SWITCH_HOME/config.toml"
KEY_DIR="$CODEX_SWITCH_HOME/codex-switch-keys"
BACKUP_DIR="$CODEX_SWITCH_HOME/backup-switch"

DEEPSEEK_NAME="DeepSeek 官方"
DEEPSEEK_BASE_URL="https://api.deepseek.com/"
DEEPSEEK_KEY_NAME="DEEPSEEK_API_KEY"
DEEPSEEK_MODEL_1="deepseek-v4-flash"
DEEPSEEK_MODEL_2="deepseek-v4-pro"

PARATERA_NAME="并行智算云 (llmapi.paratera.com)"
PARATERA_BASE_URL="https://llmapi.paratera.com/v1"
PARATERA_KEY_NAME="PARATERA_API_KEY"
PARATERA_MODEL_1="DeepSeek-V4-Flash"
PARATERA_MODEL_2="DeepSeek-V4-Pro"

say_ok() {
    printf '[OK] %s\n' "$1"
}

say_warn() {
    printf '[提示] %s\n' "$1"
}

die() {
    printf '[错误] %s\n' "$1" >&2
    exit 1
}

ensure_dirs() {
    mkdir -p "$CODEX_SWITCH_HOME" "$KEY_DIR" "$BACKUP_DIR" || die "无法创建 $CODEX_SWITCH_HOME"
    chmod 700 "$KEY_DIR" "$BACKUP_DIR" 2>/dev/null || true
}

toml_quote() {
    printf '%s' "$1" | sed 's/\\/\\\\/g; s/"/\\"/g'
}

key_path_for() {
    printf '%s/%s' "$KEY_DIR" "$1"
}

has_saved_key() {
    local key_path
    key_path="$(key_path_for "$1")"
    [ -s "$key_path" ]
}

save_key() {
    local key_name="$1"
    local key_value="$2"
    local key_path
    key_path="$(key_path_for "$key_name")"
    umask 077
    printf '%s' "$key_value" > "$key_path" || die "API Key 保存失败"
    chmod 600 "$key_path" 2>/dev/null || true
    say_ok "$key_name 已保存在本机，下次可以直接复用"
}

read_new_key() {
    local key_name="$1"
    local key_value
    printf '请输入 %s（输入时不会显示）: ' "$key_name" >&2
    IFS= read -r -s key_value
    printf '\n' >&2
    [ -n "$key_value" ] || return 1
    save_key "$key_name" "$key_value"
}

choose_key() {
    local key_name="$1"
    local choice
    if has_saved_key "$key_name"; then
        printf '\nAPI Key 使用方式:\n'
        printf ' 1) 使用上次保存的 Key\n'
        printf ' 2) 重新输入\n'
        printf '请选择 (1/2): '
        IFS= read -r choice
        case "$choice" in
            1) return 0 ;;
            2) read_new_key "$key_name" ; return $? ;;
            *) say_warn "输入无效，已取消"; return 1 ;;
        esac
    fi

    say_warn "没有找到保存的 $key_name"
    read_new_key "$key_name"
}

backup_config() {
    local stamp dest
    [ -f "$CONFIG_PATH" ] || return 0
    stamp="$(date '+%Y%m%d-%H%M%S')"
    dest="$BACKUP_DIR/config-$stamp-pre-switch.toml"
    cp "$CONFIG_PATH" "$dest" || die "配置备份失败"
    chmod 600 "$dest" 2>/dev/null || true
    printf '%s' "$dest"
}

clean_config() {
    local source_path="$1"
    local output_path="$2"

    awk '
    BEGIN { in_section = 0; skip_provider = 0 }
    {
        line = $0

        if (line ~ /^[[:space:]]*\[model_providers\.(deepseek|paratera)(\.auth)?\][[:space:]]*$/) {
            skip_provider = 1
            next
        }

        if (skip_provider && line ~ /^[[:space:]]*\[/) {
            skip_provider = 0
        }

        if (skip_provider) {
            next
        }

        if (line ~ /^[[:space:]]*\[/) {
            in_section = 1
        }

        if (!in_section && line ~ /^[[:space:]]*(model|model_provider|model_reasoning_effort|service_tier|forced_login_method|preferred_auth_method|model_catalog_json)[[:space:]]*=/) {
            next
        }

        print line
    }
    ' "$source_path" > "$output_path" || die "读取原配置失败"
}

write_config() {
    local backend="$1"
    local model="${2:-}"
    local tmp_source tmp_clean tmp_final backup key_name key_path quoted_key_path

    ensure_dirs
    tmp_source="$(mktemp "${TMPDIR:-/tmp}/codex-switch-source.XXXXXX")" || die "无法创建临时文件"
    tmp_clean="$(mktemp "${TMPDIR:-/tmp}/codex-switch-clean.XXXXXX")" || die "无法创建临时文件"
    tmp_final="$(mktemp "${TMPDIR:-/tmp}/codex-switch-final.XXXXXX")" || die "无法创建临时文件"
    trap 'rm -f "$tmp_source" "$tmp_clean" "$tmp_final"' EXIT

    if [ -f "$CONFIG_PATH" ]; then
        cp "$CONFIG_PATH" "$tmp_source" || die "无法读取 $CONFIG_PATH"
    else
        : > "$tmp_source"
    fi

    backup="$(backup_config)"
    clean_config "$tmp_source" "$tmp_clean"

    if [ "$backend" = "openai" ]; then
        {
            printf 'model = "gpt-5.6-sol"\n'
            printf 'model_reasoning_effort = "medium"\n'
            printf 'service_tier = "default"\n\n'
            cat "$tmp_clean"
        } > "$tmp_final"
    else
        if [ "$backend" = "deepseek" ]; then
            key_name="$DEEPSEEK_KEY_NAME"
            provider_name="$DEEPSEEK_NAME"
            base_url="$DEEPSEEK_BASE_URL"
        else
            key_name="$PARATERA_KEY_NAME"
            provider_name="$PARATERA_NAME"
            base_url="$PARATERA_BASE_URL"
        fi

        key_path="$(key_path_for "$key_name")"
        quoted_key_path="$(toml_quote "$key_path")"

        {
            printf 'model = "%s"\n' "$(toml_quote "$model")"
            printf 'model_provider = "%s"\n' "$backend"
            printf 'model_reasoning_effort = "high"\n'
            printf 'forced_login_method = "api"\n\n'
            cat "$tmp_clean"
            printf '\n[model_providers.%s]\n' "$backend"
            printf 'name = "%s"\n' "$(toml_quote "$provider_name")"
            printf 'base_url = "%s"\n' "$(toml_quote "$base_url")"
            printf 'wire_api = "responses"\n\n'
            printf '[model_providers.%s.auth]\n' "$backend"
            printf 'command = "/bin/cat"\n'
            printf 'args = ["%s"]\n' "$quoted_key_path"
        } > "$tmp_final"
    fi

    umask 077
    cp "$tmp_final" "$CONFIG_PATH" || die "写入 $CONFIG_PATH 失败"
    chmod 600 "$CONFIG_PATH" 2>/dev/null || true

    if [ "$backend" = "openai" ]; then
        say_ok "已切换到 Codex 原版 (gpt-5.6-sol)"
    else
        say_ok "已切换到 $provider_name，模型 = $model"
    fi
    [ -n "$backup" ] && printf '     切换前配置已备份: %s\n' "$backup"
    printf '     请按 Command + Q 完全退出 ChatGPT/Codex，再重新打开。\n'

    rm -f "$tmp_source" "$tmp_clean" "$tmp_final"
    trap - EXIT
}

choose_model() {
    local backend="$1"
    local model_1 model_2 provider_name choice
    if [ "$backend" = "deepseek" ]; then
        model_1="$DEEPSEEK_MODEL_1"
        model_2="$DEEPSEEK_MODEL_2"
        provider_name="$DEEPSEEK_NAME"
    else
        model_1="$PARATERA_MODEL_1"
        model_2="$PARATERA_MODEL_2"
        provider_name="$PARATERA_NAME"
    fi

    printf '\n请选择模型（%s）:\n' "$provider_name" >&2
    printf ' 1) %s\n' "$model_1" >&2
    printf ' 2) %s\n' "$model_2" >&2
    printf '请选择 (1/2): ' >&2
    IFS= read -r choice
    case "$choice" in
        1) printf '%s' "$model_1" ;;
        2) printf '%s' "$model_2" ;;
        *) return 1 ;;
    esac
}

show_status() {
    local model provider active
    if [ ! -f "$CONFIG_PATH" ]; then
        printf '当前没有 %s\n' "$CONFIG_PATH"
        return
    fi

    model="$(sed -n 's/^[[:space:]]*model[[:space:]]*=[[:space:]]*"\([^"]*\)".*/\1/p' "$CONFIG_PATH" | head -n 1)"
    provider="$(sed -n 's/^[[:space:]]*model_provider[[:space:]]*=[[:space:]]*"\([^"]*\)".*/\1/p' "$CONFIG_PATH" | head -n 1)"

    case "$provider" in
        deepseek) active="$DEEPSEEK_NAME" ;;
        paratera) active="$PARATERA_NAME" ;;
        "") active="Codex 原版" ;;
        *) active="自定义 ($provider)" ;;
    esac

    printf '当前配置: %s\n' "$active"
    printf 'model: %s\n' "${model:-未设置}"
    printf '配置文件: %s\n' "$CONFIG_PATH"
}

list_models() {
    local backend="$1"
    local base_url key_name key_path
    case "$backend" in
        deepseek)
            base_url="$DEEPSEEK_BASE_URL"
            key_name="$DEEPSEEK_KEY_NAME"
            ;;
        paratera)
            base_url="$PARATERA_BASE_URL"
            key_name="$PARATERA_KEY_NAME"
            ;;
        *) die "list-models 只支持 deepseek 或 paratera" ;;
    esac

    key_path="$(key_path_for "$key_name")"
    [ -s "$key_path" ] || die "没有保存 $key_name，请先运行 setkey"
    command -v curl >/dev/null 2>&1 || die "系统中没有找到 curl"

    curl -fsS "${base_url%/}/models" \
        -H "Authorization: Bearer $(cat "$key_path")" \
        -H 'Accept: application/json' || die "模型列表查询失败"
    printf '\n'
}

start_menu() {
    local choice backend model key_name
    while true; do
        printf '\n========== Codex 后端切换（Mac）==========\n'
        show_status
        printf '\n'
        printf ' 1) DeepSeek 官方\n'
        printf ' 2) 并行智算云 (llmapi.paratera.com)\n'
        printf ' 3) Codex 原版\n'
        printf ' 0) 退出\n'
        printf '请选择 (1/2/3/0): '
        IFS= read -r choice

        case "$choice" in
            0) printf '已退出\n'; break ;;
            1) backend="deepseek"; key_name="$DEEPSEEK_KEY_NAME" ;;
            2) backend="paratera"; key_name="$PARATERA_KEY_NAME" ;;
            3) write_config "openai" ""; continue ;;
            *) say_warn "输入无效，请重新输入"; continue ;;
        esac

        model="$(choose_model "$backend")" || {
            say_warn "输入无效，已取消"
            continue
        }
        choose_key "$key_name" || continue
        write_config "$backend" "$model"
    done
}

show_help() {
    cat <<'EOF'
用法:
  bash switch-codex-mac.sh start
  bash switch-codex-mac.sh status
  bash switch-codex-mac.sh setkey <deepseek|paratera>
  bash switch-codex-mac.sh list-models <deepseek|paratera>

不带参数时会直接进入交互菜单。
EOF
}

main() {
    local action="${1:-start}"
    local backend="${2:-}"

    [ "$(id -u)" -ne 0 ] || die "请不要使用 sudo 运行本工具"
    if [ "$(uname -s)" != "Darwin" ]; then
        say_warn "当前系统不是 macOS；本工具按 macOS 环境编写"
    fi
    ensure_dirs

    case "$action" in
        start) start_menu ;;
        status) show_status ;;
        setkey)
            case "$backend" in
                deepseek) read_new_key "$DEEPSEEK_KEY_NAME" ;;
                paratera) read_new_key "$PARATERA_KEY_NAME" ;;
                *) show_help; die "setkey 需要指定 deepseek 或 paratera" ;;
            esac
            ;;
        list-models) list_models "${backend:-paratera}" ;;
        help|-h|--help) show_help ;;
        *) show_help; die "未知命令: $action" ;;
    esac
}

main "$@"
