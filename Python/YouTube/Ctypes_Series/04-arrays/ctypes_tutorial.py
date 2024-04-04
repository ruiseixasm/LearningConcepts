import ctypes
import os

path = os.getcwd()
clibrary = ctypes.CDLL(os.path.join(path, 'clibrary.so'))

# In Python's ctypes module, ctypes.c_int represents a ctypes data type for a signed integer.
#     The expression ctypes.c_int * 10 creates a new data type that consists of an array
#     of 10 ctypes.c_int elements.
# To create an instance of this array type with some initial values, you can use the syntax
#     (ctypes.c_int * 10)(initial_values), where initial_values is a sequence containing
#     the initial values for the array elements.
values = (ctypes.c_int * 10)()  # Initialization exclusive to ctypes!
print(values)                       # <__main__.c_int_Array_10 object at 0x7f6126e640c0>

for i in range(len(values)):
    values[i] = i

sum = clibrary.sumArray_v1(values, len(values))
print("Sum:", sum)                  # Sum: 45

result = clibrary.incArray_v1(values, len(values))  # 1st increment of values
print("Result:", result)            # Result: -1308246176

clibrary.incArray_v1.restype = ctypes.POINTER(ctypes.c_int)
result = clibrary.incArray_v1(values, len(values))  # 2nd increment of values
print("Result:", result)            # Result: <__main__.LP_c_int object at 0x7f67b20b8140>
print("Result:", result.contents)   # Result: c_int(2)

for i in range(10):
    print(result[i])    # values was incremented twice (result points to values)

print() # blank line

clibrary.getArray_v1.restype = ctypes.POINTER(ctypes.c_int)
result = clibrary.getArray_v1()

for i in range(10):
    print(result[i])    # array with values not incremented

# do some other stuff
# then need to free the Array memory dynamically allocated
clibrary.free_memory_v1(result) # avoids memory leaks



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