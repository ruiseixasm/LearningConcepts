import ctypes
import os
import time

def fib(n):
    if n > 1:
        return fib(n - 1) + fib(n - 2)
    return n

path = os.getcwd()
clibrary = ctypes.CDLL(os.path.join(path, 'test1.so'))

start = time.perf_counter()
value = clibrary.fib(30)
end = time.perf_counter()
print("Ctypes result:", value, " time taken:", end - start)

start = time.perf_counter()
value = fib(30)
end = time.perf_counter()
print("Python result:", value, " time taken:", end - start)



# Command to be run
# python3 -u driver1.py 

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