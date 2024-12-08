# Youtube url: https://youtu.be/8C9IJEuQjhY?si=fRMRka2sPLx4Zab5&t=54
"""Threading adds new lanes for your program to execute"""
import threading
import time
import random

def print_names():
    for name in ("John", "Kate", "Mike", "Alex", "Ann"):    # 5 names
        print(name)
        time.sleep(random.uniform(0.5, 1.5))

def print_age(min_sleep, max_sleep):
    for _ in range(5):
        print(random.randint(20, 50))
        time.sleep(random.uniform(min_sleep, max_sleep))

t1 = threading.Thread(target=print_names)
t2 = threading.Thread(target=print_age, args=(0.2, 1))

t1.start()
t2.start()

# Wait until the thread terminates.
# This blocks the calling thread until the thread whose join() method is called ends
t1.join()
t2.join()
# Only gets into here when t1 and t2 ends (joined)

# print_names()
# print_age()
