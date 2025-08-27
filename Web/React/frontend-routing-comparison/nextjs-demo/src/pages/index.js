import Link from 'next/link';

export default function Home() {
  return (
    <div style={{ padding: '20px', fontFamily: 'Arial' }}>
      <h1>首页</h1>
      <nav style={{ margin: '20px 0' }}>
        <Link href="/about" style={{ margin: '0 10px', color: 'blue', textDecoration: 'underline' }}>
          关于我们
        </Link>
      </nav>
      <p>这是 Next.js 的首页。服务器预渲染 HTML，SEO 友好，首屏快！</p>
    </div>
  );
}