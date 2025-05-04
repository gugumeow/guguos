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








------

網卡接收資料的從位元（bit）→ byte → FIFO → 主記憶體的完整路徑：

1. 接收從 0x55, 0xD5 開始：Preamble + SFD

你說的：
	•	0x55 是 Ethernet 的 前導碼（Preamble）：一連串 10101010，用來幫助接收端鎖定時脈
	•	0xD5 是 SFD（Start Frame Delimiter），表示正式資料要開始了

網卡（的 MAC 控制器）會：
	1.	在 bit 級別透過 Shift Register 偵測這個模式
	2.	偵測到後 → 開始接收正式封包內容（從 Destination MAC 開始）
	3.	每收到 8 個 bit（1 byte），就可以傳進 RX FIFO

⸻

2. RX FIFO 如何存資料？
	•	RX FIFO 是「以 Byte 為單位」的快取記憶體（SRAM）
	•	MAC 收到每個 byte，就丟進 RX FIFO 中（可能還加上封包長度計數器）
	•	直到整包封包收完，並通過 CRC 驗證（FCS）

⸻

3. DMA 如何從 RX FIFO 傳到主記憶體？

當整個封包接收完畢，DMA 控制器會被觸發，開始搬資料到主記憶體。

4. 主記憶體接收封包的「區塊名稱」是什麼？

以 Linux 為例：

網卡驅動會建立：
	•	struct sk_buff（簡稱 skb）：記錄封包在記憶體中的資訊
	•	每塊資料實際存放在 skb->data 指向的那塊記憶體
	•	這塊記憶體是 DMA-able 的，通常是「ring buffer（環狀緩衝區）」的一部份
	•	通常透過 netdev_alloc_skb() 配置，或在驅動初始時用 dma_alloc_coherent() 建立一整塊共享空間

------

網卡接收的數位訊號頻率與內部 shift register clock 通常不同，兩者之間會透過 CDR + FIFO 緩衝等技術完成資料同步與時脈域轉換，確保資料穩定地從線上接收並送入內部數位邏輯。








