# 前端路由对比：Express vs React vs Next.js

三个项目对比前端路由的不同实现方式。

## 🚀 启动方式

```bash
# 1. 安装
npm install          # 根目录
cd express-demo && npm install
cd react-router-demo && npm install
cd nextjs-demo && npm install

# 2. 启动
npm run start      # http://localhost:3000
npm run dev        # http://localhost:5173
npm run dev -- -p 3001      # http://localhost:3001

## 📁 项目结构

```
frontend-routing-comparison/
│
├── express-demo/           # 后端路由
│   ├── server.js
│   └── public/
│       ├── index.html
│       └── about.html
│
├── react-router-demo/      # 前端路由
│   ├── vite.config.js
│   └── src/
│       ├── main.jsx
│       └── App.jsx
│
├── nextjs-demo/            # 混合路由（SSR + 前端路由）
│   ├── pages/
│   │   ├── index.js
│   │   └── about.js
│   └── next.config.js
│
├── README.md
└── package.json (根目录脚本)
```