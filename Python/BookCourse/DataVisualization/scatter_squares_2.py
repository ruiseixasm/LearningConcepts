import matplotlib.pyplot as plt

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.scatter(2, 4, s=200) # v.2

# Set chart title and label axes.
ax.set_title("Square Numbers", fontsize=24) # v.2
ax.set_xlabel("Value", fontsize=14) # v.2
ax.set_ylabel("Square of value", fontsize=14) # v.2

# Set size of tick labels.
ax.tick_params(axis='both', which='major', labelsize=14) # v.2

plt.show()