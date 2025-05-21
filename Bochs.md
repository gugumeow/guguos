## Bochs 簡介

Bochs 是一個開源的 IA-32 (x86) 模擬器，用來模擬 PC 系統，非常適合用於作業系統教學與開發。

## 最簡單的 Bochs 範例：只能顯示「Hello World!」

### Bochs 基本檔案結構

```
/ my_project
├── hello.asm
├── boot.img
├── bochsrc.txt
├── bochslog.txt
└── build.sh
```

### 安裝 bochs, nasm（組譯器）

```bash
sudo apt install bochs bochs-x nasm

```

### 編寫組合語言程式：hello.asm

1.	開機時載入這段程式。

2.	把 "Hello World!" 顯示在螢幕上。

3.	然後停在那裡不動。

```asm
; 告訴組譯器我們要使用的是 16 位元模式（real mode），這是 x86 CPU 開機時的模式。寫 boot sector 的程式幾乎一定要是 16-bit。
[BITS 16]

; ORG 是「原點（origin）」的意思。BIOS 會把 boot sector 載入到記憶體位置 0x7C00，這一行讓程式知道它是從這個位置開始執行。
[ORG 0x7C00]

; 標記一個程式的開始位置，方便跳轉或閱讀（其實這裡不是強制必要，僅作為方便用的標籤）。
start:
    ; 清除螢幕（可略）
    mov ah, 0x0E

    ; 把字串的位置（記憶體位址）放到 SI 暫存器，SI 會被 lodsb 使用。
    mov si, msg

; 一個迴圈開始點（label），方便之後用 jmp 回到這裡。
.next_char:
    ; LOaD String Byte：從 SI 所指的位置讀一個 byte（也就是一個字元）到 AL 暫存器，然後 SI 自動加一。
    lodsb

    ; 比較剛剛讀到的字元是否為 0（代表字串結束，因為我們用 NULL 結尾）。
    cmp al, 0

    ; 如果等於 0，跳到 hang（程式結束）。
    je hang

    ; 呼叫 BIOS 的 0x10 中斷，使用剛剛設定的 AH=0x0E 模式，來顯示 AL 中的字元。AH=0x0E 指的是「TTY 模式的文字輸出功能」，會把 AL 的字元顯示在畫面上。
    int 0x10

    ; 回到 .next_char，繼續下一個字元。
    jmp .next_char

; 顯示完字串後會跳到這裡，這是程式的「停止點」。
hang:

    ; 關閉中斷，避免外部中斷影響（乾淨停機）。

    ; Halt：讓 CPU 進入停止狀態。
    cli
    hlt
    ; $ 表示「目前位址」，jmp $ 是無限迴圈，CPU 停在這裡不再執行其他東西。
    jmp $

; db 是「定義 byte」。這一行建立了一串字元：「Hello World!」，最後用 0 作為結尾。
msg db 'Hello World!', 0

; times 是 NASM 的指令，用來重複。($ - $$) 是目前程式碼已經用了多少位元組（byte）。這行會填充 0 到總共達到 510 個 bytes。boot sector 必須是 512 bytes，所以這裡填滿剩下的空間。
times 510-($-$$) db 0  ; 填滿到 510 bytes

; 引導扇區的魔術數字（magic number），必須是 0xAA55。BIOS 開機時會檢查第 511–512 bytes 是不是這個值，來決定是否可開機。
dw 0xAA55

```

### 組譯產生開機映像檔：boot.img

```bash
nasm -f bin hello.asm -o boot.img
```

### 建立 Bochs 組態檔：bochsrc.txt

```txt
megs: 32
romimage: file=./BIOS-bochs-latest
vgaromimage: file=./VGABIOS-lgpl-latest
floppya: 1_44=boot.img, status=inserted
boot: a
log: bochslog.txt
display_library: x
```

注意：參數 romimage 及 vgaromimage 分別要設定 BIOS-bochs-latest 及 VGABIOS-lgpl-latest 檔案的目錄，此二個檔案可從 github 下載，解壓縮後會位於 /BIOS/ 資料夾中。

## 啟動 Bochs：

```bash
bochs -f bochsrc.txt
```

注意：執行後會另開 Bochs 視窗，整個是黑畫面。在原 bash 中輸入指令 c，會繼續執行，就會在 Bochs 視窗中顯示「Hello World!」。常用 Bochs 指令如下！

## Bochs 常用指令：

| 指令       | 說明                   |
| ---------- | ----------------------------- |
| `c`        | 繼續執行（Continue）                |
| `s`        | 單步執行一條指令（Step into）           |
| `v`        | 單步執行並跳過呼叫（Step over）          |
| `b [addr]` | 設定斷點，例如 `b 0x7c00`            |
| `bl`       | 列出所有斷點（breakpoint list）       |
| `bd [n]`   | 禁用第 n 個斷點（breakpoint disable） |
| `be [n]`   | 啟用第 n 個斷點（breakpoint enable）  |
| `d [addr]` | 顯示記憶體內容，例如 `d 0x7c00`         |
| `u [addr]` | 反組譯程式碼，例如 `u 0x7c00`          |
| `r`        | 顯示所有暫存器內容                     |
| `regs`     | 同上，顯示寄存器狀態                    |
| `w`        | 顯示 flags 狀態                   |
| `q`        | 離開 Bochs                      |
| `help`     | 顯示所有可用的除錯指令                   |


注意：要中斷執行中的指令使用 Ctrl+C，中斷後會出現 '<bochs:x>'，再輸入 q 即可正常退出。
