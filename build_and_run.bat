@echo off
echo --- Сборка симулятора устройства ---

g++ -o simulator.exe simulator.cpp

if %errorlevel% neq 0 (
    echo --- Ошибка компиляции симулятора ---
    exit /b 1
)

echo --- Сборка симулятора успешно завершена ---

echo --- Сборка основной программы ---

g++ -o weather_monitor.exe main.cpp -lpthread

if %errorlevel% neq 0 (
    echo --- Ошибка компиляции основной программы ---
    exit /b 1
)

echo --- Сборка основной программы успешно завершена ---

echo --- Запуск симулятора и основной программы, q для выхода из программы ---

start simulator.exe COM3
start weather_monitor.exe COM4

pause
