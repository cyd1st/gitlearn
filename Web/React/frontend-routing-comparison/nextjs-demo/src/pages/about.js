import Link from 'next/link';

export default function About() {
    return (
        <div style={{ padding: '20px', fontFamily: 'Arial' }}>
            <h1>关于我们</h1>
            <nav style={{ margin: '20px 0' }}>
                <Link href="/" style={{ margin: '0 10px', color: 'blue', textDecoration: 'underline' }}>
                    首页
                </Link>
            </nav>
            <p>这是关于我们页面。URL 变了，但切换无刷新，体验流畅！</p>
        </div>
    );
}