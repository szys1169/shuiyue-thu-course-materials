# Codex API 切换工具：Mac 版

> 作者：水至月生  
> 适用系统：macOS  
> 更新日期：2026 年 8 月 30 日

这个文件夹中只有一个真正需要运行的文件：

```text
switch-codex-mac.sh
```

第一次使用时，先按 `Command + Q` 完全退出 ChatGPT/Codex。之后打开“终端”，输入 `bash` 和一个空格，再把脚本从 Finder 拖进终端窗口，按回车即可。

完整说明见脚本旁边的《macOS 补充说明：零基础的 Codex 下载和使用攻略》。如果你只拿到了这个文件夹，也可以运行：

```bash
bash switch-codex-mac.sh
```

菜单中的三个选项分别是 DeepSeek 官方、并行智算云和 Codex 原版。每次切换前，工具都会备份 `~/.codex/config.toml`。

API Key 会保存在：

```text
~/.codex/codex-switch-keys
```

脚本会限制该目录的读取权限，但仍然不要把 `.codex` 文件夹发给别人或上传到公开仓库。
