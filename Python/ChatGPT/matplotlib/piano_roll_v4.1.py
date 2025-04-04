import matplotlib.pyplot as plt

fig, axs = plt.subplots(nrows=2, figsize=(10, 6), sharex=True)

# First chart
axs[0].barh([60, 62], [1, 1], left=[0, 1], color='blue')
axs[0].set_title("Track 1")

# Second chart
axs[1].barh([64, 65], [1, 1], left=[2, 3], color='red')
axs[1].set_title("Track 2")

plt.tight_layout()
plt.show()
