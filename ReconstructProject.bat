@echo off
chcp 65001 >nul

REM =============================================
REM Unreal Engine Projekt Cleanup & Editor Start
REM =============================================

set "SCRIPT_DIR=C:\Users\robin\Desktop\Projects\NomNomWarsFoodWars\"
set "UPROJECT=%SCRIPT_DIR%NomNomWars.uproject"
set "UBT=D:\EpicGamesLauncherStuff\UE_5.7\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
set "UEEDITOR=D:\EpicGamesLauncherStuff\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe"
;set "PLUGIN_DIR=%SCRIPT_DIR%Plugins\MultiplayerSessionsMyPluginUE55"
set "WORKSPACE=%SCRIPT_DIR%NomNomWars.code-workspace"

REM -------------------------
REM 1. Voraussetzungen prüfen
REM -------------------------
echo Pruefe Voraussetzungen...
if not exist "%UBT%"      (echo UBT nicht gefunden      & pause & exit /b 1)
if not exist "%UPROJECT%" (echo .uproject nicht gefunden & pause & exit /b 1)
if not exist "%UEEDITOR%" (echo Editor nicht gefunden    & pause & exit /b 1)

REM -------------------------
REM 2. Laufende Prozesse beenden
REM -------------------------
echo Beende laufende UE-Prozesse...
taskkill /F /IM UnrealEditor.exe 2>nul
taskkill /F /IM UnrealBuildTool.exe 2>nul
timeout /t 2 /nobreak >nul

REM -------------------------
REM 3. Cleanup
REM -------------------------
echo Fuehre Cleanup durch...
cd /d "%SCRIPT_DIR%"

for %%D in (Binaries Intermediate Saved .vs .vscode) do (
    if exist "%SCRIPT_DIR%%%D" (
        echo Loesche %%D...
        rmdir /S /Q "%SCRIPT_DIR%%%D" 2>nul
    )
)

for %%D in (Binaries Intermediate) do (
    if exist "%PLUGIN_DIR%\%%D" (
        echo Loesche Plugin\%%D...
        rmdir /S /Q "%PLUGIN_DIR%\%%D" 2>nul
    )
)

for %%F in ("%SCRIPT_DIR%*.sln" "%SCRIPT_DIR%*.code-workspace") do (
    if exist "%%F" (
        echo Loesche %%~nxF...
        del /Q "%%F" 2>nul
    )
)

echo Loesche UBT Cache...
if exist "%LOCALAPPDATA%\UnrealBuildTool" (
    rmdir /S /Q "%LOCALAPPDATA%\UnrealBuildTool" 2>nul
)

REM -------------------------
REM 4. VS Code Projektdateien generieren
REM -------------------------
echo.
echo Generiere VS Code Projektdateien...
"%UBT%" -projectfiles -project="%UPROJECT%" -game -rocket -progress -vscode 2>nul | findstr /V "Re-writing"

REM -------------------------
REM 5. Auf .code-workspace warten
REM -------------------------
echo.
echo Warte auf .code-workspace...
set "MAX_WAIT=30"
set "COUNTER=0"

:WAIT_WORKSPACE
if exist "%WORKSPACE%" (
    echo Projektdateien erfolgreich erstellt!
    goto COMPILE
)
set /a COUNTER+=1
if %COUNTER% GEQ %MAX_WAIT% (
    echo Timeout: .code-workspace wurde nicht erstellt
    pause
    exit /b 1
)
timeout /t 1 /nobreak >nul
goto WAIT_WORKSPACE

REM -------------------------
REM 6. Projekt kompilieren
REM -------------------------
:COMPILE
echo.
echo Kompiliere Projekt...
"%UBT%" NomNomWarsEditor Development Win64 -project="%UPROJECT%" -game -progress
if %ERRORLEVEL% NEQ 0 (
    echo Compile fehlgeschlagen!
    pause
    exit /b 1
)

REM -------------------------
REM 7. Editor starten
REM -------------------------
:START_EDITOR
echo.
echo Starte Unreal Editor...
start "" "%UEEDITOR%" "%UPROJECT%" -editor
timeout /t 3 /nobreak >nul
powershell -command "Add-Type -AssemblyName System.Windows.Forms; [System.Windows.Forms.SendKeys]::SendWait('{ENTER}')" 2>nul

echo.
echo Fertig! Oeffne in VS Code mit: code "%WORKSPACE%"
echo.
exit /b 0