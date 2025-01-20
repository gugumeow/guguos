# [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/)

# Download [OpenSBI](https://github.com/riscv-software-src/opensbi)

```
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
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