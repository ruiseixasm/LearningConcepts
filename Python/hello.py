def main():
    name = input("What's your name? ")
    hello(name)


def hello(to="world"): # default value like in Visual Basic
    print("hello,", to)


hello()
main()