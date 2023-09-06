import matplotlib.pyplot as plt

input_values = [1, 2, 3, 4, 5] # v.3
squares = [1, 4, 9, 16, 25]

plt.style.use('seaborn') # v.4
fig, ax = plt.subplots()
ax.plot(input_values, squares, linewidth=3) # v.2 v.3

# Set chart title and label axes.
ax.set_title("Square Numbers", fontsize=24) # v.2
ax.set_xlabel("Value", fontsize=14) # v.2
ax.set_ylabel("Square of Value", fontsize=14) # v.2

# Set size of tick labels.
ax.tick_params(axis='both', labelsize=14) # v.2

plt.show()