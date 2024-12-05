import tkinter as tk

class App(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack()

        self.entry_thing_y = tk.Entry()
        self.entry_thing_y.pack()

        # Create the application variable.
        self.contents = tk.StringVar()
        # Set it to some value.
        self.contents.set("this is a variable")
        # Tell the entry widget to watch this variable.
        self.entry_thing_y["textvariable"] = self.contents  # It's an Option NOT and attribute!
        # These options are "variable", "textvariable", "onvalue", "offvalue", and "value".

        # Define a callback for when the user hits return.
        # It prints the current value of the variable.
        self.entry_thing_y.bind('<Key-Return>',
                             self.print_contents)

    def print_contents(self, event):
        print("Hi. The current entry content is:",
              self.contents.get())

root = tk.Tk()
myapp = App(root)
myapp.mainloop()