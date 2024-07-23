import ctypes
import platform
import os

# Determine the operating system
current_os = platform.system()

# Define the name of the shared library based on the operating system
if current_os == "Windows":
    lib_name = 'libMyLibrary_ctypes.dll'
elif current_os == "Darwin":  # macOS
    lib_name = 'libMyLibrary_ctypes.dylib'
else:  # Assume Linux/Unix
    lib_name = 'libMyLibrary_ctypes.so'

# Get the absolute path to the library
lib_path = os.path.abspath(f'./build/lib/{lib_name}')

# Print the library path for debugging
print(f"Library path: {lib_path}")

# Check if the library file exists
if not os.path.isfile(lib_path):
    raise FileNotFoundError(f"COULD NOT FIND THE LIBRARY FILE: {lib_path}")

# Load the shared library
lib = ctypes.CDLL(lib_path)

# Define the argument and return types for the C function
lib.add_ctypes.argtypes = [ctypes.c_int, ctypes.c_int]
lib.add_ctypes.restype = ctypes.c_int

# Call the C++ function from Python
result = lib.add_ctypes(3, 4)
print(f"3 + 4 = {result}")
