import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # y = x for this example

# Create the plot
plt.figure(figsize=(12, 4))
plt.plot(x, y, marker='o', linestyle='-', color='blue', markersize=4)

# Add dashed horizontal grid lines at multiples of 16
for i in range(0, 128, 16):
    plt.axhline(y=i, color='gray', linestyle='--', linewidth=1)

# Dashed red line at y = 127
plt.axhline(y=127, color='red', linestyle='--', linewidth=1.5)

# Highlight the solid green line at y = 64
plt.axhline(y=64, color='green', linestyle='-', linewidth=2)

# Set y-limits with symmetric padding above and below the data
plt.ylim(-1, 128)

# Set x-limits to exactly 0 to 120, no extra margins
plt.xlim(0, 120)

# Set ticks
plt.xticks(range(0, 121, 8))
plt.yticks(range(0, 129, 16))

# Labels and layout
plt.title("Integer Points with Horizontal Lines Every 16")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True, axis='x')
plt.tight_layout()

# Show the plot
plt.show()
