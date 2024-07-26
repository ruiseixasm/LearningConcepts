import sys
import os

# Add the directory containing the .pyd file to the sys.path
build_dir = os.path.abspath('./build')
sys.path.append(build_dir)

# Print sys.path to verify the directory is included
print("sys.path:", sys.path)

# Verify that the .pyd file is in the specified directory
pyd_path = os.path.join(build_dir, 'my_library.cp311-win_amd64.pyd')
print("Checking if .pyd file exists:", os.path.exists(pyd_path))
print("Expected .pyd file path:", pyd_path)

# Now you can try to import the module
try:
    import my_library
    # Test the function from the module
    result = my_library.add(1, 2)
    print(f"Result of add(1, 2): {result}")
except ImportError as e:
    print("ImportError:", e)
except Exception as e:
    print("An error occurred:", e)
