[4 對雙絞線]

雙絞線對 1 —— Tx / Rx 同時進行（差動）

雙絞線對 2 —— Tx / Rx 同時進行（差動）

雙絞線對 3 —— Tx / Rx 同時進行（差動）

雙絞線對 4 —— Tx / Rx 同時進行（差動）

    ↓

[PHY：解碼 + descramble + SFD]

名稱 位元組數 內容 (二進位) 用途

Preamble 7 Bytes 10101010 x7 (0x55) 同步時脈

SFD 1 Byte 10101011 (0xD5) 封包資料的起點指示

    ↓（每週期約 8 bits）

[RX FIFO（網卡內部 SRAM）]

    ↓（MAC 驗證封包完整性）

[DMA 將封包搬到主記憶體 buffer]

    ↓

[CPU 被中斷 → 處理網路封包]




