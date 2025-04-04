import matplotlib.pyplot as plt

fig, ax = plt.subplots()

# Main plot
ax.plot([0, 1, 2], [60, 62, 64])

# Inset
inset_ax = ax.inset_axes([0.6, 0.6, 0.3, 0.3])
inset_ax.plot([0, 1, 2], [64, 66, 68], color='red')

plt.show()
