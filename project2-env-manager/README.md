# Environment variable manager

This project is using my current knowleage of Linux programming to create manager for envs.

It works for current session only.

It can do env operations:

* list
* add
* remove

Made for Linux x86_64.

## Build process

```shell
make
```

## Usage

```shell
env-manager list
env-manager add NEW-VAR=content
env-manager remove NEW-VAR
```

## Used properties

* listing - [environ](https://www.man7.org/linux/man-pages/man7/environ.7.html)
* adding - [setenv](https://man7.org/linux/man-pages/man3/setenv.3.html)
