# test.py
try:
    import my_library
    result = my_library.add(1, 2)
    print(f"Result of add(1, 2): {result}")
except ImportError as e:
    print("ImportError:", e)
except Exception as e:
    print("An error occurred:", e)
