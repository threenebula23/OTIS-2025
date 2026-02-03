@echo off
setlocal EnableDelayedExpansion

echo.
echo === Building project (Windows / MinGW) ===
echo.

if not exist build mkdir build
cd build

echo [1/4] Configuring CMake...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

if %errorlevel% neq 0 (
    echo.
    echo CMake configuration FAILED!
    cd ..
    pause
    exit /b %errorlevel%
)

echo.
echo [2/4] Building main program...
cmake --build . --config Release --target task_3_ii02802

if %errorlevel% neq 0 (
    echo.
    echo Build main program FAILED!
    cd ..
    pause
    exit /b %errorlevel%
)

echo.
echo [3/4] Building tests...
cmake --build . --config Release --target testlab3_runner_ii02802

if %errorlevel% neq 0 (
    echo.
    echo Build tests FAILED!
    cd ..
    pause
    exit /b %errorlevel%
)

echo.
echo [4/4] Running tests...
if exist testlab3_runner_ii02802.exe (
    echo Running tests...
    .\testlab3_runner_ii02802.exe
) else (
    echo Test executable not found: testlab3_runner_ii02802.exe
)

echo.
echo Running main program...
if exist task_3_ii02802.exe (
    echo Running main...
    .\task_3_ii02802.exe
    echo.
    echo Results saved to: simulation_results.csv
) else (
    echo Main executable not found: task_3_ii02802.exe
)

cd ..
echo.
echo Done.
pause