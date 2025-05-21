## Bochs 簡介

Bochs 是一個開源的 IA-32 (x86) 模擬器，用來模擬 PC 系統，非常適合用於作業系統教學與開發。

## 最簡單的 Bochs 範例：只能顯示「Hello World!」

### Bochs 基本檔案結構

```
/your_project
├── boot.asm
├── build.sh
└── bochsrc.txt
```

### 安裝 bochs, nasm（組譯器）

```bash
sudo apt install bochs bochs-x nasm

```

### 編寫組合語言程式：hello.asm

```asm
[BITS 16]
[ORG 0x7C00]

start:
    ; 清除螢幕（可略）
    mov ah, 0x0E

    mov si, msg
.next_char:
    lodsb           ; 讀一個字元到 AL
    cmp al, 0
    je hang         ; 如果是 NULL 結束

    int 0x10        ; BIOS 輸出字元到螢幕
    jmp .next_char

hang:
    cli
    hlt
    jmp $

msg db 'Hello World!', 0

times 510-($-$$) db 0  ; 填滿到 510 bytes
dw 0xAA55              ; 引導扇區魔術字
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
