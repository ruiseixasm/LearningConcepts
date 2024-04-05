import ctypes
import os

# Equivalent to a C struct
class Point(ctypes.Structure):
    _fields_ = [("x", ctypes.c_int), ("y", ctypes.c_int)]

class PointArray(ctypes.Structure):
    _fields_ = [("points", Point * 3)]  # This is how arrays are created in ctypes

class Student(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p)]

path = os.getcwd()
clibrary = ctypes.CDLL(os.path.join(path, 'clibrary.so'))

# Point Class/Struct
print()

p = Point(5, 6)
print(p)
pointer_to_p = ctypes.pointer(p)
clibrary.printPoint_c(pointer_to_p)

clibrary.getPoint_c.restype = ctypes.POINTER(Point)
p = clibrary.getPoint_c()   # FACTORY (Object needs to be deleted!)
print(p)
print(p.contents)
print(p.contents.x, p.contents.y)
# Do other code
# Delete Point p
clibrary.deletePoint_c(p)

points = (Point(1, 1), Point(2, 3), Point(5, 10))
pa = PointArray(points)
clibrary.printPointArray_c(pa)

# Student Classs/Struct
print()

s = Student(b"Coders Legacy")
clibrary.printStudent_c(s)

name = "Binary name format"
name_b = bytes(name, 'utf-8')
s = Student(name_b)
clibrary.printStudent_c(s)

clibrary.getStudent_c.restype = ctypes.POINTER(Student)
s = clibrary.getStudent_c() # FACTORY (Object needs to be deleted!)
print(s)
print(s.contents)
print(s.contents.name)
print(s.contents.name.decode('utf-8'))
# Do other code
# Delete Student s
clibrary.deleteStudent_c(s)



# Command to be run
# python3 -u ctypes_tutorial.py 

# In Python, the -u flag stands for "unbuffered binary stdout and stderr".
#     When Python is run in unbuffered mode (-u), it means that the
#     standard output (stdout) and standard error (stderr) streams will be
#     flushed immediately after each write operation, instead of being buffered
#     and flushed periodically.

# This is particularly useful for ensuring that the output from your Python script
#     is displayed in real-time, especially when the script's output is being
#     redirected or piped to another program or process.

# So, in the command python3 -u ctypes_tutorial.py, the -u flag is ensuring that
#     the output produced by the ctypes_tutorial.py script is displayed
#     immediately without buffering.