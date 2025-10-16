#!/bin/bash

echo "=== CORRECTED PHILOSOPHERS TEST ==="

run_test() {
    local test_name="$1"
    local command="$2"
    local expect_timeout="$3"  # "yes" o "no"

    echo "🧪 $test_name"
    echo "   Command: $command"

    timeout 5s $command > output.log 2>&1
    local exit_code=$?

    if [ "$expect_timeout" = "yes" ]; then
        if [ $exit_code -eq 124 ]; then
            echo "   ✅ PASS: Program runs indefinitely (no deaths)"
        else
            echo "   ❌ FAIL: Program stopped (unexpected death or completion)"
            grep "died" output.log 2>/dev/null && echo "   💀 Death detected"
        fi
    else
        if grep -q "died" output.log; then
            echo "   ✅ PASS: Death correctly detected"
        else
            echo "   ❌ FAIL: Expected death but none occurred"
        fi
    fi
    echo ""
}

# TESTS CORREGIDOS
run_test "Single philosopher should die" "./philo 1 800 200 200" "no"
run_test "5 philosophers no death" "./philo 5 800 200 200" "yes"
run_test "2 philosophers tight timing" "./philo 2 210 100 100" "yes"
run_test "4 philosophers should die" "./philo 2 60 60 60" "no"

echo "=== TESTING COMPLETED ==="
