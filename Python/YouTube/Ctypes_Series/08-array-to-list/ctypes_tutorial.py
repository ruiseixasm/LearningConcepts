import ctypes
import os

path = os.getcwd()
clibrary = ctypes.CDLL(os.path.join(path, 'clibrary.so'))

clibrary.getArray_c.restype = ctypes.POINTER(ctypes.c_int)  # signature for pointers
result = clibrary.getArray_c()
print(result.contents.value)

# Slow solution
mylist = []
for i in range(10):
    mylist.append(result[i])
print(mylist)

# Faster solution (slicing)
mylist = result[:10]
print(mylist)


clibrary.delete_array_c(result)



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