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

## [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/) 筆記


### 00.Intro 簡介

* Linux 0.01 版只有 8413 行程式碼。
* 用 1000 行 C 語言實作基礎的上下文切換、分頁、使用者模式、命令列 shell、硬碟驅動、文件讀寫。
* 書 CC BY 4.0 license 協議，程式碼 MIT license 協議。

### 01.Getting Started 入門

* 僅筆記 Ubuntu 用法。
* 安裝所需套件:
>```bash
>sudo apt update 
>sudo apt install -y clang llvm lld qemu-system-riscv32 curl
>```
>1. -y：自動回答「是」。
>
>2. clang：LLVM 編譯器前端，編譯 C/C++ 原始碼，生成中間表示（IR）或可執行檔。
>
>3. llvm：LLVM 基礎架構，與 Clang 結合使用進行程式編譯和優化。
>
>4. lld：LLVM 的程式鏈接器（Linker）。
>
>5. qemu-system-riscv32：QEMU 的一個子程式，專門用來模擬 RISC-V 32 位元系統。
>
>6. curl：命令列工具，常用於從伺服器下載檔案或發送 HTTP 請求。
>


* 下載 OpenSBI（可理解成是 PC 的 BIOS/UEFI）
>```bash
>curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
>```
>

* 新增 Git 的忽略清單文件：.gitignore
>```
>/disk/*
>!/disk/.gitkeep
>*.map
>*.tar
>*.o
>*.elf
>*.bin
>*.log
>*.pcap
>```
>

### 02.RISC-V 101

* OS 隱藏了不同 CPU 之間的差異。
* RISC-V CPU 的特色：
>1. 規範簡單，適合新手。
>
>2. 近年流行
>
>3. 規範中有詳細紀錄設計決策
>

* QEMU 虛擬機：
>1. 模擬真實設備。
>
>2. 免費。
>
>3. 可查找原始碼來找出問題。
>

* RISC-V assembly 101
>1. RISC-V 是一種 ISA（指令集架構），定義 CPU 可執行的指令
>
>2. 可使用 C 語言，再使用編譯器編譯成 RISC-V 組合語言。
>
>3. 暫存器：
>
>4. 記憶體存取：lw、sw
>
>5. 分支：bnez、beq
>
>6. 函數呼叫：jal
>
>7. 堆疊：
>

* Compiler Explorer
>1. 線上編譯器，學習組合語言的實用工具。
>
>2. 編寫 C 語言程式碼，會顯示相對應的組合語言。
>
>3. 預設使用 x86-64 CPU，可指定 RISC-V rv32gc clang (trunk) 輸出 32 位元的 RISC-V 組合語言。
>
>4. 編譯選項中可指定優化選項：-O0（關閉優化）、-O2（二級優化）
>

* CPU 模式：
>1. M-mode：OpenSBI 運行的模式。
>
>2. S-mode：核心模式。
>
>3. U-mode：應用程式模式。
>

* 特權指令：csrr、csrw、csrrw、sret、sfence.vma

* 行內組語（Inline assembly）：低階組合語言內嵌在高階語言原始碼中，用於增加執行效率、執行處理器特有指令、執行系統呼叫。

### 03.Overview

* 目錄結構：
>```
>├── disk/     - 文件系统内容
>├── common.c  - 内核/用户共用库：printf、memset 等
>├── common.h  - 内核/用户共用库：结构体和常量的定义
>├── kernel.c  - 内核：进程管理、系统调用、设备驱动、文件系统
>├── kernel.h  - 内核：结构体和常量的定义
>├── kernel.ld - 内核：链接器脚本（内存布局定义）
>├── shell.c   - 命令行 shell
>├── user.c    - 用户库：系统调用函数
>├── user.h    - 用户库：结构体和常量的定义
>├── user.ld   - 用户：链接器脚本（内存布局定义）
>└── run.sh    - 构建脚本
>```
>

### 04.Boot 引導

* 啟動 OpenSBI：
>1. 建立 Shell 腳本：run.sh
>```
>touch run.sh
>chmod +x run.sh
>```
>
>2. 編輯腳本：
>```
>#!/bin/bash
>set -xue
>
># QEMU 文件路徑
>QEMU=qemu-system-riscv32
>
># 啟動 QEMU
>$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot
>```
>+ `set -xue` 適合用在需要嚴格錯誤檢查的 Bash 腳本，確保：
>>(1). 每個命令執行前都可見（方便除錯）。
>>
>>(2). 避免使用未定義變數。
>>
>>(3). 當命令失敗時立即停止，避免錯誤擴大影響。
>>
>+ `#!` Shebang，稱為 “hash-bang” 或 “sharp-bang”，它的作用是指定該腳本應該由哪個解釋器（interpreter）來執行。
>
>
>3. 執行腳本：
>```
>$ ./run.sh
>```
>

* QEMU monitor：按 Ctrl+A 進入
>```
>C-a h    打印此帮助
>C-a x    退出模拟器
>C-a s    将磁盘数据保存回文件（如果使用 -snapshot）
>C-a t    切换控制台时间戳
>C-a b    发送中断（magic sysrq）
>C-a c    在控制台和监视器之间切换
>C-a C-a  发送 C-a
>info registers 查看 CPU 暫存器內容
>```
>

* 連接腳本（Linkder Script）：定義可執行檔記憶體布局的文件。
>```kernel.ld
>// kernel.ld
>
>ENTRY(boot)
>
>SECTIONS {
>    . = 0x80200000;
>
>    .text :{
>        KEEP(*(.text.boot));
>        *(.text .text.*);
>    }
>
>    .rodata : ALIGN(4) {
>        *(.rodata .rodata.*);
>    }
>
>    .data : ALIGN(4) {
>        *(.data .data.*);
>    }
>
>    .bss : ALIGN(4) {
>        __bss = .;
>        *(.bss .bss.* .sbss .sbss.*);
>        __bss_end = .;
>    }
>
>    . = ALIGN(4);
>    . += 128 * 1024; /* 128KB */
>    __stack_top = .;
>}
>```
>
>1. kernel.ld：GNU linker script，用來定義 kernel 映像在記憶體中的佈局。即各段 (section) 的起始地址、排列順序及其記憶體範圍。如下圖所示：
>
>>| 地址 | 區段 | 內容 |
>>|---|---|---|
>>| 0x802xxxxx | __stack_top | 堆疊頂端               |
>>|            | (保留區)   | 128KB 堆疊區域         |
>>| 0x802xxxxx | .bss      | 未初始化變數 (預設 0)  |
>>| 0x802xxxxx | .data     | 已初始化變數           |
>>| 0x802xxxxx | .rodata   | 常數、只讀資料         |
>>| 0x80200000 | .text     | 程式碼 (boot, main)    |
>>
>
>2. ENTRY(boot)：指定程式的入口點，即kernel 啟動位置。
>
>3. .text：存放程式碼，從 0x80200000 開始。
>
>4. .rodata：存放唯讀資料 (常數、字串表)，對齊 4 bytes。
>
>5. .data：存放已初始化的變數 (全域、靜態變數)。
>
>6. .bss：存放未初始化的變數，kernel 會自動清零。
>
>7. __stack_top：設定堆疊的頂端，保留 128KB 記憶體給堆疊。
>

* 最小核心：

>```C
>
>// kernel.c
>typedef unsigned char uint8_t;
>typedef unsigned int uint32_t;
>typedef uint32_t size_t;
>
>extern char __bss[], __bss_end[], __stack_top[];
>
>void *memset(void *buf, char c, size_t n) {
>    uint8_t *p = (uint8_t *) buf;
>    while (n--)
>        *p++ = c;
>    return buf;
>}
>
>void kernel_main(void) {
>    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);
>
>    for (;;);
>}
>
>__attribute__((section(".text.boot")))
>__attribute__((naked))
>void boot(void) {
>    __asm__ __volatile__(
>        "mv sp, %[stack_top]\n" // 設定堆疊指標
>        "j kernel_main\n"       // 跳轉到核心主函式 kernel_main
>        :
>        : [stack_top] "r" (__stack_top) // 將堆疊頂端地址作為 %[stack_top] 傳遞
>    );
>}
>```
>1. kernel 入口：由連結腳本檔`kernel.ld`指定入口函式名稱為 boot `ENTRY(boot)`。
>
>2. boot 函式：`__asm__ __volatile__(...)`，其中`__asm__` (或 `asm`) 表示這是內嵌組合語法。`__volatile__`告訴編譯器不要對這段組合語優化，確保它一定會執行，避免編譯器因優化而移除或改變指令順序。`mv sp, %[stack_top]`設定堆疊指標（sp）為連接腳本中所定義的堆疊區域的結束地址。這是因為啟動時處理器的
>
>3. GCC 內嵌組合語法(`__asm__`)基本格式：
>>```c
>>__asm__ __volatile__(
>>    "指令"    // 組合語言指令
>>    : "約束1"(輸出操作數)    // 沒有輸出操作數時，留空白
>>    : "約束2"(輸入操作數)    // 表示變數 `__stack_top` 會被存入某個暫存器 `r`
>>    : "約束3"(損壞的暫存器)    // 可選。沒有需要標示的破壞暫存器，所以省略
>>);
>>```
>4. boot 函式屬性：
>+ `__attribute__((naked))` 屬性告訴編譯器不要在函式前後生成不必要的代碼。例如不要自動產生函式的進入 (prologue) 和返回 (epilogue) 代碼，只保留函式內部的指令。
>+ `__attribute__((section(".text.boot")))` 屬性控制函式在連接器腳本中的放置。在 linker script (連結腳本) 中，必須定義 .text.boot，這樣 boot_function() 就會被放到 .text.boot 這個記憶體區段中，而不是一般的 .text 區段。因 OpenSBI 簡單地跳轉到 0x80200000 而不知道入口點，所以需要將 boot 函式放在 0x80200000 位址。
>
>5. kernel_main 函式：`kernel_main` 是核心主函式。首先，它使用 `memset` 函式清除 BSS 區段的記憶體區域，將其設置為 0，這是因為 BSS 段中儲存的是未初始化的全域變數。接著，`for (;;);` 則進入一個無窮迴圈，這表示內核進入了靜止狀態，通常此處會進行後續的初始化或等待中斷。
>
>6. memset 函式：主要功能是將指定記憶體區域填充為指定的值，通常用於初始化記憶體區塊。將指定記憶體區域 `buf` 的前 `n` 個位元組設置為指定的值 `c`，並返回原來的指標 `buf`。
>+ 這是一個非常常用的記憶體初始化函式，尤其在嵌入式系統、操作系統開發以及其他底層編程中，經常用來清空或初始化記憶體區域。
>+ memset 回傳傳入的指標主要是出於設計上的一致性和提供函式鏈式調用的可能性。雖然在 C 語言中，函式鏈式調用並不常見，但這樣的設計為開發者提供了更多的靈活性。在實務應用中，是否利用其回傳值，取決於具體的程式設計需求。
>
>8. extern char 宣告：宣告了三個外部符號，它們通常是由鏈結器（linker）設定的記憶體區域，用於嵌入式系統或裸機程式設計中。這些符號用來指向程式中不同的記憶體區段。
>+ `__bss` 指向未初始化變數的開始位置，通常是 BSS 區段的起始地址。
>+ `__bss_end` 指向 BSS 區段的結束位置，用來確定需要初始化的記憶體範圍。
>+ `__stack_top` 指向堆疊區域的頂端位置，用來設置堆疊指標。
>+ BSS 區段的大小通常是由 `__bss_end` - `__bss` 計算出來的，這樣就能確定需要填充的範圍。
>+ 這些符號是裸機啟動程式的基本要素，通常會被用於記憶體初始化（例如清零 BSS 區段）以及設置堆疊指標等工作。
>

* 運行起來：`./run.sh`

>```bash
># run.sh
>
>#!/bin/bash
>set -xue
>
>QEMU=qemu-system-riscv32
>
># clang 路徑和編譯器標誌
>CC=/opt/homebrew/opt/llvm/bin/clang  # Ubuntu 用户：使用 CC=clang
>CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fno-stack-protector -ffreestanding -nostdlib"
>
># 構建核心
>$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
>    kernel.c
>
># 啟動 QEMU
>$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
>    -kernel kernel.elf
>```
>
>1. clang選項（即 CFLAGS 變數）：
>+ `-std=c11`	使用 C11。
>+ `-O2` 启用优化以生成高效的机器代码。
>+ `-g3` 生成最大量的调试信息。
>+ `-Wall` 启用主要警告。
>+ `-Wextra` 启用额外警告。
>+ `--target=riscv32-unknown-elf` 编译为 32 位 RISC-V。
>+ `-fno-stack-protector` 禁用栈保护功能（#31 参考)
>+ `-ffreestanding` 不使用主机环境（你的开发环境）的标准库。
>+ `-nostdlib` 不链接标准库。
>+ `-Wl,-Tkernel.ld	指定链接器脚本。
>+ `-Wl,-Map=kernel.map	输出映射文件（链接器

* 第一次核心除錯

> 當你執行 `run.sh` 時，核心會進入無限迴圈。沒有任何跡象顯示核心正在正常運作。但別擔心，這在底層開發中是很常見的情況！這正是 QEMU 除錯功能派上用場的時候。
> 若要取得更多關於 CPU 暫存器的資訊，請開啟 QEMU 監控器並執行 `info registers` 指令：
> ```
>QEMU 8.0.2 monitor - type 'help' for more information
>(qemu) info registers
>
>CPU#0
> V      =   0
> pc       80200014  ← 将要执行的指令的地址（程序计数器）
> ...
> x0/zero  00000000 x1/ra    8000a084 x2/sp    80220018 x3/gp    00000000  ← 每个寄存器的值
> x4/tp    80033000 x5/t0    00000001 x6/t1    00000002 x7/t2    00000000
> x8/s0    80032f50 x9/s1    00000001 x10/a0   80220018 x11/a1   87e00000
> x12/a2   00000007 x13/a3   00000019 x14/a4   00000000 x15/a5   00000001
> x16/a6   00000001 x17/a7   00000005 x18/s2   80200000 x19/s3   00000000
> x20/s4   87e00000 x21/s5   00000000 x22/s6   80006800 x23/s7   8001c020
> x24/s8   00002000 x25/s9   8002b4e4 x26/s10  00000000 x27/s11  00000000
> x28/t3   616d6569 x29/t4   8001a5a1 x30/t5   000000b4 x31/t6   00000000
> ```
>
>使用反編譯器（llvm-objdump）來確定具體的程式行：
>
>```
>$ llvm-objdump -d kernel.elf
>
>kernel.elf:     file format elf32-littleriscv
>
>Disassembly of section .text:
>
>80200000 <boot>:  ← boot 函数
>80200000: 37 05 22 80   lui     a0, 524832
>80200004: 13 05 85 01   addi    a0, a0, 24
>80200008: 2a 81         mv      sp, a0
>8020000a: 6f 00 60 00   j       0x80200010 <kernel_main>
>8020000e: 00 00         unimp
>
>80200010 <kernel_main>:  ← kernel_main 函数
>80200010: 73 00 50 10   wfi
>80200014: f5 bf         j       0x80200010 <kernel_main>  ← pc 在这里
>```
>
> 查看 kernel.map 文件，檢視鏈結器放置 __stack_top 的位址；
> 
>```
>     VMA      LMA     Size Align Out     In      Symbol
>       0        0 80200000     1 . = 0x80200000
>80200000 80200000       16     4 .text
>...
>80200016 80200016        2     1 . = ALIGN ( 4 )
>80200018 80200018    20000     1 . += 128 * 1024
>80220018 80220018        0     1 __stack_top = .
>```


也可以使用 llvm-nm 检查函数/变量的地址：
```
$ llvm-nm kernel.elf
80200010 t .LBB0_1
00000000 N .Lline_table_start0
80220018 T __stack_top
80200000 T boot
80200010 T kernel_main
```

第一列是它们被放置的地址（VMA）。你可以看到 __stack_top 被放置在 0x80220018。这确认了栈指针在 boot 函数中被正确设置。漂亮！

随着程序的运行，info registers 的结果会发生变化。如果你想暂时停止模拟，可以在 QEMU 监视器中使用 stop 命令：

```
(qemu) stop             ← 进程停止
(qemu) info registers   ← 你可以观察停止时的状态
(qemu) cont             ← 进程继续
```

### 05.Hello World!

* 向 SBI 說 hello

SBI 是「作業系统的 API」。要調用 SBI 的功能，我们使用 ecall 指令：

```
#include "kernel.h"

extern char __bss[], __bss_end[], __stack_top[];

struct sbiret sbi_call(long arg0, long arg1, long arg2, long arg3, long arg4,
                       long arg5, long fid, long eid) {
    register long a0 __asm__("a0") = arg0;
    register long a1 __asm__("a1") = arg1;
    register long a2 __asm__("a2") = arg2;
    register long a3 __asm__("a3") = arg3;
    register long a4 __asm__("a4") = arg4;
    register long a5 __asm__("a5") = arg5;
    register long a6 __asm__("a6") = fid;
    register long a7 __asm__("a7") = eid;

    __asm__ __volatile__("ecall"
                         : "=r"(a0), "=r"(a1)
                         : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5),
                           "r"(a6), "r"(a7)
                         : "memory");
    return (struct sbiret){.error = a0, .value = a1};
}

void putchar(char ch) {
    sbi_call(ch, 0, 0, 0, 0, 0, 0, 1 /* Console Putchar */);
}

void kernel_main(void) {
    const char *s = "\n\nHello World!\n";
    for (int i = 0; s[i] != '\0'; i++) {
        putchar(s[i]);
    }

    for (;;) {
        __asm__ __volatile__("wfi");
    }
}
```

同時創建一個新的 kernel.h 檔案並定義返回值結構：
```
#pragma once

struct sbiret {
    long error;
    long value;
};
```

以下是 printf 函式的實作：

```
#include "common.h"

void putchar(char ch);

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; // 跳过 '%'
            switch (*fmt) { // 读取下一个字符
                case '\0': // 当 '%' 作为格式字符串的末尾
                    putchar('%');
                    goto end;
                case '%': // 打印 '%'
                    putchar('%');
                    break;
                case 's': { // 打印以 NULL 结尾的字符串
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': { // 以十进制打印整型
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value; // https://github.com/nuta/operating-system-in-1000-lines/issues/64
                    if (value < 0) {
                        putchar('-');
                        magnitude = -magnitude;
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9)
                        divisor *= 10;

                    while (divisor > 0) {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }

                    break;
                }
                case 'x': { // 以十六进制打印整型
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                }
            }
        } else {
            putchar(*fmt);
        }

        fmt++;
    }

end:
    va_end(vargs);
}
```

來自核心的"Hello World"：
```
#include "kernel.h"
#include "common.h"

void kernel_main(void) {
    printf("\n\nHello %s\n", "World!");
    printf("1 + 2 = %d, %x\n", 1 + 2, 0x1234abcd);

    for (;;) {
        __asm__ __volatile__("wfi");
    }
}
```

將 common.c 加到編譯目標：
```
run.sh

$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c common.c
```

運行它，將會看到以下所示 Hello World! 和 1 + 2 = 3, 1234abcd：

```
$ ./run.sh

Hello World!
1 + 2 = 3, 1234abcd
```

強大的盟友「printf 除錯」已經加入你的作業系統了！


06.C Standard Library

本章從頭開始實現 C 標準函式庫的基本類型記憶體操作。

```
typedef int bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint32_t size_t;
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

#define true  1
#define false 0
#define NULL  ((void *) 0)
#define align_up(value, align)   __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)
#define offsetof(type, member)   __builtin_offsetof(type, member)
#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg

void *memset(void *buf, char c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
void printf(const char *fmt, ...);
```










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




| 位元數 (bits) | 可位址單元數 (2ⁿ)             | 對應容量       |
|---------------|-------------------------------|----------------|
| 1             | 2                             | 2 Bytes        |
| 2             | 4                             | 4 Bytes        |
| 3             | 8                             | 8 Bytes        |
| 4             | 16                            | 16 Bytes       |
| 5             | 32                            | 32 Bytes       |
| 6             | 64                            | 64 Bytes       |
| 7             | 128                           | 128 Bytes      |
| 8             | 256                           | 256 Bytes      |
| 9             | 512                           | 512 Bytes      |
| 10            | 1,024                         | 1 KB           |
| 11            | 2,048                         | 2 KB           |
| 12            | 4,096                         | 4 KB           |
| 13            | 8,192                         | 8 KB           |
| 14            | 16,384                        | 16 KB          |
| 15            | 32,768                        | 32 KB          |
| 16            | 65,536                        | 64 KB          |
| 17            | 131,072                       | 128 KB         |
| 18            | 262,144                       | 256 KB         |
| 19            | 524,288                       | 512 KB         |
| 20            | 1,048,576                     | 1 MB           |
| 21            | 2,097,152                     | 2 MB           |
| 22            | 4,194,304                     | 4 MB           |
| 23            | 8,388,608                     | 8 MB           |
| 24            | 16,777,216                    | 16 MB          |
| 25            | 33,554,432                    | 32 MB          |
| 26            | 67,108,864                    | 64 MB          |
| 27            | 134,217,728                   | 128 MB         |
| 28            | 268,435,456                   | 256 MB         |
| 29            | 536,870,912                   | 512 MB         |
| 30            | 1,073,741,824                 | 1 GB           |
| 31            | 2,147,483,648                 | 2 GB           |
| 32            | 4,294,967,296                 | 4 GB           |
| 33            | 8,589,934,592                 | 8 GB           |
| 34            | 17,179,869,184                | 16 GB          |
| 35            | 34,359,738,368                | 32 GB          |
| 36            | 68,719,476,736                | 64 GB          |
| 37            | 137,438,953,472               | 128 GB         |
| 38            | 274,877,906,944               | 256 GB         |
| 39            | 549,755,813,888               | 512 GB         |
| 40            | 1,099,511,627,776             | 1 TB           |
| 41            | 2,199,023,255,552             | 2 TB           |
| 42            | 4,398,046,511,104             | 4 TB           |
| 43            | 8,796,093,022,208             | 8 TB           |
| 44            | 17,592,186,044,416            | 16 TB          |
| 45            | 35,184,372,088,832            | 32 TB          |
| 46            | 70,368,744,177,664            | 64 TB          |
| 47            | 140,737,488,355,328           | 128 TB         |
| 48            | 281,474,976,710,656           | 256 TB         |
| 49            | 562,949,953,421,312           | 512 TB         |
| 50            | 1,125,899,906,842,624         | 1 PB           |
| 51            | 2,251,799,813,685,248         | 2 PB           |
| 52            | 4,503,599,627,370,496         | 4 PB           |
| 53            | 9,007,199,254,740,992         | 8 PB           |
| 54            | 18,014,398,509,481,984        | 16 PB          |
| 55            | 36,028,797,018,963,968        | 32 PB          |
| 56            | 72,057,594,037,927,936        | 64 PB          |
| 57            | 144,115,188,075,855,872       | 128 PB         |
| 58            | 288,230,376,151,711,744       | 256 PB         |
| 59            | 576,460,752,303,423,488       | 512 PB         |
| 60            | 1,152,921,504,606,846,976     | 1 EB           |
| 61            | 2,305,843,009,213,693,952     | 2 EB           |
| 62            | 4,611,686,018,427,387,904     | 4 EB           |
| 63            | 9,223,372,036,854,775,808     | 8 EB           |
| 64            | 18,446,744,073,709,551,616    | 16 EB          |

