from turtle import *

setup(500, 500, 800, 400)
circle(100)

for i in range(10):
    pendown()
    fd(10)
    penup()
    fd(10)

pd()
left(100)
circle(100)

input()