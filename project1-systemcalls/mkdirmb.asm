%define SYS_write 1
%define SYS_exit 60
%define SYS_mkdir 83
%define PATH_MAX 4096

section .data
    usage_msg db "Usage: mkdirmb [-p] directory_path", 10, 0
    success_msg db "Directory created successfully.", 10, 0
    error_msg db "Error creating directory.", 10, 0

section .bss
    path resb PATH_MAX      ; Buffer for directory path (max path length)

section .text
    global _start

_start:
    ; Check for arguments
    mov rdi, rsi            ; Get argument count
    cmp rdi, 2              ; Minimum 2 arguments: program and path
    jl print_usage          ; If fewer, print usage

    ; Check for -p flag
    mov rdi, [rsi + 8]      ; First argument after program name
    mov al, '-p'
    cmp byte [rdi], al
    je set_create_parents_flag

    ; No -p flag, treat as directory path
    mov rdi, [rsi + 8]
    jmp process_path

set_create_parents_flag:
    ; Set flag to create parent directories
    mov rdi, [rsi + 16]     ; Get the second argument as path
    jmp process_path

print_usage:
    mov rdi, usage_msg
    call print_string
    jmp exit_program

process_path:
    ; Copy directory path to buffer using strncpy equivalent
    mov rsi, path           ; Destination buffer
    mov rdi, [rsi + 8]      ; Source path string
    mov rcx, PATH_MAX       ; Max bytes to copy
    call strncpy

    ; Set directory creation mode (0755)
    mov rsi, 0o755
    call create_parents

    ; Print success message if directory created
    mov rdi, success_msg
    call print_string
    jmp exit_program

create_parents:
    ; Process path and create each directory in sequence
    mov rcx, 0                  ; Character counter

next_segment:
    mov al, [path + rcx]
    cmp al, 0
    je create_final_dir         ; If end of path, create final dir

    cmp al, '/'
    jne next_char

    ; Temporarily replace '/' with null-terminator
    mov byte [path + rcx], 0
    mov rax, SYS_mkdir         ; mkdir syscall
    mov rdi, path               ; path up to current position
    mov rsi, 0o755              ; directory mode
    syscall

    ; Restore '/' character
    mov byte [path + rcx], '/'
next_char:
    inc rcx
    jmp next_segment

create_final_dir:
    ; Create the final directory specified by path
    mov rax, SYS_mkdir
    mov rdi, path
    mov rsi, 0o755
    syscall
    ret

strncpy:
    ; Copy src to dest until n bytes or null terminator
    mov rdx, rcx                ; n - max bytes to copy
.copy_loop:
    cmp byte [rdi], 0           ; Check for null terminator in src
    je .fill_null               ; If end of src, fill with nulls
    mov al, [rdi]               ; Load byte from src
    mov [rsi], al               ; Store byte to dest
    inc rdi                     ; Advance src pointer
    inc rsi                     ; Advance dest pointer
    dec rdx                     ; Decrease byte count
    jnz .copy_loop              ; Continue if not zero

.fill_null:
    mov byte [rsi], 0           ; Write null terminator to dest
    inc rsi
    dec rdx
    jnz .fill_null              ; Fill remaining bytes with nulls
    ret

print_string:
    ; Print string from rdi, calculate length using strlen
    mov rsi, rdi                ; Load string pointer into rsi
    call strlen                 ; Calculate string length
    mov rdx, rax                ; Move length to rdx

    mov rax, SYS_write          ; write syscall
    mov rdi, 1                  ; file descriptor (stdout)
    syscall
    ret

strlen:
    ; Simple implementation of strlen (returns length in rax)
    xor rax, rax                ; Clear rax (length)
strlen_loop:
    cmp byte [rsi + rax], 0      ; Check if null terminator
    je strlen_done
    inc rax                     ; Increment length
    jmp strlen_loop
strlen_done:
    ret

exit_program:
    mov rax, SYS_exit           ; exit syscall
    xor rdi, rdi                ; status 0
    syscall
