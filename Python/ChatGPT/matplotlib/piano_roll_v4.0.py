import matplotlib.pyplot as plt

fig, ax = plt.subplots()

# Chart 1
ax.barh(y=[60, 62], width=[1, 1], left=[0, 1], color='green', label='Track 1')

# Chart 2
ax.barh(y=[64, 65], width=[1, 1], left=[2, 3], color='orange', label='Track 2')

ax.legend()
plt.show()
