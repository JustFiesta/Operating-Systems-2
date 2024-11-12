# Syscalls project

This project is using system calls to create simple mkdir program.

They were made for UNIX x86_64.

## Ports

These program can be compiled from:

* C

```shell
gcc mkdirmb.c -o mkdirmb
```

* NASM

```shell
nasm -f elf64 -o mkdir_program.o mkdir_program.asm
ld -o mkdir_program mkdir_program.o
```

## Usage

```shell
mkdirmb -h
mkdirmb -p hello/world
mkdirmb hello
```

### Parameters

* -p (create parent directories)
* -h (print usage)
