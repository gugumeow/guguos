## transister level -> digital logic level -> block diagram -> assembler -> programming language -> algorithm




## 課程內容
[影片](https://www.youtube.com/live/HiT19cs_Ys0?si=t9JkiY9_6aYeyMe6)

[教材](https://wiki.csie.ncku.edu.tw/linux/schedule)

IPO:7823

## W14: 20250522

HSA - Heteogeneous System Architecture 










## W10: 20250424 現代微處理器

2017-10-03

SI 系統整合商

MALI

Wall: Power, ILP, Memory

CPU 不能只看時脈，要看整體表現 spec.org

branch predictor machine learning

沒有強度的就是非本科，本科就應該開發有強度的東西！清楚系統架構才能寫出好的軟體！

分支預測是很難的！ARM的compiler工程師約有2百人！晶芯科技全部人數約100人！（2017）

**linux中斷處理**

CPU Timer 與 clock 的差異和用途？

top-half, bottom-half

tasklets, softirq, rtos, clock interrupt

母親節

eBPF:強大，alice也有介紹

mpstat -A, cat /proc/interrupts, NMI(no-markable interrupt), ARM FIQ

ADB with USB

Tickless Kernel

預測未來最好的方法就是創造未來

VM: Bochs, QEMU

Linux Kernel 已發展到3000萬行的規模，切勿用格物致知的方式來看原始碼，需系統化了解功能再去讀程式碼！



## W09-2: 20250418 課程

sehttp: about 1000 lines code

cserv: by jserv, about 4K lines code

創新唯一的理由是，原本做得不夠好

切換成本：process > thread > coroutine

eBPF 打造 tcp server.進一步打造 web server?



## W09-1: 20250417 futex, 伺服器開發與 Linux 核心對應的系統呼叫

server 開發： select

dynamic tracing 動態追蹤機制：分析運作中的系統，不需要把程序停下來，大部分os都做不到

eBPF tracing tool: extended BPF 動態分析的關鍵，一開始是做封包過濾。BPG 在 kernel 中執行一個 VM。

XDP: 抵禦 DDoS

安裝 simrupt

DAC

workqueue

* 00:40:00

pstree

task_struct

lsmod,  PID 0, 1, 2

* 02:00:00

Brendan blog: bpftrace v.c. BCC

CK: RSDL

Ingo: CFS 掠 CK 之美，將 RSDL 重寫，取名 CFS，CK 回歸麻醉醫師本業！讓自己有選擇性很重要！

* 03:27:00

CFS: IFS, WFQ, 無固定 time slice, 

* 03:40:00























nested IRQ























## W08-2: 20250410

測驗題說明：web server epoil

* 00:13:00

kweb，之後http3 建構在 UDP 之上，以往是 TCP 上，khttpd

namespace: from plan 9

sk: socket, skb: socket buffer

KGDB: kernel debugger

bh: bottom half

* 01:20:00

container_of, schedule_work

回顧同學作業

學店仔面試要用知識來武裝自己：youtube 學習基本知識

Brendan: CPU utilization is wrong, IPC, perf state, Xt or Xt-1, soomRV 慕尼黑大學專題自幹CPU, 

休息

* 02:02:00

測量是大學問，統計

ILP: 軟體工程師常被責備是因為對硬體的掌握度很低，導致效能不彰

cpu效能計算：給人看的 load average, 給排程器看的 pelt

Linux 註解只能用 ASCII 表示

page fault

rcu, work stealing, atomics, RMW, 生產者消費者問題， dmesg

OoOE: out of order execution

* 03:50:00






































## W08-1: 20250408

e 尤拉數：工程與數學、thermal、取樣定理

* 00:20:00

htc：自動重開機

Linux 排程器沒有 ready queue 概念：不需要的東西不做

RT system: A/V sync, 指紋辨識(biometric)

Multilevel feedback queue (MLFB), CFS

* 01:10:00

Linux 0.11 scheduler: Good code

linux/sched.c

nice: -19 ~ 20

Linux 1.2 (o) schedule: for SMP 成為主流

processor affinity

* 02:20:00 

quadcore 的 SMP 運行 linux，裡面有幾套 OS？1套

IPI: cup shoulder tap

* 02:45:00 

上帝視角

SMP v.s. AMP

amp rtos linux

spinlock

BKL: Big Kernel Lock，搬家時，所有CPU都要停止

03:00:00

O(n) schedule: this.cpu is per-cpu data/variable, 跳過 cache coherence

linux kernel version history

O(1) scheduler: Ingo, bitmap - select a task in constant time, still w/KBL

03:50:00 

O(1) - per-cpu queue


## W07: 20250404

前置作業：英文、數學、作業、測驗

開始進入 Linux 核心程式碼

老師寫的三本書

interconnect：分享記憶體資源、NUMA 架構、

* 00:43:20

休息

回答課堂問答：

tanh 泰勒展開計算，精度問題：e為底改2為底，泰勒展開只取前4項，程式無迴圈，union 節省 memcpy的copy成本、貝茲曲線、EWMA、

* 01:50:00

休息

ARM big.LITTLE: e core, p core

Linux 6.6+排程器： CFS 改成 EEVDF

ATC 小故事、worst case response time, worst case execute time

* 02:37:00

real time KVM(Linux提的虛擬化技術)

程式交易：關鍵交易要 microsecond 等級

排程器：資訊科技很多

* 02:55:00

休息

公平：是有**權重**的

川普關稅：經濟會越來越差，貢獻 Linux 核心，翻身，只能學難的事情才能脫穎而出

新教材：歐拉數

Linux 核心背後很多數學：但沒有展現出來，也沒有幾本書充分描述

程式交易裡面一堆 Linux：資訊人員懂得如何將策略寫成程式描述，且降低延遲，比別人早下單才能賺到錢。

**不可打斷**的行程：有機會動態調整優先權 bonus system，CFS -> EEDVF

OS好書：Operating Systems - Three Easy Pieces，Time sharing 即 Multiplexting

* 03:42:00

preemption(make configuration), htop, select

* 04:01:00

LAZY（不重要的事晚點一起做）

時脈4G已是極限：效能功耗問題

異質多核

cgroups:類似分組喜歡找夥伴

* 04:16:00

案例探討：Linux scheduler - a decade of wasted cores

EEVDF scheduler: 降低排程導致的延遲（早在CFS 已解決 fairness 問題），Linux 6.6 因引入，但每次更新版本的 EEDVF 都不一樣

EEMA 在 Linux 中是用在統計上


## W06: 20250327

作業說明：recursive log計算

* 00:18:00

系統軟體思維

bloom filter

測驗題說明：實作traceroute、ASLR

ARM: ROP 記憶體簽章

* 01:33:00 

統計看網路品質

理工人缺乏：英文讀寫、數學、動手及思考

* 02:20:00

休息

fast switching

**TCP/IP illustrated** 自幹 TCP/IP

遞延遲時間 + 高throughout

模組偏差談亂數分佈

* 02:43:00 

一切為檔案

* 02:55:00

Linux 可在開機網路連線後，就可存取外部資源

Windows 需開機完，才可以使用網路芳鄰的資源

03:20:00 

diskless linux

DRBL

例外：socket, pipe

一切都是檔案：pipe, plan 9

* 03:48:00 

BSD 1,2,3,4,4.1,4.2,4.3,4.4(final)

* 04:10:00





## W05: 20250320

作業：紅黑樹實作

* 01:22:00

線上 Meeting

物理隨機分佈：指數函數e

* 01:45:00

locking

* 02:44:00 

git rebase

linked list sort 作業

* 03:01:00

list sort:指標、成本分析、效能分析

2024同學成果：Futex - Fast Mutex

* 03.47:00 

生命攸關系統





## W03作業

#### 00:36:00 

共筆



## W00: 20250218

目的是**翻身**
#### 00:45:00
教學是因為有學生需要
#### 01:15:00
解決**真實世界**的問題
#### 01:56:00
軟體造成的災難
#### 02:20:00
閱讀**規格說明書**
#### 03:04:00
學習Linux所需**背景知識**

## W01: 20250220

#### 00:16:30
每週上課隨堂測驗：快速看懂C語言程式碼

第一週作業：看懂題目至少三天202502220624)

[CPU land](https://cpu.land/)

[EWMA](https://zh.m.wikipedia.org/wiki/%E7%A7%BB%E5%8B%95%E5%B9%B3%E5%9D%87)

用字遣詞要正確：天演論-嚴復

#### 01:10:00 

浮點數(FP) > Rounding Error > Fixed-Point Number

IEEE 754(1985)

Linux 避免使用浮點數暫存器

Mado(日文的「視窗」)

#### 01:30:00

Linked List: &(*p)

記憶體管理：這學期重視

Power 2

#### 02:00:00

**W01 HW**

lab0: [CMU junior starts](https://www.andrew.cmu.edu/course/18-613/labs/QuickStart-lab0.pdf)

ideas: 是學習到期末該會的底線

[拜占庭將軍問題](https://zh.m.wikipedia.org/zh-tw/%E6%8B%9C%E5%8D%A0%E5%BA%AD%E5%B0%86%E5%86%9B%E9%97%AE%E9%A2%98)、[Sparse](https://en.m.wikipedia.org/wiki/Sparse)、sanitizer(適量使用)

#### 03:10:00

Good GitHub commit message

CONTRIBUTING.md：務必詳閱

#### 03:41:00 

lab0


## W02: 20250225

評分修改說明

#### 00:05:00

良好溝通、linux 的 hash table

#### 00:22:00

hlist, hash table(Golden Ratio)

ThreadX v.6.4.2

#### 01:12:30

W01 HW

記憶體管理

#### 01:34:00 

[sqrt](https://github.com/torvalds/linux/blob/99fa936e8e4f117d62f229003c9799686f74cebc/lib/math/int_sqrt.c#L20): 無乘法，僅用 bitwise, +-, 迴圈

使用LLM需先有Domain Knowledge

#### 03:37:00

檢討W01作業
bug on
bit field


#### 03:52:00 

## W03: 20250306

作業說明
auto-Tetris

#### 00:15:00 

排程器原理

coroutine

排程器 100行

第三次測驗

#### 01:13:00 

man mmap

preempty

ipc

addres kling: ladybird

同學貢獻

Llama, ollama

long int: mpi

no division

c preproceesor

#### 03:45:00

