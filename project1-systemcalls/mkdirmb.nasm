section .data
    dir_name db "new_directory", 0   ; nazwa katalogu zakończona zerem

section .text
    global _start

_start:
    ; Syscall mkdir
    mov rax, 83                    ; numer syscallu dla mkdir w x86_64
    mov rdi, dir_name              ; pierwszy argument: wskaźnik do nazwy katalogu
    mov rsi, 0o755                 ; drugi argument: prawa dostępu w formacie ósemkowym
    syscall                        ; wykonanie syscall

    ; Obsługa błędów (sprawdzamy wartość zwróconą w rax)
    cmp rax, 0                     ; jeżeli rax jest 0, to syscall zakończył się sukcesem
    je success

    ; Wyświetlenie komunikatu o błędzie w przypadku niepowodzenia
    mov rax, 60                    ; numer syscallu dla exit
    mov rdi, 1                     ; kod wyjścia w przypadku błędu
    syscall

success:
    ; Wyjście z kodem sukcesu
    mov rax, 60                    ; numer syscallu dla exit
    xor rdi, rdi                   ; kod wyjścia 0 (sukces)
    syscall
