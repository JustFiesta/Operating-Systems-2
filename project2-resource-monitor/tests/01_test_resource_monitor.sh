#!/usr/bin/env bash

# Ścieżka do testowanego programu
PROGRAM="./resource-monitor"

# Licznik testów
TESTS_TOTAL=0
TESTS_PASSED=0

# Funkcja do raportowania wyników testów
report_test() {
    local test_name="$1"
    local result="$2"
    TESTS_TOTAL=$((TESTS_TOTAL + 1))
    
    if [ "$result" -eq 0 ]; then
        echo "[PASS] $test_name"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo "[FAIL] $test_name"
    fi
}

# Test 1: Uruchomienie długotrwałego procesu (np. sleep 5)
test_long_running_process() {
    local cmd="sleep 5"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Long running process (sleep 5)" $?
}

# Test 2: Uruchomienie krótkotrwałego procesu (np. sleep 1)
test_short_running_process() {
    local cmd="sleep 1"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Short running process (sleep 1)" $?
}

# Test 3: Uruchomienie nieistniejącego procesu
test_non_existent_process() {
    local cmd="nonexistent_command"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Non-existent process" $?
}

# Test 4: Proces zakończony przed monitorowaniem
test_terminated_before_monitoring() {
    local cmd="sleep 0.1"  # Bardzo krótki proces
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Terminated before monitoring (sleep 0.1)" $?
}

# Test 5: Monitorowanie procesu z dużym zużyciem pamięci
test_high_memory_usage_process() {
    local cmd="stress --vm 1 --vm-bytes 256M --timeout 5s"  # Używa pamięci
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "High memory usage process" $?
}

# Test 6: Testowanie procesu z długim czasem oczekiwania na zakończenie
test_wait_for_termination() {
    local cmd="sleep 5"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Wait for process termination (sleep 5)" $?
}

# Test 7: Nieprawidłowe polecenie z błędnymi argumentami
test_invalid_command() {
    local cmd="echo 'Hello' | non_existent_command"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Invalid command" $?
}

# Testy
echo "Running tests...\n"

test_long_running_process
test_short_running_process
test_non_existent_process
test_terminated_before_monitoring
test_high_memory_usage_process
test_wait_for_termination
test_invalid_command

# Podsumowanie wyników
echo -e "\nTests completed: $TESTS_TOTAL"
echo "Tests passed: $TESTS_PASSED"
echo "Tests failed: $((TESTS_TOTAL - TESTS_PASSED))"
