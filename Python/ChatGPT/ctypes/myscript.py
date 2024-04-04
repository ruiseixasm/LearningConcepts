# myscript.py
import ctypes

# Load the shared library
mylib = ctypes.CDLL('./mylibrary.so')

# Define the function prototype
add_func = mylib.add
add_func.argtypes = [ctypes.c_int, ctypes.c_int]
add_func.restype = ctypes.c_int

# Call the C++ function
result = add_func(10, 20)
print("Result:", result)
