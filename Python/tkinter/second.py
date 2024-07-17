import tkinter as tk

# 创建一个主窗口
root = tk.Tk()
root.title("Google")
root.geometry("800x600")

# 创建一个画布来容纳徽标
canvas = tk.Canvas(root, width=800, height=120)
canvas.pack(side=tk.TOP, anchor=tk.CENTER)
# 加载徽标图像
logo = tk.PhotoImage(file="./asset/google-logo.png")
canvas.create_image(10, 10, anchor=tk.CENTER, image=logo)

# 创建一个框架来容纳搜索栏和按钮
frame = tk.Frame(root)
frame.pack(fill=tk.X)

# 创建一个搜索栏
entry = tk.Entry(frame, width=50)
entry.pack(side=tk.LEFT)

# 创建一个搜索按钮
button = tk.Button(frame, text="Search")
button.pack(side=tk.LEFT)

# 创建一个标签来显示结果
label = tk.Label(root, text="Results:")
label.pack(fill=tk.X)


# 运行事件循环
root.mainloop()