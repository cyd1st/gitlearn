class Namespace1:
    def __init__(self, **kwargs):
        for name in kwargs:
            setattr(self, name, kwargs[name])
            
class Namespace2:
    def __init__(self, **kwargs):
        for name in kwargs:
            self.name = kwargs[name]

            
n1 = Namespace1(a=1, b=2)
n2 = Namespace2(a=1, b=1)

print(vars(n1))
print(vars(n2))