import PySide2

class MyForm(PySide2.QtCore.QObject):
    def __init__(self):
        super().__init__()

        self.text_input = PySide2.QtWidgets.QLineEdit()
        self.button = PySide2.QtWidgets.QPushButton("Submit")

        self.layout = PySide2.QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.text_input)
        self.layout.addWidget(self.button)

        self.widget = PySide2.QtWidgets.QWidget()
        self.widget.setLayout(self.layout)

    def show(self):
        self.widget.show()

form = MyForm()
form.show()