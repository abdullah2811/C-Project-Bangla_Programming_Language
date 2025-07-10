@echo off
setlocal enabledelayedexpansion

:: Get the batch file's directory
set "BATCH_DIR=%~dp0"
set "TR=%BATCH_DIR%translator.exe"

:: Default input if none provided
set "INPUT=%~1"
if "%INPUT%"=="" set "INPUT=%BATCH_DIR%input.bpl"

:: Define output file paths
set "TEMP_C=%BATCH_DIR%translated_temp.c"
set "OUTPUT_EXE=%BATCH_DIR%program.exe"

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

:: Clean up old outputs
del "%TEMP_C%" "%OUTPUT_EXE%" 2>nul

:: Step 1: Translate .bpl to C
echo.
echo [1/3] Translating Bangla source code...
"%TR%" "%INPUT%" "%TEMP_C%"
if errorlevel 1 (
    echo ERROR: Translation failed
    pause
    exit /b 1
)

:: Step 2: Compile C code (force UTF-8 support in compiler)
echo.
echo [2/3] Compiling C code with UTF‑8 support...
gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 "%TEMP_C%" -o "%OUTPUT_EXE%"
if errorlevel 1 (
    echo ERROR: Compilation failed
    echo ---- Translated C code ----
    type "%TEMP_C%"
    pause
    exit /b 1
)

:: Step 3: Run the compiled executable
echo.
echo [3/3] Running the program...
echo -------------------------------
"%OUTPUT_EXE%"
echo.
echo -------------------------------

:: Optional: clean up temporary files
:: del "%TEMP_C%" "%OUTPUT_EXE%" 2>nul

echo.
echo Thanks for using the Bangla Programming Language developed by Abdullah.
echo.
pause >nul
