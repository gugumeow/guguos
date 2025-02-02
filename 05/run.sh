#!/bin/bash
set -xue

# QEMU 啟動路徑
QEMU=qemu-system-riscv32

# clang 路徑和編譯器標誌
# macOS 用戶：使用 CC=/opt/homebrew/opt/llvm/bin/clang  # Ubuntu 用户：使用 CC=clang
CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32 -ffreestanding -nostdlib"

# 構建內核
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c

# 啟動 QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel kernel.elf