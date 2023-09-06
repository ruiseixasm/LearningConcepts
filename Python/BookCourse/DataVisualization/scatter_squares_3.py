import matplotlib.pyplot as plt

x_values = [1, 2, 3, 4, 5] # v.3
y_values = [1, 4, 9, 16, 25] # v.3

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.scatter(x_values, y_values, s=100) # v.2 v.3

# Set chart title and label axes.
ax.set_title("Square Numbers", fontsize=24) # v.2
ax.set_xlabel("Value", fontsize=14) # v.2
ax.set_ylabel("Square of value", fontsize=14) # v.2

# Set size of tick labels.
ax.tick_params(axis='both', which='major', labelsize=14) # v.2

plt.show()