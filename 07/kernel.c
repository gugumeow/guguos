// 05
#include "kernel.h"
#include "common.h"

// 04
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

// 04
extern char __bss[], __bss_end[], __stack_top[];

// 05
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

// 05
void putchar(char ch) {
    sbi_call(ch, 0, 0, 0, 0, 0, 0, 1 /* Console Putchar */);
}

// 04: 06 改定義在 common.h
/*
void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}
*/

// 04
void kernel_main(void) {

    // 04
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    // 05
    const char *s = "\nHello World!\n";
    for (int i = 0; s[i] != '\0'; i++) {
        putchar(s[i]);
    }

    // 05
    printf("\nHello %s\n", "World!!");
    printf("1 + 2 = %d, %x\n", 1 + 2, 0x1234abcd);

    // 07
    PANIC("booted!");  // 确认显示了正确的文件名和行号:PANIC: kernel.c:65: booted!
    printf("unreachable here!\n");  // 并且 PANIC 之后的处理没有执行（即，没有显示 "unreachable here!"）

    // 04
    for (;;) {
        // 05
        __asm__ __volatile__("wfi");
    }
}

// 04
__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n" // 设置栈指针
        "j kernel_main\n"       // 跳转到内核主函数
        :
        : [stack_top] "r" (__stack_top) // 将栈顶地址作为 %[stack_top] 传递
    );
}