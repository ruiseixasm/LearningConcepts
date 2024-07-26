import os
import sys

# Define the lib directory path
lib_dir = os.path.join(os.path.dirname(__file__), 'lib')

# Print and check if lib_dir exists and list its contents
print(f"Lib directory: {lib_dir}")
print("Files in lib directory:", os.listdir(lib_dir))

# Add the lib directory to sys.path
sys.path.insert(0, lib_dir)

# Verify that the .pyd file is in the specified directory
pyd_file = 'my_library.cp311-win_amd64.pyd'
pyd_path = os.path.join(lib_dir, pyd_file)
print(f"Checking if {pyd_file} file exists: {os.path.exists(pyd_path)}")
print(f"Expected .pyd file path: {pyd_path}")

# Add the lib directory to PATH to resolve any dependent DLLs
os.environ['PATH'] = lib_dir + os.pathsep + os.environ['PATH']

# Print the current sys.path and PATH for debugging
print("sys.path:", sys.path)
print("PATH:", os.environ['PATH'])

# Now you can try to import the module
try:
    import my_library
    print("Successfully imported my_library")
    # If you want to call a function from my_library, do it here
except ImportError as e:
    print("ImportError:", e)
except Exception as e:
    print("An error occurred:", e)
