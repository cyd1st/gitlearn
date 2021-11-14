'''
Descripttion: 关于对象的练习
Author: cyd
Date: 2021-08-27 15:23:59
LastEditTime: 2021-08-27 17:08:15
'''
class Student(object):

    def __init__(self, name, score):
        self.__name = name
        self._score = score

    def print_score(self):
        print("%s: %s" % (self.__name, self._score))

    def get_grade(self):
        if self._score >= 90:
            return 'A'
        elif self._score >= 80:
            return 'B'
        elif self._score >= 60:
            return 'C'
        else:
            return 'D'


狗子 = Student('陈诗渊', 59)

狗子.print_score()

狗子.get_grade()

狗子.__name

狗子._score
