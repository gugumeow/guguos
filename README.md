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
>6. memset 函式：主要功能是將指定記憶體區域填充為指定的值，通常用於初始化記憶體區塊。將指定記憶體區域 `buf` 的前 `n` 個位元組設置為指定的值 `c`，並返回原來的指標 `buf`。這是一個非常常用的記憶體初始化函式，尤其在嵌入式系統、操作系統開發以及其他底層編程中，經常用來清空或初始化記憶體區域。
>
>7. extern char 宣告：宣告了三個外部符號，它們通常是由鏈結器（linker）設定的記憶體區域，用於嵌入式系統或裸機程式設計中。這些符號用來指向程式中不同的記憶體區段。
>+ `__bss` 指向未初始化變數的開始位置，通常是 BSS 區段的起始地址。
>+ `__bss_end` 指向 BSS 區段的結束位置，用來確定需要初始化的記憶體範圍。
>+ `__stack_top` 指向堆疊區域的頂端位置，用來設置堆疊指標。
>+ BSS 區段的大小通常是由 `__bss_end` - `__bss` 計算出來的，這樣就能確定需要填充的範圍。
>+ 這些符號是裸機啟動程式的基本要素，通常會被用於記憶體初始化（例如清零 BSS 區段）以及設置堆疊指標等工作。
>

* 運行起來

```bash
#run.sh

#!/bin/bash
set -xue

QEMU=qemu-system-riscv32

# clang 路径和编译器标志
CC=/opt/homebrew/opt/llvm/bin/clang  # Ubuntu 用户：使用 CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fno-stack-protector -ffreestanding -nostdlib"

# 构建内核
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c

# 启动 QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel kernel.elf
```






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



