# ARM Cortex-M QEMU Demo

This project contains source that demostrates the use of a variety of software
I find useful in embedded projects:

 * FreeRTOS
 * CmBacktrace
 * Red Rocket Computing Backtrace
 * Newlib-nano with malloc and printf implemented
 * Selected faster C standard library routines from Newlib (non-nano) and MUSL
 * CMSIS

TODO:
 * Test b-l475e-iot01a (Cortex M4F with float)
 * Try Clang
 * Try Musl instead of Newlib, see also https://github.com/embeddedartistry/libc
 * Try C++ (find non-GPL STL), see also https://github.com/embeddedartistry/libcpp
 * Enable FORTIFY_SOURCE
 * Enable stack protector

The target device is the Stellaris LM3S6965 run from QEMU so no physical hardware is needed.

Tested with the arm-none-eabi-gcc version 13.3.rel1 provided by ARM.
