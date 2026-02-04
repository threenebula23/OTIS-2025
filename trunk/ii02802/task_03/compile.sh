#!/usr/bin/env bash
set -euo pipefail

echo ""
echo "=== Сборка и запуск проекта ==="
echo ""

# Удаляем старую папку build, если она существует
if [ -d "build" ]; then
    echo "Удаляем старую папку build..."
    rm -rf build
    echo "Папка build удалена."
else
    echo "Папка build не найдена — создаём новую."
fi

echo ""
mkdir -p build
cd build

echo "[1/4] Конфигурирование CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo ""
echo "[2/4] Сборка основной программы..."
cmake --build . --config Release --target task_3_ii02802 -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "[3/4] Сборка тестов..."
cmake --build . --config Release --target testlab3_runner_ii02802 -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "[4/4] Запуск тестов..."
if [[ -f ./testlab3_runner_ii02802 ]]; then
    echo "Запускаем тесты..."
    ./testlab3_runner_ii02802
    echo ""
else
    echo "Ошибка: исполняемый файл тестов не найден: ./testlab3_runner_ii02802"
    exit 1
fi

echo ""
echo "Запуск основной программы..."
if [[ -f ./task_3_ii02802 ]]; then
    echo "Запускаем программу..."
    ./task_3_ii02802
    echo ""
    echo "Результаты сохранены в: simulation_results.csv"
    echo "Запуск визуализации..."
    if command -v python3 >/dev/null 2>&1; then
        python3 ../vizualize.py
    elif command -v python >/dev/null 2>&1; then
        python ../vizualize.py
    else
        echo "Python не найден. Визуализация не запущена."
        echo "Запустите vizualize.py вручную."
    fi
else
    echo "Ошибка: исполняемый файл основной программы не найден: ./task_3_ii02802"
    exit 1
fi

cd ..
echo ""
echo "Готово."
read -p "Нажмите Enter для завершения..."