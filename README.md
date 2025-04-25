# retvalwrap
A simple wrapper to obtain and print return value of a program.

## How to use?
In order to use just specify a name of a program you want to run and arguments it needs.
Here is an example:

```
> retvalwrap echo "hello world"



hello world

Program exited with status 0
```

> [!NOTE]
> Due to functions that are used in this program, only 8 least significant bits of return value are returned, so the **range of possible return value is [0..255]**

## Compilation
Compilation is as easy as:

```
gcc -o retvalwrap retvalwrap.c
```

> [!WARNING]
> This software is not finished, there may be bugs, use on your own risk 
