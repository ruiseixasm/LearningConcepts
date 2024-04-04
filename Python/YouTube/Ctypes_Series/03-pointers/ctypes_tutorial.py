import ctypes

clibrary = ctypes.CDLL("./clibrary.so")   # recomended to write the full path

ctypes.pointer  # is a function used to create a pointer to an existing ctypes object.
ctypes.POINTER  # is a class used to create new pointer types for ctypes data types.

alloc_func = clibrary.alloc_memory_v1
alloc_func.restype = ctypes.POINTER(ctypes.c_char_p)

free_func = clibrary.free_memory_v1
free_func.argtypes = [ctypes.POINTER(ctypes.c_char_p)]

cstring_pointer = alloc_func()  # returns the memory address pointer (char* str)
print(cstring_pointer)
#print(cstring_pointer.value)    # error, object has no attribute 'value'

cstring = ctypes.c_char_p.from_buffer(cstring_pointer)  # converts C pointer to Python string
print(cstring.value)

free_func(cstring_pointer)


num = 100
#ptr = ctypes.pointer(num)   # TypeError: _type_ must have storage info
#print(ptr.contents)

num = ctypes.c_int(100)
ptr = ctypes.pointer(num)           # create a pointer to an existing ctypes object
print(ptr.contents)         # c_int(100)

ptr2 = ctypes.POINTER(ctypes.c_int) # create new pointer types for ctypes data types
ptr2.contents = num         # num is an existing ctypes object
print(ptr2.contents)        # c_int(100)

num2 = ctypes.c_int(200)
ptr2.contents = num2        # num2 is an existing ctypes object
print(ptr2.contents)        # c_int(200)