from die import Die

# Create a D6.
die = Die()

# Make some rolls, and store results in a list.
results = []
for roll_num in range(1000): # v.2
    result = die.roll()
    results.append(result)

# Analyze the results.
frequencies = [] # v.2
for value in range(1, die.num_sides + 1): # v.2
    frequency = results.count(value)
    frequencies.append(frequency)

print(frequencies) # v.2