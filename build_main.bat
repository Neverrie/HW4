@echo off
echo --- Сборка основной программы ---

g++ -o weather_monitor.exe main.cpp -lpthread

if %errorlevel% neq 0 (
    echo --- Ошибка компиляции ---
    exit /b 1
)

echo --- Сборка успешно завершена ---
pause
