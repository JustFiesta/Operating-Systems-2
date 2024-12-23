#!/bin/bash

# Ścieżka do testowanego programu
PROGRAM="../env-manager"

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

# Test 1: Próba dodania zmiennej z nieprawidłową nazwą
test_invalid_name() {
    $PROGRAM add 123TEST=value 2>/dev/null
    if [ $? -ne 0 ]; then
        report_test "Invalid variable name (starts with number)" 0
    else
        report_test "Invalid variable name (starts with number)" 1
    fi
}

# Test 2: Próba dodania zmiennej z pustą nazwą
test_empty_name() {
    $PROGRAM add =value 2>/dev/null
    if [ $? -ne 0 ]; then
        report_test "Empty variable name" 0
    else
        report_test "Empty variable name" 1
    fi
}

# Test 3: Próba usunięcia nieistniejącej zmiennej
test_remove_nonexistent() {
    $PROGRAM remove NONEXISTENT_VAR_12345 2>/dev/null
    if [ $? -ne 0 ]; then
        report_test "Removing nonexistent variable" 0
    else
        report_test "Removing nonexistent variable" 1
    fi
}

# Test 4: Próba dodania zmiennej z niedozwolonymi znakami
test_invalid_chars() {
    $PROGRAM add "TEST@VAR=value" 2>/dev/null
    if [ $? -ne 0 ]; then
        report_test "Invalid characters in variable name" 0
    else
        report_test "Invalid characters in variable name" 1
    fi
}

# Test 5: Sprawdzenie nieprawidłowej składni komendy add
test_invalid_add_syntax() {
    $PROGRAM add TEST_VAR 2>/dev/null
    if [ $? -ne 0 ]; then
        report_test "Invalid add command syntax" 0
    else
        report_test "Invalid add command syntax" 1
    fi
}

# Uruchomienie testów
echo "Running edge cases and error handling tests..."
test_invalid_name
test_empty_name
test_remove_nonexistent
test_invalid_chars
test_invalid_add_syntax

# Podsumowanie
echo "Tests completed: $TESTS_PASSED/$TESTS_TOTAL passed"