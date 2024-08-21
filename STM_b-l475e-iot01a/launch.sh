#!/bin/sh

qemu-system-arm -M b-l475e-iot01a -serial stdio -kernel ../STM_b-l475e-iot01a_Build/arm-cortex-qemu-demo.bin -gdb tcp::1234,ipv4 -S
