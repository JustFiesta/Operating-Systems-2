# Resource monitor

This project is using my current knowleage of Linux programming to create manager for envs.

It works for current session only.

It can monitor resources (CPU, RAM) of given process.

Made for Linux x86_64.

## Build process

```shell
make
```

## Usage

```shell
./resource-monitor "firefox"
./resource-monitor firefox
```

## Dependencies

* gcc

## User resources

1. Libraries:

    * <unistd.h> - manage process
    * <sys/types.h>, <sys/wait.h> - monitor process
    * <stdio.h>, <stdlib.h> - in/out

2. System files:

    * /proc/[PID]/stat - CPU info
    * /proc/[PID]/status - memory info

[Linux `/proc` filesystem](https://www.kernel.org/doc/Documentation/filesystems/proc.txt)

3. POSIX docs:

    * [fork](https://man7.org/linux/man-pages/man2/fork.2.html)()
    * [execvp](https://www.man7.org/linux/man-pages/man3/exec.3p.html)()
    * [waitpid](https://man7.org/linux/man-pages/man3/waitpid.3p.html)()
