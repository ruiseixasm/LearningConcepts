import ctypes

clibrary = ctypes.CDLL("./clibrary.so")   # recomended to write the full path

clibrary.display1()
clibrary.display2("John", 18)
clibrary.display2(b"John", 18)  # needs to be argued as binary (b)

func2 = clibrary.display2
func2.argtypes = [ctypes.c_char_p, ctypes.c_int]
func2(b"John", 18)

func3 = clibrary.display3
func3.argtypes = [ctypes.c_char_p, ctypes.c_int]
func3.restype = ctypes.c_char_p
string = func3(b"John", 18)
print(string)