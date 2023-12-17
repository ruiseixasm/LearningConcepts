def print_method():
    print("hello world")
def test_print_method():
    for i in range(2):
        print_method()
for i in range(3):
    test_print_method()
