#!/bin/sh

qemu-system-arm -M lm3s6965evb -kernel Debug/arm-cortex-qemu-demo.elf -gdb tcp::1234,ipv4 -S
