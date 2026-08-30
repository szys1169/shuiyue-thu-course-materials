#requires -Version 5.1
<#
.SYNOPSIS
    Codex 后端交互式切换：DeepSeek 官方 / 并行智算云 (llmapi.paratera.com) / Codex 原版

.DESCRIPTION
    运行 start 后按菜单提示输入数字即可完成切换：先选后端（1/2/3），再选模型
    （1=Flash / 2=Pro），最后选择使用上次保存的 API Key 还是重新输入。
    每次切换前自动备份 config.toml。

.EXAMPLE
    .\switch-codex.ps1 start
    .\switch-codex.ps1 status
    .\switch-codex.ps1 list-models paratera
    .\switch-codex.ps1 setkey deepseek
#>
[CmdletBinding()]
param(
    [Parameter(Position = 0)]
    [string]$Action = 'start',

    [Parameter(Position = 1)]
    [string]$Arg2,

    [Parameter(Position = 2)]
    [string]$Arg3
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# ==================== 路径 ====================
$CodexHome = if ($env:CODEX_HOME) { $env:CODEX_HOME } else { Join-Path $HOME '.codex' }
$ConfigPath = Join-Path $CodexHome 'config.toml'
$KeyStorePath = Join-Path $CodexHome '.codex-switch-keys.json'
$CatalogTemplate = Join-Path $CodexHome 'models.json'
$BackupDir = Join-Path $CodexHome 'backup-switch'

# ==================== 后端定义 ====================
# 模型 ID 以平台实际为准；若切换后报模型不存在，可运行 list-models 查询后改这里
$Backends = @{
    'deepseek' = @{
        name     = 'DeepSeek 官方'
        provider = 'deepseek'
        base_url = 'https://api.deepseek.com/'
        key_env  = 'DEEPSEEK_API_KEY'
        models   = @{ '1' = 'deepseek-v4-flash'; '2' = 'deepseek-v4-pro' }
    }
    'paratera' = @{
        name     = '并行智算云 (llmapi.paratera.com)'
        provider = 'paratera'
        base_url = 'https://llmapi.paratera.com/v1'
        key_env  = 'PARATERA_API_KEY'
        models   = @{ '1' = 'DeepSeek-V4-Flash'; '2' = 'DeepSeek-V4-Pro' }
    }
    'openai' = @{
        name     = 'Codex 原版'
        provider = 'openai'
        base_url = ''
        key_env  = ''
        models   = @{}
    }
}

# ==================== 密钥存储 ====================
$KeyStore = @{}
if (Test-Path $KeyStorePath) {
    try {
        $obj = Get-Content $KeyStorePath -Raw -Encoding UTF8 | ConvertFrom-Json
        if ($obj) {
            foreach ($prop in $obj.PSObject.Properties) { $KeyStore[$prop.Name] = [string]$prop.Value }
        }
    } catch {
        $KeyStore = @{}
    }
}

function Save-KeyStore {
    $dir = Split-Path $KeyStorePath -Parent
    if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    $json = $KeyStore | ConvertTo-Json
    [System.IO.File]::WriteAllText($KeyStorePath, $json, (New-Object System.Text.UTF8Encoding($false)))
    try {
        & icacls.exe $KeyStorePath /inheritance:r /grant:r ("{0}:F" -f $env:USERNAME) 2>$null | Out-Null
    } catch {
        # ACL 设置失败不阻塞主流程
    }
}

function Get-StoredKey {
    param([string]$EnvName)
    if (-not $EnvName) { return '' }
    if ($KeyStore.ContainsKey($EnvName) -and $KeyStore[$EnvName]) { return [string]$KeyStore[$EnvName] }
    $userVal = [Environment]::GetEnvironmentVariable($EnvName, 'User')
    if ($userVal) { return $userVal }
    $procVal = [Environment]::GetEnvironmentVariable($EnvName)
    if ($procVal) { return $procVal }
    return ''
}

function Read-KeyInteractive {
    param([string]$Prompt)
    $sec = Read-Host -Prompt $Prompt -AsSecureString
    if ($null -eq $sec -or $sec.Length -eq 0) { return '' }
    $bstr = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($sec)
    try {
        return [System.Runtime.InteropServices.Marshal]::PtrToStringBSTR($bstr)
    } finally {
        [System.Runtime.InteropServices.Marshal]::ZeroFreeBSTR($bstr)
    }
}

function Save-Key {
    param([string]$EnvName, [string]$KeyValue)
    $KeyStore[$EnvName] = $KeyValue
    Save-KeyStore
    try { [Environment]::SetEnvironmentVariable($EnvName, $KeyValue, 'User') } catch { }
    Write-Host "[OK] $EnvName 已保存（下次可选项 1 直接使用）"
}

# ==================== TOML 编辑工具 ====================
function Format-TomlString {
    param([string]$Value)
    $v = $Value.Replace('\', '\\').Replace('"', '\"')
    return '"' + $v + '"'
}

function Read-Lines {
    param([string]$Path)
    if (Test-Path $Path) { return ,@(Get-Content $Path -Encoding UTF8) }
    return ,@()
}

function Write-Config {
    param([string[]]$Lines)
    $text = ($Lines -join [Environment]::NewLine) + [Environment]::NewLine
    [System.IO.File]::WriteAllText($ConfigPath, $text, (New-Object System.Text.UTF8Encoding($false)))
}

function Set-TopLevelKey {
    param([string[]]$Lines, [string]$Key, [string]$Value)
    $pattern = '^\s*' + [regex]::Escape($Key) + '\s*='
    $replaced = $false
    $list = New-Object System.Collections.Generic.List[string]
    foreach ($line in $Lines) {
        if ($line -match $pattern) {
            if (-not $replaced) {
                $list.Add(('{0} = {1}' -f $Key, (Format-TomlString $Value)))
                $replaced = $true
            }
            continue
        }
        $list.Add($line)
    }
    if (-not $replaced) {
        $list.Insert(0, ('{0} = {1}' -f $Key, (Format-TomlString $Value)))
    }
    return ,$list.ToArray()
}

function Remove-TopLevelKey {
    param([string[]]$Lines, [string]$Key)
    $pattern = '^\s*' + [regex]::Escape($Key) + '\s*='
    $out = @($Lines | Where-Object { $_ -notmatch $pattern })
    return ,$out
}

function Remove-ProviderSection {
    param([string[]]$Lines, [string]$ProviderName)
    $header = '^\s*\[' + [regex]::Escape('model_providers.' + $ProviderName) + '\]\s*$'
    $inSection = $false
    $list = New-Object System.Collections.Generic.List[string]
    foreach ($line in $Lines) {
        if ($line -match $header) { $inSection = $true; continue }
        if ($inSection) {
            if ($line -match '^\s*\[') { $inSection = $false }
            else { continue }
        }
        $list.Add($line)
    }
    return ,$list.ToArray()
}

function Remove-EmptyProvidersHeader {
    param([string[]]$Lines)
    $hasEntry = $false
    foreach ($line in $Lines) {
        if ($line -match '^\s*\[model_providers\.') { $hasEntry = $true; break }
    }
    if (-not $hasEntry) {
        $out = @($Lines | Where-Object { $_ -notmatch '^\s*\[model_providers\]\s*$' })
        return ,$out
    }
    return ,$Lines
}

function New-ProviderSection {
    param(
        [string]$ProviderName,
        [string]$DisplayName,
        [string]$BaseUrl,
        [string]$WireApi,
        [string]$Token
    )
    $sb = New-Object System.Text.StringBuilder
    [void]$sb.AppendLine(('[model_providers.{0}]' -f $ProviderName))
    [void]$sb.AppendLine(('name = {0}' -f (Format-TomlString $DisplayName)))
    [void]$sb.AppendLine(('base_url = {0}' -f (Format-TomlString $BaseUrl)))
    [void]$sb.AppendLine(('wire_api = {0}' -f (Format-TomlString $WireApi)))
    [void]$sb.AppendLine(('experimental_bearer_token = {0}' -f (Format-TomlString $Token)))
    return $sb.ToString().TrimEnd()
}

function New-ModelCatalog {
    param([string]$ModelId, [string]$DestPath)
    if (-not (Test-Path $CatalogTemplate)) { return '' }
    try {
        $cat = Get-Content $CatalogTemplate -Raw -Encoding UTF8 | ConvertFrom-Json
        $models = @($cat.models)
        if ($models.Count -eq 0) { return '' }
        $model = $models[0]
        $model.slug = $ModelId
        $model.display_name = $ModelId
        $cat.models = @($model)
        $json = $cat | ConvertTo-Json -Depth 100
        [System.IO.File]::WriteAllText($DestPath, $json, (New-Object System.Text.UTF8Encoding($false)))
        return $DestPath
    } catch {
        return ''
    }
}

# ==================== 备份 ====================
function Backup-Config {
    param([string]$Label)
    if (-not (Test-Path $ConfigPath)) { return '' }
    if (-not (Test-Path $BackupDir)) { New-Item -ItemType Directory -Force -Path $BackupDir | Out-Null }
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $safeLabel = $Label -replace '[^\w\-]', ''
    $dest = Join-Path $BackupDir ("config-{0}-{1}.toml" -f $stamp, $safeLabel)
    Copy-Item $ConfigPath $dest -Force
    return $dest
}

# ==================== 执行切换 ====================
function Apply-Switch {
    param(
        [string]$BackendKey,   # deepseek / paratera / openai
        [string]$Model,
        [string]$Token
    )
    $p = $Backends[$BackendKey]
    $backup = Backup-Config 'pre-switch'
    $lines = Read-Lines $ConfigPath

    # 拆成“顶部键区”和“区块区”，避免新键误入某个 table
    $firstSection = -1
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match '^\s*\[') { $firstSection = $i; break }
    }
    $header = @()
    $body = @()
    if ($firstSection -lt 0) {
        $header = @($lines)
    } elseif ($firstSection -eq 0) {
        $body = @($lines)
    } else {
        $header = @($lines[0..($firstSection - 1)])
        $body = @($lines[$firstSection..($lines.Count - 1)])
    }

    # 先清理旧的第三方 provider 段落
    $body = Remove-ProviderSection $body 'deepseek'
    $body = Remove-ProviderSection $body 'paratera'
    $body = Remove-EmptyProvidersHeader $body

    if ($BackendKey -eq 'openai') {
        # 恢复 Codex 原版
        $header = Set-TopLevelKey $header 'model' 'gpt-5.6-sol'
        $header = Set-TopLevelKey $header 'model_reasoning_effort' 'medium'
        $header = Set-TopLevelKey $header 'service_tier' 'default'
        foreach ($k in @('model_provider', 'preferred_auth_method', 'forced_login_method', 'model_catalog_json')) {
            $header = Remove-TopLevelKey $header $k
        }
        Write-Host '[OK] 已切换到 Codex 原版 (gpt-5.6-sol)'
    } else {
        $header = Set-TopLevelKey $header 'model' $Model
        $header = Set-TopLevelKey $header 'model_reasoning_effort' 'high'
        $header = Set-TopLevelKey $header 'model_provider' $p.provider
        $header = Set-TopLevelKey $header 'preferred_auth_method' 'apikey'
        $header = Set-TopLevelKey $header 'forced_login_method' 'api'
        $header = Remove-TopLevelKey $header 'service_tier'

        $catalog = New-ModelCatalog $Model (Join-Path $CodexHome ("models-{0}.json" -f $p.provider))
        if ($catalog) { $header = Set-TopLevelKey $header 'model_catalog_json' $catalog }
        else { $header = Remove-TopLevelKey $header 'model_catalog_json' }

        $section = New-ProviderSection $p.provider $p.name $p.base_url 'responses' $Token
        $body += $section
        Write-Host "[OK] 已切换到 $($p.name)，模型 = $Model"
    }

    $newLines = @($header) + @($body)
    Write-Config $newLines
    if ($backup) { Write-Host "     切换前配置已备份: $backup" }
    Write-Host "     提示: 新开 codex 会话即可生效；桌面 App 需重启。"
}

# ==================== 交互菜单 ====================
function Select-Model {
    param([string]$BackendKey)
    $models = $Backends[$BackendKey].models
    Write-Host ''
    Write-Host ('请选择模型（{0}）:' -f $Backends[$BackendKey].name)
    Write-Host (' 1) {0}' -f $models['1'])
    Write-Host (' 2) {0}' -f $models['2'])
    $m = Read-Host '请输入 (1/2)'
    if ($m -eq '1' -or $m -eq '2') { return $models[$m] }
    Write-Host '输入无效，已取消'
    return $null
}

function Select-Key {
    param([string]$KeyEnv)
    $saved = Get-StoredKey $KeyEnv
    if ($saved) {
        Write-Host ''
        Write-Host 'API Key 使用方式:'
        Write-Host ' 1) 使用上次保存的 Key'
        Write-Host ' 2) 重新输入'
        $k = Read-Host '请输入 (1/2)'
        if ($k -eq '1') { return $saved }
        if ($k -eq '2') {
            $new = Read-KeyInteractive "请输入新的 $KeyEnv"
            if (-not $new) { Write-Host '未输入，已取消'; return $null }
            Save-Key $KeyEnv $new
            return $new
        }
        Write-Host '输入无效，已取消'
        return $null
    }
    Write-Host ''
    Write-Host "没有找到保存的 $KeyEnv，请输入新 Key（不会回显）:"
    $new = Read-KeyInteractive "请输入 $KeyEnv"
    if (-not $new) { Write-Host '未输入，已取消'; return $null }
    Save-Key $KeyEnv $new
    return $new
}

function Show-StatusSummary {
    if (-not (Test-Path $ConfigPath)) {
        Write-Host '（当前没有 config.toml）'
        return
    }
    $raw = Get-Content $ConfigPath -Raw -Encoding UTF8
    $model = ([regex]::Match($raw, '(?m)^model\s*=\s*"([^"]*)"')).Groups[1].Value
    $provider = ([regex]::Match($raw, '(?m)^model_provider\s*=\s*"([^"]*)"')).Groups[1].Value
    if (-not $provider) { $active = 'Codex 原版' }
    elseif ($Backends.ContainsKey($provider)) { $active = $Backends[$provider].name }
    else { $active = $provider }
    Write-Host ('当前: {0}  |  model: {1}' -f $active, $model)
}

function Start-Menu {
    while ($true) {
        Write-Host ''
        Write-Host '========== Codex 后端切换 =========='
        Show-StatusSummary
        Write-Host ''
        Write-Host ' 1) DeepSeek 官方'
        Write-Host ' 2) 并行智算云 (llmapi.paratera.com)'
        Write-Host ' 3) Codex 原版'
        Write-Host ' 0) 退出'
        $choice = Read-Host '请选择 (1/2/3/0)'
        if ($choice -eq '0') { Write-Host '已退出'; break }

        $backendKey = switch ($choice) {
            '1' { 'deepseek' }
            '2' { 'paratera' }
            '3' { 'openai' }
            default { '' }
        }
        if (-not $backendKey) { Write-Host '输入无效，请重新输入'; continue }

        $model = $null
        $token = ''
        if ($backendKey -ne 'openai') {
            $model = Select-Model $backendKey
            if (-not $model) { continue }
            $token = Select-Key $Backends[$backendKey].key_env
            if ($null -eq $token) { continue }
        }
        Apply-Switch $backendKey $model $token
    }
}

# ==================== 其它命令 ====================
function Get-Status {
    if (-not (Test-Path $ConfigPath)) {
        Write-Host "未找到 $ConfigPath"
        return
    }
    $raw = Get-Content $ConfigPath -Raw -Encoding UTF8
    $model = ([regex]::Match($raw, '(?m)^model\s*=\s*"([^"]*)"')).Groups[1].Value
    $provider = ([regex]::Match($raw, '(?m)^model_provider\s*=\s*"([^"]*)"')).Groups[1].Value
    $reasoning = ([regex]::Match($raw, '(?m)^model_reasoning_effort\s*=\s*"([^"]*)"')).Groups[1].Value
    $catalog = ([regex]::Match($raw, '(?m)^model_catalog_json\s*=\s*"([^"]*)"')).Groups[1].Value
    $baseUrl = ''
    $tokenMask = '未设置'
    if ($provider) {
        $esc = [regex]::Escape($provider)
        $m = [regex]::Match($raw, '(?ms)^\[model_providers\.' + $esc + '\][\s\S]*?^base_url\s*=\s*"([^"]*)"')
        $baseUrl = $m.Groups[1].Value
        $tm = [regex]::Match($raw, '(?ms)^\[model_providers\.' + $esc + '\][\s\S]*?^experimental_bearer_token\s*=\s*"([^"]*)"')
        if ($tm.Success -and $tm.Groups[1].Value) {
            $v = $tm.Groups[1].Value
            $tokenMask = if ($v.Length -gt 8) { $v.Substring(0, 4) + '***' } else { '***' }
        }
    }
    if (-not $provider) { $active = 'Codex 原版' }
    elseif ($Backends.ContainsKey($provider)) { $active = $Backends[$provider].name }
    else { $active = "自定义 ($provider)" }

    Write-Host "当前配置档 : $active"
    Write-Host "model       : $model"
    Write-Host "provider    : $(if ($provider) { $provider } else { 'openai (默认)' })"
    Write-Host "reasoning   : $reasoning"
    if ($baseUrl) { Write-Host "base_url    : $baseUrl" }
    if ($provider) { Write-Host "API Key     : $tokenMask" }
    if ($catalog) { Write-Host "model_catalog_json: $catalog" }
}

function Invoke-SetKey {
    param([string]$BackendKey, [string]$KeyValue)
    if (-not $Backends.ContainsKey($BackendKey) -or $BackendKey -eq 'openai') {
        throw 'setkey 仅支持 deepseek / paratera'
    }
    $envName = $Backends[$BackendKey].key_env
    if (-not $KeyValue) {
        $KeyValue = Read-KeyInteractive "请输入 $envName"
    }
    if (-not $KeyValue) { throw '未输入密钥' }
    Save-Key $envName $KeyValue
}

function Invoke-ListModels {
    param([string]$BackendKey)
    if (-not $Backends.ContainsKey($BackendKey) -or $BackendKey -eq 'openai') {
        throw 'list-models 仅支持 deepseek / paratera'
    }
    $p = $Backends[$BackendKey]
    $key = Get-StoredKey $p.key_env
    if (-not $key) { throw "缺少 $($p.key_env)，请先运行: .\switch-codex.ps1 setkey $BackendKey" }
    $url = $p.base_url.TrimEnd('/') + '/models'
    try {
        [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
        $resp = Invoke-RestMethod -Uri $url -Headers @{ Authorization = "Bearer $key" } -Method Get -TimeoutSec 30
        if ($resp.data) {
            foreach ($m in @($resp.data)) { Write-Host $m.id }
        } else {
            $resp | ConvertTo-Json -Depth 5
        }
    } catch {
        Write-Warning "查询失败: $($_.Exception.Message)"
    }
}

function Show-Usage {
    @"
用法:
  .\switch-codex.ps1 start        进入交互式切换菜单（不带参数也一样）
  .\switch-codex.ps1 status       查看当前配置
  .\switch-codex.ps1 setkey <deepseek|paratera> [密钥]
  .\switch-codex.ps1 list-models <deepseek|paratera>

菜单流程: 选择后端(1/2/3) -> 选择模型(1=Flash/2=Pro) -> 使用上次 Key 或重新输入
"@
}

# ==================== 入口 ====================
if (-not $Action) { $Action = 'start' }
$Action = $Action.ToLower()

switch ($Action) {
    'start'      { Start-Menu }
    'status'     { Get-Status }
    'help'       { Show-Usage }
    'setkey'     { if (-not $Arg2) { Show-Usage; throw 'setkey 需要指定 deepseek / paratera' }
                   Invoke-SetKey $Arg2.ToLower() $Arg3 }
    'list-models' { $b = if ($Arg2) { $Arg2.ToLower() } else { 'paratera' }
                    Invoke-ListModels $b }
    default      { Show-Usage; throw "未知命令: $Action" }
}
