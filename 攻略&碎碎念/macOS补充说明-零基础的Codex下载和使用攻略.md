# 零基础的 Codex 下载和使用攻略：macOS 补充说明

> 作者：水至月生  
> 更新时间：2026 年 8 月 30 日  
> 对应主文档：[零基础的 Codex 下载和使用攻略](./零基础的codex下载和使用攻略.md)

## 前言

之前的攻略和配套脚本主要是在 Windows 上测试的，所以有朋友照着做到 Mac 时，会发现 `.bat` 双击打不开，PowerShell 脚本也不能直接运行。Mac 版并不是不能用，只是下载方式、终端命令和文件路径有些不同，于是便有了这份补充说明。

这篇只写 macOS 与原攻略不同的部分。账号注册、算力券申领、API Key 获取、费用与 AI 工作流等内容仍然看主文档即可。

文中涉及的软件界面、模型名称和平台接口以后都可能变化，遇到与本文不同的地方，以当时的官方页面和脚本菜单为准。有哪里写错了，也欢迎直接提醒我。

如果对你有帮助的话请说谢谢水至月生。

## 目录

- [一、先确认自己的 Mac 类型](#一先确认自己的-mac-类型)
- [二、下载与安装 Codex](#二下载与安装-codex)
- [三、使用 Codex CLI](#三使用-codex-cli)
- [四、用 Mac 脚本切换 API](#四用-mac-脚本切换-api)
  - [方案一：使用水月写的切换脚本](#方案一使用水月写的切换脚本)
  - [方案二：使用 DeepSeek 官方一键脚本](#方案二使用-deepseek-官方一键脚本)
- [五、恢复 Codex 原版](#五恢复-codex-原版)
- [六、常见问题](#六常见问题)
- [七、安全与备份](#七安全与备份)

## 一、先确认自己的 Mac 类型

点击屏幕左上角苹果图标，选择“关于本机”，查看芯片一栏。

- 显示 Apple M1、M2、M3、M4 或后续 M 系列，说明是 Apple Silicon；
- 显示 Intel，说明是 Intel Mac。

OpenAI 当前提供的 macOS 桌面应用下载项标注为 Apple Silicon。Apple Silicon 用户可以直接安装桌面应用；Intel Mac 如果无法安装，不是电脑坏了，可以改用 Codex CLI 或 VS Code 的 Codex 扩展。

## 二、下载与安装 Codex

### 1. Apple Silicon

1. 打开 [ChatGPT/Codex 官方下载页](https://chatgpt.com/download/)；
2. 下载 macOS 版本；
3. 打开下载得到的 `.dmg` 文件；
4. 把 ChatGPT 图标拖进“应用程序”文件夹；
5. 从“应用程序”中打开 ChatGPT，并登录自己的账号；
6. 在应用内进入 Codex，新建一个对话测试。

第一次打开时，macOS 可能会询问是否允许访问“下载”“桌面”“文稿”等文件夹。只给当前任务需要的权限即可，不需要把所有权限一股脑全部打开。

### 2. Intel Mac

如果官方下载页没有适合 Intel 芯片的安装包，可以先使用第三部分的 Codex CLI。平时习惯 VS Code 的话，也可以安装 Codex 扩展。两种方式都能读取项目、修改文件和运行命令，只是没有桌面应用的完整界面。

## 三、使用 Codex CLI

打开“终端”，粘贴下面的官方安装命令，然后按回车：

```bash
curl -fsSL https://chatgpt.com/codex/install.sh | sh
```

安装完成后，先关闭终端再重新打开，然后运行：

```bash
codex
```

第一次运行会让你选择登录方式。使用官方服务时，选择 ChatGPT 登录即可；如果之后使用本文的第三方 API 脚本，则按脚本完成切换后重新运行 `codex`。

如果终端提示 `command not found: codex`，通常是安装目录还没有加入 `PATH`。先完全退出终端并重新打开；仍然无效时，再按照安装命令最后显示的提示补充环境变量。

## 四、用 Mac 脚本切换 API

Mac 不能运行原来的 `启动Codex切换.bat`。这里有两种方案：如果需要在并行智算云、DeepSeek 和 Codex 原版之间来回切换，使用水月写的脚本；如果只准备接入 DeepSeek，直接使用 DeepSeek 官方脚本更省事。

两个脚本都会修改 `~/.codex/config.toml`，不要同时运行。决定换方案时，先用当前脚本恢复 Codex 原版，再运行另一个脚本。

### 方案一：使用水月写的切换脚本

本文旁边提供了下面这个文件：

```text
codex-api切换-Mac/switch-codex-mac.sh
```

这个脚本支持三种状态：

1. DeepSeek 官方；
2. 并行智算云；
3. Codex 原版。

#### 第一次使用

1. 下载并解压 `codex-api切换-Mac.zip`；
2. 按 `Command + Q` 完全退出 ChatGPT/Codex，不能只点左上角红色按钮；
3. 打开“终端”；
4. 输入 `bash`，后面留一个空格；
5. 把 `switch-codex-mac.sh` 从 Finder 拖进终端窗口；
6. 按回车运行脚本；
7. 在第一个菜单输入 `2`，选择并行智算云；
8. 在第二个菜单输入 `1` 或 `2`，选择模型；
9. 粘贴 API Key，再按回车；
10. 看到 `[OK]` 后，重新打开 ChatGPT/Codex。

完整命令看起来大概是这样，实际路径会因文件保存位置而不同：

```bash
bash "/Users/你的用户名/Downloads/codex-api切换-Mac/switch-codex-mac.sh"
```

输入 API Key 时，终端不会出现文字、圆点或星号，这是隐藏输入，不是键盘失灵。正常粘贴后按回车即可。

可以用下面这句话测试：

```text
请只回复“连接成功”，不要读取或修改任何文件。
```

桌面应用里可能显示具体模型名，也可能只显示 `Custom`。能正常回答，基本就说明接入成功。

#### 以后再次切换

再次用同样的方法运行脚本即可。脚本会询问是复用上次保存的 Key，还是重新输入。

熟悉终端后，也可以先进入脚本所在文件夹，再运行：

```bash
bash switch-codex-mac.sh
```

### 方案二：使用 DeepSeek 官方一键脚本

DeepSeek 官方也提供了适用于 macOS 和 Linux 的一键配置脚本。如果只想使用 DeepSeek，水月更建议优先尝试官方方案。官方脚本会同时处理模型目录和配置校验，平台以后更新模型信息时通常也会先更新自己的脚本。

开始前请确认三件事：

1. 已经安装 Codex CLI 或 ChatGPT/Codex 桌面应用；
2. 至少启动过一次 Codex，使 `~/.codex` 文件夹已经生成；
3. 已经在 [DeepSeek 开放平台](https://platform.deepseek.com/api_keys) 创建 API Key。

之后按下面操作：

1. 按 `Command + Q` 完全退出 ChatGPT/Codex；
2. 打开“终端”；
3. 粘贴 DeepSeek 官方提供的命令并按回车；

```bash
bash <(curl -fsSL https://cdn.deepseek.com/api-docs/codex-deepseek-setup-en.sh)
```

4. 在菜单中选择需要使用的模型；
5. 第一次运行时粘贴 DeepSeek API Key。Key 一般以 `sk-` 开头，输入时没有显示是正常现象；
6. 等待脚本完成配置检查，看到成功提示后关闭终端；
7. 重新打开 ChatGPT/Codex、VS Code 扩展或 Codex CLI。

官方脚本会完成下面几件事：

- 把原来的 `~/.codex/config.toml` 备份到 `~/.codex/backup-deepseek/`；
- 生成 `~/.codex/models.json`，写入 DeepSeek 模型的上下文长度、推理强度和工具调用等信息；
- 在 `config.toml` 中加入 DeepSeek provider，同时保留 MCP、项目信任等无关配置；
- 写入前检查 `config.toml` 和 `models.json` 的语法，检查失败时停止修改。

配置完成后，可以分别这样确认：

- Codex CLI：进入项目文件夹运行 `codex`，启动界面中的模型应当变成刚才选择的 DeepSeek 模型；
- Mac 桌面应用：模型位置通常显示为 `Custom`，这是正常现象，实际使用的是刚才选择的 DeepSeek 模型；
- VS Code：Codex 扩展与 CLI 共用 `~/.codex/config.toml`，重启扩展或 VS Code 后即可生效。

如果不放心直接执行联网脚本，可以先把脚本下载到“下载”文件夹并查看内容：

```bash
curl -fsSL https://cdn.deepseek.com/api-docs/codex-deepseek-setup-en.sh -o ~/Downloads/codex-deepseek-setup-en.sh
less ~/Downloads/codex-deepseek-setup-en.sh
```

确认没有问题后按 `q` 退出查看，再执行：

```bash
bash ~/Downloads/codex-deepseek-setup-en.sh
```

DeepSeek 官方接入说明：<https://api-docs.deepseek.com/quick_start/agent_integrations/codex/>

## 五、恢复 Codex 原版

### 使用水月脚本时

重新运行 `switch-codex-mac.sh`，在第一个菜单输入 `3`。看到下面的提示后，按 `Command + Q` 完全退出应用并重新打开：

```text
[OK] 已切换到 Codex 原版
```

恢复原版会删除脚本添加的 DeepSeek 和并行智算云配置，但不会删除聊天记录，也不会删除已经保存的第三方 API Key。

### 使用 DeepSeek 官方脚本时

重新执行官方命令：

```bash
bash <(curl -fsSL https://cdn.deepseek.com/api-docs/codex-deepseek-setup-en.sh)
```

在菜单中选择恢复原配置。DeepSeek 当前官方说明对应的是选项 `3`，如果以后菜单发生变化，以终端中实际显示的“恢复”选项为准。恢复完成后，再按 `Command + Q` 完全退出应用并重新打开。

切换 provider 后如果以前的会话暂时不见了，不代表聊天记录被删除。Codex 会按登录方式分组显示会话；恢复原来的配置后，之前使用官方 ChatGPT 登录产生的会话通常会重新出现。

## 六、常见问题

### 1. 双击脚本没有反应

`.sh` 文件默认不是通过双击运行的。按照第四部分的方法，在终端中输入 `bash` 加空格，再把脚本拖进去运行即可。不要为了省一步而使用来路不明的“一键解除系统限制”命令。

### 2. 提示 Permission denied

如果你直接输入脚本路径，可能遇到这个提示。最简单的解决方式是明确用 Bash 运行：

```bash
bash switch-codex-mac.sh
```

也可以给文件增加执行权限：

```bash
chmod +x switch-codex-mac.sh
```

之后再运行：

```bash
./switch-codex-mac.sh
```

### 3. 切换成功，但模型没有变化

先按 `Command + Q` 完全退出 ChatGPT/Codex，再重新打开。点击窗口左上角红色按钮通常只是关掉窗口，应用仍然可能在后台运行。

如果使用的是 Codex CLI，要退出当前会话，再重新执行 `codex`。

### 4. 提示模型不存在

平台可能更新了模型 ID。可以先换菜单中的另一个模型，也可以在终端查询平台返回的模型列表：

```bash
bash switch-codex-mac.sh list-models paratera
bash switch-codex-mac.sh list-models deepseek
```

这个命令只查询模型，不会切换配置。返回的是 JSON，查找其中的 `id` 即可。

### 5. 想查看当前配置

运行：

```bash
bash switch-codex-mac.sh status
```

脚本只显示后端和模型，不会显示完整 API Key。

### 6. 配置改坏了

每次切换前，脚本都会备份原来的配置。备份位置是：

```text
~/.codex/backup-switch
```

先完全退出 Codex，再把需要的备份复制回：

```text
~/.codex/config.toml
```

Finder 默认不显示以点开头的文件夹。可以在 Finder 中按 `Command + Shift + G`，输入 `~/.codex` 后回车。

### 7. Intel Mac 能不能使用脚本

可以。脚本只负责修改 Codex 的用户配置，与 Intel 或 Apple Silicon 无关。Intel Mac 没有合适的桌面应用时，可以让脚本配合 Codex CLI 使用。

## 七、安全与备份

Codex 的用户级配置位于：

```text
~/.codex/config.toml
```

OpenAI 官方文档也使用这个位置。Mac 脚本不会把 API Key 直接写进 `config.toml`，而是保存在：

```text
~/.codex/codex-switch-keys
```

脚本会把该目录和 Key 文件设置为仅当前用户可读。即便如此，API Key 仍然是本机凭证，不要把 `.codex` 文件夹发给别人，也不要上传到 GitHub、网盘或群文件。Key 一旦泄露，应立即到对应平台撤销并重新生成。

脚本切换前会备份 `config.toml`，不会删除其他 Codex 配置。第一次使用时仍然建议先保存正在进行的工作，再完全退出应用。

## 相关页面

- [ChatGPT/Codex 官方下载页](https://chatgpt.com/download/)
- [Codex CLI 官方说明](https://learn.chatgpt.com/docs/codex/cli)
- [Codex 配置参考](https://learn.chatgpt.com/docs/config-file/config-reference)
- [算力券申领平台](https://easycompute.cs.tsinghua.edu.cn/login)
- [并行智算云文档中心](https://ai.paratera.com/document)
- [DeepSeek API 平台](https://platform.deepseek.com/)
- [DeepSeek 官方 Codex 接入说明](https://api-docs.deepseek.com/quick_start/agent_integrations/codex/)
