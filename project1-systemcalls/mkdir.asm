; mkdir.asm - implementacja mkdir z opcjami -p i -h
; Rejestry użyte w programie:
; rax - używany do numerów syscalli i wartości zwracanych
; rbx - liczba argumentów, później używany do tymczasowego przechowywania danych
; rdi - pierwszy argument funkcji/syscalla (np. ścieżka)
; rsi - drugi argument funkcji/syscalla (np. uprawnienia)
; r12 - wskaźnik do tablicy argumentów
; r13 - indeks aktualnie przetwarzanego argumentu
; r14 - flaga -p (0 = wyłączona, 1 = włączona)

section .data
    ; Definicje stałych systemowych
    SYS_EXIT    equ 60     ; Numer syscalla exit
    SYS_WRITE   equ 1      ; Numer syscalla write
    SYS_MKDIR   equ 83     ; Numer syscalla mkdir
    STDOUT      equ 1      ; Standardowe wyjście
    STDERR      equ 2      ; Standardowe wyjście błędów
    PATH_MAX    equ 4096   ; Maksymalna długość ścieżki
    
    ; Komunikaty wyświetlane przez program
    usage_msg:      db "Usage: %s [-p] directory_path", 10, 0  ; 10 = nowa linia, 0 = koniec stringa
    success_msg:    db "Directory created successfully.", 10, 0
    error_msg:      db "Error: No directory path provided.", 10, 0
    create_err_msg: db "Failed to create directory: ", 0
    
    ; Stałe używane przy tworzeniu katalogów
    mode:       equ 0755q    ; Uprawnienia w formacie oktalnym (rwxr-xr-x)
    O_CREAT:    equ 0100q    ; Flaga create dla syscalli
    
section .bss
    ; Bufory na ścieżki
    path_buffer:    resb PATH_MAX    ; Bufor roboczy na modyfikowaną ścieżkę
    original_path:  resb PATH_MAX    ; Bufor na oryginalną ścieżkę

section .text
global _start

_start:
    ; [Stan początkowy stosu]
    ; [rsp] -> liczba argumentów
    ; [rsp + 8] -> nazwa programu
    ; [rsp + 16] -> pierwszy argument itd.
    
    pop rbx                 ; rbx = liczba argumentów (argc)
    mov r12, rsp           ; r12 = wskaźnik do tablicy argumentów (argv)
    
    ; Sprawdź czy są argumenty
    cmp rbx, 1             ; Porównaj liczbę argumentów z 1
    jle print_usage        ; Jeśli <= 1, wyświetl usage (brak argumentów)
    
    ; Inicjalizacja przed przetwarzaniem argumentów
    mov r13, 1             ; r13 = 1 (indeks pierwszego argumentu, pomijamy nazwę programu)
    xor r14, r14          ; r14 = 0 (flaga -p wyłączona)
    
process_args:
    ; Przetwarzanie argumentów wiersza poleceń
    ; r13 - aktualny indeks argumentu
    ; rbx - całkowita liczba argumentów
    cmp r13, rbx          ; Sprawdź czy przetworzyliśmy wszystkie argumenty
    jge no_path_error     ; Jeśli tak i nie znaleźliśmy ścieżki, błąd
    
    ; Pobierz kolejny argument
    mov rdi, [r12 + r13*8] ; rdi = argv[r13] (adres aktualnego argumentu)
    cmp byte [rdi], '-'    ; Sprawdź czy argument zaczyna się od '-'
    jne process_path       ; Jeśli nie, to musi być ścieżka
    
    ; Sprawdzanie opcji
    inc rdi                ; Przesuń wskaźnik za znak '-'
    cmp byte [rdi], 'p'    ; Sprawdź czy to opcja 'p'
    je set_p_flag
    cmp byte [rdi], 'h'    ; Sprawdź czy to opcja 'h'
    je print_usage
    jmp print_usage        ; Jeśli nieznana opcja, wyświetl usage
    
set_p_flag:
    mov r14, 1            ; Ustaw flagę -p (r14 = 1)
    inc r13               ; Przejdź do następnego argumentu
    jmp process_args
    
process_path:
    ; Kopiowanie ścieżki do bufora
    ; rsi - źródłowy string (argument z wiersza poleceń)
    ; rdi - docelowy bufor (path_buffer)
    mov rsi, [r12 + r13*8]
    mov rdi, path_buffer
    call strcpy
    
    ; Sprawdź czy trzeba utworzyć katalogi nadrzędne
    test r14, r14         ; Sprawdź flagę -p
    jnz create_parents    ; Jeśli ustawiona, twórz katalogi nadrzędne
    
    ; Tworzenie pojedynczego katalogu
    mov rdi, path_buffer  ; rdi = ścieżka do katalogu
    mov rsi, mode         ; rsi = uprawnienia (0755)
    call create_directory
    jmp check_result

create_directory:
    ; Funkcja tworząca katalog używając syscalla mkdir
    ; rdi - ścieżka do katalogu
    ; rsi - uprawnienia
    push rbp
    mov rbp, rsp
    
    mov rax, SYS_MKDIR    ; rax = 83 (numer syscalla mkdir)
    syscall               ; Wykonaj syscall mkdir(path, mode)
    
    leave
    ret

create_parents:
    ; Funkcja tworząca katalogi nadrzędne
    ; rdi - ścieżka wejściowa
    mov rdi, path_buffer
    call create_parent_dirs
    
check_result:
    ; Sprawdzenie wyniku operacji
    ; rax - kod powrotu z create_directory/create_parent_dirs
    test rax, rax         ; Sprawdź czy wystąpił błąd (rax != 0)
    jnz print_error       ; Jeśli błąd, wyświetl komunikat
    
    ; Wyświetl komunikat o sukcesie i zakończ
    mov rdi, success_msg
    call print_string
    mov rax, SYS_EXIT     ; Przygotuj syscall exit
    xor rdi, rdi          ; rdi = 0 (kod wyjścia: sukces)
    syscall               ; Zakończ program

create_parent_dirs:
    ; Funkcja rekurencyjnie tworząca katalogi nadrzędne
    ; rbx - wskaźnik do ścieżki
    ; r12 - indeks aktualnego znaku
    push rbp
    mov rbp, rsp
    push rbx              ; Zachowaj oryginalne wartości rejestrów
    push r12
    
    mov rbx, rdi          ; rbx = wskaźnik do ścieżki
    mov r12, 1            ; r12 = 1 (indeks, pomijamy pierwszy znak)
    
.loop:
    ; Pętla przetwarzająca każdy znak ścieżki
    cmp byte [rbx + r12], 0    ; Sprawdź czy koniec stringa
    je .done
    
    cmp byte [rbx + r12], '/'  ; Sprawdź czy aktualny znak to '/'
    jne .next
    
    ; Znaleziono '/', próba utworzenia katalogu
    mov byte [rbx + r12], 0    ; Tymczasowo zastąp '/' przez 0
    
    push r12              ; Zachowaj r12
    mov rdi, rbx          ; rdi = ścieżka do częściowego katalogu
    mov rsi, mode         ; rsi = uprawnienia
    call create_directory
    pop r12               ; Przywróć r12
    
    mov byte [rbx + r12], '/'  ; Przywróć znak '/'
    
.next:
    inc r12               ; Przejdź do następnego znaku
    jmp .loop
    
.done:
    ; Utwórz końcowy katalog
    mov rdi, rbx
    mov rsi, mode
    call create_directory
    
    pop r12               ; Przywróć zachowane rejestry
    pop rbx
    leave
    ret

strcpy:
    ; Funkcja kopiująca string
    ; rdi - cel
    ; rsi - źródło
    push rbp
    mov rbp, rsp
    
.loop:
    mov al, [rsi]         ; al = aktualny znak ze źródła
    mov [rdi], al         ; Skopiuj znak do celu
    test al, al           ; Sprawdź czy to koniec stringa (znak 0)
    jz .done              ; Jeśli tak, zakończ
    inc rsi               ; Przejdź do następnego znaku źródła
    inc rdi               ; Przejdź do następnej pozycji w celu
    jmp .loop
    
.done:
    leave
    ret

print_string:
    ; Funkcja wyświetlająca string na standardowe wyjście
    ; rdi - wskaźnik do stringa
    push rbp
    mov rbp, rsp
    
    ; Oblicz długość stringa
    mov rsi, rdi          ; rsi = wskaźnik do stringa
    xor rdx, rdx          ; rdx = 0 (licznik długości)
.len_loop:
    cmp byte [rsi + rdx], 0    ; Sprawdź czy koniec stringa
    je .print                  ; Jeśli tak, wyświetl
    inc rdx                    ; Zwiększ licznik długości
    jmp .len_loop
    
.print:
    ; Wykonaj syscall write
    mov rax, SYS_WRITE    ; rax = 1 (syscall write)
    mov rdi, STDOUT       ; rdi = 1 (standardowe wyjście)
    syscall               ; write(stdout, string, length)
    
    leave
    ret

print_usage:
    ; Wyświetl instrukcję użycia i zakończ
    mov rdi, usage_msg
    call print_string
    mov rax, SYS_EXIT
    mov rdi, 1            ; Kod wyjścia: 1 (błąd)
    syscall

print_error:
    ; Wyświetl komunikat o błędzie i zakończ
    mov rdi, create_err_msg
    call print_string
    mov rax, SYS_EXIT
    mov rdi, 1            ; Kod wyjścia: 1 (błąd)
    syscall

no_path_error:
    ; Wyświetl błąd braku ścieżki i zakończ
    mov rdi, error_msg
    call print_string
    mov rax, SYS_EXIT
    mov rdi, 1            ; Kod wyjścia: 1 (błąd)
    syscall