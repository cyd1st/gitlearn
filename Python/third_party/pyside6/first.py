import sys
from PySide6.QtCore import QObject, Qt
from PySide6.QtWidgets import QApplication, QLineEdit, QPushButton, QVBoxLayout, QWidget

class MyForm(QObject):
    def __init__(self, app):
        super().__init__()

        self.text_input = QLineEdit()
        self.button = QPushButton("Submit")

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text_input)
        self.layout.addWidget(self.button)

        self.widget = QWidget()
        self.widget.setLayout(self.layout)

    def show(self):
        self.widget.show()

# 创建并显示表单
if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = MyForm(app)
    form.show()
    sys.exit(app.exec())