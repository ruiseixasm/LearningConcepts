import ctypes
import os
import time
from random import randint

def partition(array, low, high):
    pivot = array[high]
    i = low - 1
    for j in range(low, high):
        if array[j] <= pivot:
            i += 1
            (array[i], array[j]) = (array[j], array[i])
    (array[i + 1], array[high]) = (array[high], array[i + 1])
    return i + 1

def quick_sort(array, low, high):
    if low < high:
        pi = partition(array, low, high)
        quick_sort(array, low, pi - 1)
        quick_sort(array, pi + 1, high)

path = os.getcwd()
clibrary = ctypes.CDLL(os.path.join(path, 'test3.so'))

array_size = 1000

array = (ctypes.c_int * array_size)()
for i in range(array_size):
    array[i] = randint(0, array_size * 10)

start = time.perf_counter()
value = clibrary.quick_sort_c(array, 0, array_size - 1)
end = time.perf_counter()
print("Ctypes result 3 time taken:", end - start)

new_array = []
for i in range(array_size):
    new_array.append(randint(0, array_size * 10))

start = time.perf_counter()
value = quick_sort(new_array, 0, array_size - 1)
end = time.perf_counter()
print("Python result 3 time taken:", end - start)



# Command to be run
# python3 -u driver3.py 

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