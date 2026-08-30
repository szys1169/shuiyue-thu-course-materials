@echo off
chcp 65001 >nul
title Create Codex Switch Desktop Shortcut
cd /d "%~dp0"
powershell -NoProfile -ExecutionPolicy Bypass -Command "$target = (Get-ChildItem -LiteralPath '%~dp0' -Filter '*.bat' | Where-Object { $_.Name -ne '%~nx0' } | Select-Object -First 1).FullName; $ws = New-Object -ComObject WScript.Shell; $lnk = $ws.CreateShortcut([Environment]::GetFolderPath('Desktop') + '\Codex' + [char]0x5207 + [char]0x6362 + '.lnk'); $lnk.TargetPath = $target; $lnk.WorkingDirectory = '%~dp0'; $lnk.Save()"
echo.
echo  Desktop shortcut created.
echo  You can now start it from the Desktop.
pause
