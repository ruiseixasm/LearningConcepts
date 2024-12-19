def count_up_to(n):
    """A generator that counts from 1 to n."""
    count = 1
    while count <= n:
        yield count
        count += 1

# Using the generator
for number in count_up_to(5):
    print(number)

# How it Works:
#     The yield keyword is used to pause the function and return a value to the caller.
#     When the generator is called (e.g., by the for loop), it resumes from where it left off after yield.
#     This continues until the generator finishes (i.e., when the condition count <= n is no longer true).
