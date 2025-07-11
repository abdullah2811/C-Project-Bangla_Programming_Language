@echo off
setlocal enabledelayedexpansion

:: Get the batch file's directory
set "BATCH_DIR=%~dp0"
set "TR=%BATCH_DIR%translator.exe"

:: Default input if none provided
set "INPUT=%~1"
if "%INPUT%"=="" set "INPUT=%BATCH_DIR%input.bpl"

:: Check if input file exists
if not exist "%INPUT%" (
    echo Error: File not found - "%INPUT%"
    echo Usage: Drag a .bpl file here or name it input.bpl
    pause
    exit /b 1
)

:: Check if translator exists
if not exist "%TR%" (
    echo Error: translator.exe not found in:
    echo %BATCH_DIR%
    pause
    exit /b 1
)

:: Extract filename without extension
for %%F in ("%INPUT%") do (
    set "FNAME=%%~nF"
)

:: Check if FNAME.c already exists, and if so, append (1), (2), etc.
set "SUFFIX="
set "INDEX=1"
:check_loop
set "TEMP_C=%BATCH_DIR%%FNAME%%SUFFIX%.c"
if exist "!TEMP_C!" (
    set "SUFFIX=(%INDEX%)"
    set /a INDEX+=1
    goto check_loop
)

:: Set executable name
set "OUTPUT_EXE=%BATCH_DIR%%FNAME%%SUFFIX%.exe"

:: Step 1: Translate .bpl to .c
echo.
echo [1/3] Translating Bangla source code...
"%TR%" "%INPUT%" "!TEMP_C!"
if errorlevel 1 (
    echo ERROR: Translation failed
    pause
    exit /b 1
)

:: Step 2: Compile the .c file with UTF‑8 support
echo.
echo [2/3] Compiling to .exe...
gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 "!TEMP_C!" -o "!OUTPUT_EXE!"
if errorlevel 1 (
    echo ERROR: Compilation failed
    echo ---- Translated C code ----
    type "!TEMP_C!"
    pause
    exit /b 1
)

:: Step 3: Run the .exe file
echo.
echo [3/3] Running the program...
echo -------------------------------
"!OUTPUT_EXE!"
echo.
echo -------------------------------

echo.
echo Thanks for using the Bangla Programming Language developed by Abdullah.
echo.
pause >nul
