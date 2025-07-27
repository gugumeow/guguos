### 設定canvas寬高

- 通過canvas標籤或canvas.width及canvas.height來設定，"不要"用CSS或canvas.style.width或canvas.style.height來設定。

- 否則CSS會對整個canvas畫布會進行拉伸，讓原來的canvas圖案失真。

### 先設定樣式，再進行stroke描邊或fill填充

- strokeStyle描邊樣式、stroke描邊
- fillStyle填充樣式、fill填充
- shadow陰影：

```javascript
ctx.shadowColor = 'rgba(0, 0, 0, 0.5)';  // 陰影顏色
ctx.shadowOffsetX = 4;                   // 陰影往右偏移 4px
ctx.shadowOffsetY = 4;                   // 陰影往下偏移 4px
ctx.shadowBlur = 8;                      // 陰影模糊程度

ctx.fillStyle = 'blue';
ctx.fillRect(50, 50, 100, 100);
```








