#!/bin/bash

# Ścieżka do testowanego programu
PROGRAM="./env-manager"

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

# Test 1: Sprawdzenie komendy list
test_list() {
    $PROGRAM list > /dev/null 2>&1
    report_test "Basic list command" $?
}

# Test 2: Dodawanie zmiennej
test_add() {
    $PROGRAM add TEST_VAR=hello
    # Sprawdź czy zmienna została dodana
    if [ "$TEST_VAR" = "hello" ]; then
        report_test "Adding environment variable" 0
    else
        report_test "Adding environment variable" 1
    fi
}

# Test 3: Usuwanie zmiennej
test_remove() {
    export TEST_VAR_REMOVE=test
    $PROGRAM remove TEST_VAR_REMOVE
    if [ -z "$TEST_VAR_REMOVE" ]; then
        report_test "Removing environment variable" 0
    else
        report_test "Removing environment variable" 1
    fi
}

# Test 4: Nadpisywanie istniejącej zmiennej
test_overwrite() {
    $PROGRAM add TEST_VAR=hello
    $PROGRAM add TEST_VAR=world
    if [ "$TEST_VAR" = "world" ]; then
        report_test "Overwriting existing variable" 0
    else
        report_test "Overwriting existing variable" 1
    fi
}

# Uruchomienie testów
echo "Running basic functionality tests..."
test_list
test_add
test_remove
test_overwrite

# Podsumowanie
echo "Tests completed: $TESTS_PASSED/$TESTS_TOTAL passed"