import matplotlib.pyplot as plt

x_values = range(1, 1001) # v.3 v.4
y_values = [x**2 for x in x_values] # v.3 v.4

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.scatter(x_values, y_values, s=10) # v.2 v.3 v.4

# Set chart title and label axes.
ax.set_title("Square Numbers", fontsize=24) # v.2
ax.set_xlabel("Value", fontsize=14) # v.2
ax.set_ylabel("Square of value", fontsize=14) # v.2

# Set size of tick labels.
ax.tick_params(axis='both', which='major', labelsize=14) # v.2

# Set the range for each axis.
ax.axis([0, 1100, 0, 1100000])

plt.show()