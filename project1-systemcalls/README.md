# Syscalls project

This project is using system calls to create simple mkdir program.

They were made for UNIX x86_64.

## Ports

These program can be compiled from:

* C

```shell
gcc mkdir.c -o mkdir
```

* NASM

```shell
nasm -f elf64 -o mkdir.o mkdir.asm
ld -o mkdir mkdir.o
```

## Usage

```shell
mkdir -h
mkdir -p hello/world
mkdir hello
```

### Parameters

* -p (create parent directories)
* -h (print usage)
