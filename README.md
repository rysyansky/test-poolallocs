###Test project

This project contains two custom allocators for 15 and 180 bytes. Both are made with memory pool strategy for low memory use and high speed. O(1) allocation and freeing time.

```main.c``` have tests of variables. printed adress of x1 must be the same as x3.

build with gcc command for 32-bit systems:
```
gcc -m32 -std=c11 bigsmall-alloc.c main.c -o test
```