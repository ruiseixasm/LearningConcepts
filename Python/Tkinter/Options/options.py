import tkinter as tk    # Better practice than "from tkinter import *"
from tkinter import ttk

root = tk.Tk()
frm = ttk.Frame(root, padding=10)
btn = ttk.Button(frm, text="Just a Button")
print(btn.configure().keys())
print(set(btn.configure().keys()) - set(frm.configure().keys()))

print(dir(btn))
print(set(dir(btn)) - set(dir(frm)))
