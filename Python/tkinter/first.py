import tkinter as tk

# 创建一个主窗口
root = tk.Tk()
root.title("Hello, tkinter!")
root.geometry("400x200")

# 添加一个按钮
button = tk.Button(root, text="Click me")
button.pack()

# 创建一个文本框
entry = tk.Entry(root)
entry.pack()

# 创建一个标签
label = tk.Label(root, text="Hello, world!")
label.pack()

root.title("My First App")
root.geometry("400x200")
root.resizable(False, False)

# 运行事件循环
root.mainloop()