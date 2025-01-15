@echo off
echo --- Сборка симулятора устройства ---

g++ -o simulator.exe simulator.cpp

if %errorlevel% neq 0 (
    echo --- Ошибка компиляции ---
    exit /b 1
)

echo --- Сборка успешно завершена ---
pause

