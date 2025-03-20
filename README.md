## License & Copyright

*This repository includes content from [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/)
which is licensed under the **MIT License**.*

According to the MIT License, you are free to use, modify, and distribute the content, provided that the original copyright notice is included.

*Original Copyright:*

© [OS in 1,000 Lines](https://github.com/nuta/operating-system-in-1000-lines/blob/main/LICENCE.md)  
Licensed under the **MIT License** – see the [MIT License](https://opensource.org/license/MIT) file for details.

*Modifications in This Project:*

Additional modifications and contributions in this repository are also released under the **MIT License**.

---

# [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/) 筆記

## 00.Intro 簡介

* Linux 0.01 版只有 8413 行程式碼。
* 用 1000 行 C 語言實作基礎的上下文切換、分頁、使用者模式、命令列 shell、硬碟驅動、文件讀寫。
* 書 CC BY 4.0 license 協議，程式碼 MIT license 協議。

## 01.Getting Started 入門

* 僅筆記 Ubuntu 用法。
* 安裝所需套件:
```bash
sudo apt update 
sudo apt install -y clang llvm lld qemu-system-riscv32 curl
```
>1.-y：自動回答「是」。
>2.clang：LLVM 編譯器前端，編譯 C/C++ 原始碼，生成中間表示（IR）或可執行檔。
>3.llvm：LLVM 基礎架構，與 Clang 結合使用進行程式編譯和優化。
>4.lld：LLVM 的程式鏈接器（Linker）。
>5.qemu-system-riscv32：QEMU 的一個子程式，專門用來模擬 RISC-V 32 位元系統。
>6.curl：命令列工具，常用於從伺服器下載檔案或發送 HTTP 請求。



* 下載 OpenSBI（可理解成是 PC 的 BIOS/UEFI）
```bash
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
```
* 新增 Git 的忽略清單文件：.gitignore
```
/disk/*
!/disk/.gitkeep
*.map
*.tar
*.o
*.elf
*.bin
*.log
*.pcap
```



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
