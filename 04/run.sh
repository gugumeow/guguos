#!/bin/bash
set -xue

# QEMU 文件路徑
QEMU=qemu-system-riscv32

# 啟動 QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot