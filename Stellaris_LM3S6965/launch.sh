#!/bin/sh

qemu-system-arm -M lm3s6965evb -kernel ../Stellaris_LM3S6965_Build/arm-cortex-qemu-demo.bin -gdb tcp::1234,ipv4 -S
