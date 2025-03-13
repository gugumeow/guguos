 Linux Mint 上安裝 n8n 有幾種方式，以下是三種常見的方法：

## 方法一：使用 Docker 安裝（推薦）

這是最簡單和方便的方法，因為 n8n 官方提供 Docker 映像。

安裝 Docker：
```
sudo apt update
sudo apt install docker.io docker-compose -y
```

拉取 n8n 映像：
```
sudo docker pull n8nio/n8n
```

建立 n8n 容器：
```
sudo docker run -d --name n8n -p 5678:5678 n8nio/n8n
```

瀏覽器訪問：
打開瀏覽器並輸入：http://localhost:5678


## 方法二：使用 npm 安裝

可以直接使用 Node.js 安裝 n8n，但相對於 Docker，環境管理較為麻煩。

安裝 Node.js (建議使用 nvm)：
```
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.4/install.sh | bash
source ~/.bashrc
nvm install --lts


安裝 n8n：
```
npm install -g n8n
```

啟動 n8n：
```
n8n
```

瀏覽器訪問：
```
http://localhost:5678
```

## 方法三：使用 Docker Compose 自訂配置

這種方式適合需要更多自訂設定或持久化資料的情況。

建立資料夾：
```
mkdir ~/n8n-docker && cd ~/n8n-docker
```

建立 docker-compose.yml：
```yaml
version: '3'
services:
  n8n:
    image: n8nio/n8n
    ports:
      - 5678:5678
    volumes:
      - ./n8n:/home/node/.n8n
    environment:
      - N8N_BASIC_AUTH_ACTIVE=true
      - N8N_BASIC_AUTH_USER=admin
      - N8N_BASIC_AUTH_PASSWORD=password
```

啟動服務：
```
sudo docker-compose up -d
```

瀏覽器訪問：
```
http://localhost:5678
```

使用者名稱：admin
密碼：password

## 注意事項

1.使用 Docker 安裝時，請確保防火牆允許埠號 5678。

2.若要設定自動開機啟動，可將 Docker Compose 加入系統服務。

3.若在生產環境中使用，建議加上 HTTPS 和資料庫持久化配置。

4.有任何問題或需要更多設定，隨時問我！ 😄
