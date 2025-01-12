There are some bugs with STM32L4xx UART in qemu.

Bugs were reported here https://gitlab.com/qemu-project/qemu/-/issues/2540

I partially fixed the issue in qemu but register access size is still a problem that has not been
fixed yet. Work was started here https://mail.gnu.org/archive/html/qemu-devel/2024-09/msg00071.html
but needs to be completed.
