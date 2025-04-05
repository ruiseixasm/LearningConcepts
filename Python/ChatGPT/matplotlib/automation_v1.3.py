import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # Example data: y = x

# Create the plot
plt.figure(figsize=(12, 4))
plt.plot(x, y, marker='o', linestyle='-', color='blue', markersize=4)

# Add horizontal grid lines at multiples of 16
for i in range(0, 128, 16):
    plt.axhline(y=i, color='gray', linestyle='--', linewidth=1)

# Highlight the line at y = 64
plt.axhline(y=64, color='green', linestyle='-', linewidth=2)

# Bold horizontal line at 127
plt.axhline(y=127, color='red', linestyle='-', linewidth=2)

# Set limits: top is 128, bottom is symmetric about y=127
distance_to_top = 128 - 127  # = 1
plt.ylim(-1, 128)

# Customize ticks
plt.xticks(range(0, 128, 8))
plt.yticks(range(0, 129, 16))  # 128 won't be drawn, but ticks go up to it

# Labels and layout
plt.title("Integer Points with Horizontal Lines Every 16")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True, axis='x')
plt.tight_layout()

# Show the plot
plt.show()
