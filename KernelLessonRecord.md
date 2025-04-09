## 課程內容
[影片](https://www.youtube.com/live/HiT19cs_Ys0?si=t9JkiY9_6aYeyMe6)

[教材](https://wiki.csie.ncku.edu.tw/linux/schedule)


## W08-1: 20250408

e 尤拉數：工程與數學、thermal、取樣定理

* 00:20:00

htc

Linux 排程器沒有 ready queue 概念：不需要的東西不做

RT system: A/V sync, 指紋辨識(biometric)

Multilevel feedback queue (MLFB), CFS

* 01:10:00

















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

