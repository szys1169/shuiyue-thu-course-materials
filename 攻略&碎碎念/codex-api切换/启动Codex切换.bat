@echo off
chcp 65001 >nul
title Codex Switch
cd /d "%~dp0"
powershell -NoProfile -ExecutionPolicy Bypass -Command "Unblock-File -LiteralPath '%~dp0switch-codex.ps1' -ErrorAction SilentlyContinue"
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0switch-codex.ps1" start
echo.
echo ============================================
echo  Finished. You can close this window now.
echo ============================================
pause
