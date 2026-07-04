const express = require('express');
const path = require('path');
const app = express();
const PORT = 3000;

// 静态文件中间件
app.use(express.static(path.join(__dirname, 'public')));

// 后端路由
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.get('/about', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'about.html'));
});

app.listen(PORT, () => {
  console.log(`服务器运行在 http://localhost:${PORT}`);
});