# Cross-compiling for ARM

## Part 1
* We create 2 virtual machines in QEMU. 
    * The first has **armel** (arm EABI little-endian) architecture.
    * The second has **armhf** (arm hard-float) architecture.
* We install the custom cross-compiler building toolchain `crosstool-ng`.
* We install the pre-compiled building toolchain `linaro`.
* We **compare** the two different cross-compilers by testing some exetutables in the host machine and in the above virtual machines.

*For more information about the installation steps and the results of the two different cross-compilers, go to [report](https://github.com/chrisbetze/Embedded-System-Design/blob/11f779ed38955b4ee8fa71162fccc37242edda65/Lab5/report.pdf).*

## Part 2
* Using the custom cross-compiler building toolchain `crosstool-ng` from part 1, we build a **new kernel** for Debian Operationg System.
* We add a **new system call** to the new linux kernel, that uses the function `printk` to print a phrase in the kernel log.
* The changes we made to the kernel source code are described in the report.
* The final image of the kernel is at [linux-source-3.16](https://github.com/chrisbetze/Embedded-System-Design/tree/main/Lab5/linux-source-3.16) directory.
* Finally, we write a program in C (`test.c`), which uses the new system call, in order to check its proper operation.

*The full steps of the new kernel building along with the new system call, are described in detail in the [report](https://github.com/chrisbetze/Embedded-System-Design/blob/11f779ed38955b4ee8fa71162fccc37242edda65/Lab5/report.pdf).*
