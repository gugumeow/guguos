# [OS in 1,000 Lines](https://operating-system-in-1000-lines.vercel.app/)

# QEMU monitor
- C-a h&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;print this help
- C-a x&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;exit emulator
- C-a s&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;save disk data back to file (if -snapshot)
- C-a t&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;toggle console timestamps
- C-a b&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;send break (magic sysrq)
- C-a C-a&ensp;&ensp;&ensp;&ensp;sends C-a
- C-a c&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;switch between console and monitor (qemu)
    - help              more information
    - q                 quit
    - info registers    CPU registers informations