import { Routes, Route, Link } from 'react-router-dom';

function App() {
  return (
    <div style={{ padding: '20px', fontFamily: 'Arial' }}>
      <nav style={{ marginBottom: '20px' }}>
        <Link to="/" style={{ margin: '0 10px' }}>首页</Link>
        <Link to="/about" style={{ margin: '0 10px' }}>关于我们</Link>
      </nav>

      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/about" element={<About />} />
      </Routes>
    </div>
  );
}

function Home() {
  return (
    <div>
      <h1>首页</h1>
      <p>这是首页内容。点击导航，页面不会刷新！</p>
    </div>
  );
}

function About() {
  return (
    <div>
      <h1>关于我们</h1>
      <p>这是关于我们页面。URL 变了，但没有刷新！</p>
    </div>
  );
}

export default App;