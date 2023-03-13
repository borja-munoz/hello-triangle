# Direct3D 11

Direct3D code based on https://antongerdelan.net/opengl/d3d11.html and https://olster1.github.io/direct3d_11_part3.html

Windows desktop applications based on https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

Using [mingw-w64](http://mingw-w64.org/) distribution from [MSYS2](https://www.msys2.org/):

1. Install MSYS2

2. Install the mingw-64 distribution with pacman:

```shell
$ pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

3. Add the bin folder to the PATH environment variable

Tested with Geforce 9600M GT that only supports Direct3D feature level 10_0 (shader model 4.0). It should work with Direct3D 11 (shader model 5.0) as well.

We need to compile with the `-municode` flag and provide the linker flags to `ld` to the Direct3D libraries.