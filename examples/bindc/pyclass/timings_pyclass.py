from timer import timer
import bbdir.pycart as pycart

class fakecart:
  def __new__(cls, *args, **kwargs):
    obj = object.__new__(cls)
    obj.x = 0
    obj.y = 0
    obj.z = 0
    return obj

  def __init__(self, x, y, z):
    self.x = x
    self.y = y
    self.z = z
  def __repr__(self):
    return f"fakecart(x: {self.x}, y: {self.y}, z: {self.z})"

  def unitstep(self):
    self.x = self.x + 1
    self.y = self.y + 1
    self.z = self.z +1

aak = pycart.pycart(1, 10, 2)
bbk = fakecart(1, 10, 2)

print(f"{bbk} starting here:")
with timer() as t:
    [bbk.unitstep() for x in range(50000)]
    print(f"Python class took: {t.elapse}")
print(f"{bbk} from the Python Class")
print(f"{aak} starting now:")
with timer() as t:
    [aak.unitstep() for x in range(50000)]
    print(f"FortranDT class took: {t.elapse}")
print(f"{aak} from FortranDT")

del(aak)
