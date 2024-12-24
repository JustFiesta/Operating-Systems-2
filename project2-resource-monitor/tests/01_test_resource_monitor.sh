#!/usr/bin/env bash

# Ścieżka do testowanego programu
PROGRAM="./resource-monitor"

# Licznik testów
TESTS_TOTAL=0
TESTS_PASSED=0

# Funkcja do wyłączania komend w tle
cleanup() {
    local pid=$1
    kill -TERM $pid 2>/dev/null || true
    wait $pid 2>/dev/null || true
}

# Funkcja do raportowania wyników testów
report_test() {
    local test_name="$1"
    local result="$2"
    local expected="$3"
    TESTS_TOTAL=$((TESTS_TOTAL + 1))
    
    if [ "$result" -eq "$expected" ]; then
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
    report_test "Long running process (sleep 5)" $? 0
}

# Test 2: Uruchomienie krótkotrwałego procesu (np. sleep 1)
test_short_running_process() {
    local cmd="sleep 1"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Short running process (sleep 1)" $? 0
}

# Test 3: Uruchomienie nieistniejącego procesu
test_non_existent_process() {
    local cmd="non_existent_command"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Non-existent process" $? 1
}

# Test 4: Proces zakończony przed monitorowaniem
test_terminated_before_monitoring() {
    local cmd="sleep 0.1"  # Bardzo krótki proces
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Terminated before monitoring (sleep 0.1)" $? 0
}

# Test 5: Testowanie procesu z długim czasem oczekiwania na zakończenie
test_wait_for_termination() {
    local cmd="sleep 5"
    $PROGRAM "$cmd" > /dev/null 2>&1
    report_test "Wait for process termination (sleep 5)" $? 0
}

# Test 6: Testowanie obciążenia za pomocą openssl speed
test_openssl_speed() {
    local cmd="openssl speed &"
    $PROGRAM "$cmd" > /dev/null 2>&1 &
    sleep 5
    cleanup $!
    report_test "CPU load with openssl speed" $? 0
}

# Test 7: Testowanie obciążenia I/O za pomocą cat /dev/zero > /dev/null
test_io_load() {
    local cmd="cat /dev/zero > /dev/null"
    $PROGRAM "$cmd" > /dev/null 2>&1 &
    sleep 5
    cleanup $!
    report_test "I/O load with cat /dev/zero > /dev/null" $? 0
}

# Test 8: Testowanie obciążenia CPU za pomocą sha1sum /dev/zero &
test_sha1sum_load() {
    local cmd="sha1sum /dev/zero &"
    $PROGRAM "$cmd" > /dev/null 2>&1 &
    sleep 5
    cleanup $!
    report_test "CPU load with sha1sum /dev/zero" $? 0
}

# Testy
test_long_running_process
test_short_running_process
test_non_existent_process
test_terminated_before_monitoring
test_wait_for_termination
test_openssl_speed
test_io_load
test_sha1sum_load

# Podsumowanie wyników
echo -e "\nTests completed: $TESTS_TOTAL"
echo "Tests passed: $TESTS_PASSED"
echo "Tests failed: $((TESTS_TOTAL - TESTS_PASSED))"