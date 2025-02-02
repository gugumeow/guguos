> #### *This page includes content from [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/)* ####
---

# [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/)

00.Intro

01.Getting Started

02.RISC-V 101

03.Overview

04.Boot

05.Hello World!

06.C Standard Library

07.Kernel Panic

08.Exception

09.Memory Allocation

10.Process

11.Page Table

12.Application

13.User Mode

14.System Call

15.Disk I/O

16.File System

17.Outro

# Download [OpenSBI](https://github.com/riscv-software-src/opensbi)
```
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
```

# Source code structure
```
├── disk/     - File system contents
├── common.c  - Kernel/user common library: printf, memset, ...
├── common.h  - Kernel/user common library: definitions of structs and constants
├── kernel.c  - Kernel: process management, system calls, device drivers, file system
├── kernel.h  - Kernel: definitions of structs and constants
├── kernel.ld - Kernel: linker script (memory layout definition)
├── shell.c   - Command-line shell
├── user.c    - User library: functions for system calls
├── user.h    - User library: definitions of structs and constants
├── user.ld   - User: linker script (memory layout definition)
└── run.sh    - Build script
```

# QEMU monitor
```
- C-a h      print this help
- C-a x      exit emulator
- C-a s      save disk data back to file (if -snapshot)
- C-a t      toggle console timestamps
- C-a b      send break (magic sysrq)
- C-a C-a    sends C-a
- C-a c      switch between console and monitor (qemu)
    - help              more information
    - q                 quit
    - info registers    CPU registers informations
```
