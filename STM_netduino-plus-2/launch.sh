#!/bin/sh

qemu-system-arm -M netduinoplus2 -serial stdio -kernel ../STM_netduino-plus-2_Build/arm-cortex-qemu-demo.bin -gdb tcp::1234,ipv4 -S
