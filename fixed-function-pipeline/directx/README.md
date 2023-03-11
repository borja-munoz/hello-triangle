# Direct3D 11

Direct3D code based on http://www.directxtutorial.com/Lesson.aspx?lessonid=9-4-4

Windows desktop applications based on https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

Using [mingw-w64](http://mingw-w64.org/) distribution from [MSYS2](https://www.msys2.org/):

1. Install MSYS2

2. Install the mingw-64 distribution with pacman:

```shell
$ pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

3. Add the bin folder to the PATH environment variable

Tested with Geforce 9600M GT.

We need to compile with the `-municode` flag and provide the linker flags to `ld` to the Direct3D libraries.