# ARM Cortex-M QEMU Demo

This project contains source that demostrates the use of a variety of software
and techniques I find useful in embedded projects. The projects run in qemu.

 * FreeRTOS
 * CmBacktrace
 * Red Rocket Computing Backtrace
 * Newlib-nano with malloc and printf implemented
 * Selected faster C standard library routines from Newlib (non-nano) and MUSL
 * CMSIS
 * FORTIFY_SOURCE (level 3)
 * Stack protector (strong)

TODO:
 * Try Clang
 * Try Musl instead of Newlib, possibly https://github.com/embeddedartistry/libc
 * Try C++ (find non-GPL STL), possibly https://github.com/embeddedartistry/libcpp
 * Enable MMU
 * Add mbedTLS

Tested with the arm-none-eabi-gcc version 13.3.rel1 provided by ARM.

The Eclipse CDT project file is checked in and was used to generate the 
makefiles.

There are `launch.sh` scripts to run each project in qemu and wait for the
debugger. Eclipse can be used to interactively debug.

There is a Docker container that can be used to run a very recent version of
qemu since most linux distros are behind.
