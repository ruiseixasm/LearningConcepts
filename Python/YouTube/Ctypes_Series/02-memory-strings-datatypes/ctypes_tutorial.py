import ctypes

clibrary = ctypes.CDLL("./clibrary.so")   # recomended to write the full path

print(clibrary.add_v1(5, 6))

py_add_v1 = clibrary.add_v1
py_add_v1.argtypes = [ctypes.c_int, ctypes.c_int]
py_add_v1.restype = ctypes.c_int
print(py_add_v1(8, 7))

clibrary.display_v1("Hello World")
clibrary.display_v1(b"Hello World")

string = ctypes.c_char_p(b"Hello World")
clibrary.display_v1(string)

# In C strings are mutable while in Python strings are immutable!
print(string)   # Memory location
string.value = b"Goodbye World" # modifies the value attribute of the object referred to by string
print(string)   # Memory location

# Creates string buffer to give mutable strings to Python
string = ctypes.create_string_buffer(b"Hello World")    # auto size based on "Hello World"
clibrary.display_v1(string)
print(string)   # Memory location original address
string = ctypes.create_string_buffer(100)               # set buffer size of 100
print(string)   # Memory location new address
string.value = b"Goodbye World" # modifies the value attribute of the object referred to by string
print(string)   # Memory location same address

