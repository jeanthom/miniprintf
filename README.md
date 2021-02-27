# miniprintf: a printf that barely works

I needed a minimal printf for debugging stuff that didn't include a libc so I wrote this.

## Features

 - Supported specifiers: *x, X* 
 - Supported flags: *0, none*
 - Pre-defined width
 - Can escape the '%' character

## Demo

```
$ cc -Wall miniprintf.c -o miniprintf
feedbebe (%08x): feedbebe
FEEDBEBE (%08X): FEEDBEBE
0001 (%04x): 0001
01 (%02x): 01
 1 (%2x):  1
```
