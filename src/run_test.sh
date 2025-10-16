#!/bin/bash

echo "=== PHILOSOPHERS TEST SUITE ==="

declare -A tests=(
    ["Death Precision"]="./philo 2 210 100 100"
    ["High Contention"]="./philo 5 600 200 200"
    ["Minimum Times"]="./philo 2 60 60 60"
    ["Stop Condition"]="./philo 3 800 200 200 2"
    ["Stress Test"]="./philo 100 1000 200 200"
    ["Single Philo"]="./philo 1 500 200 200"
    ["Uneven Times"]="./philo 4 300 100 150"
)

for test_name in "${!tests[@]}"; do
    echo "🧪 Testing: $test_name"
    echo "Command: ${tests[$test_name]}"

    # Ejecutar con timeout de 10 segundos
    timeout 10s ${tests[$test_name]} > output.log 2>&1

    if [ $? -eq 124 ]; then
        echo "⚠️  TIMEOUT - Possible deadlock"
    fi

    if grep -q "died" output.log; then
        echo "💀 Death detected"
    else
        echo "✅ No deaths"
    fi

    # Verificar condiciones específicas
    if [[ "$test_name" == "Single Philo" ]] && grep -q "is eating" output.log; then
        echo "❌ ERROR: Single philosopher should not eat!"
    fi

    echo "---"
    rm -f output.log
done

echo "=== TESTS COMPLETED ==="
