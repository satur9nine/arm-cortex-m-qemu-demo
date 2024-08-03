#!/bin/sh

qemu-system-arm -M lm3s6965evb -kernel Debug/RTOSDemo.elf -gdb tcp::1234,ipv4 -S
