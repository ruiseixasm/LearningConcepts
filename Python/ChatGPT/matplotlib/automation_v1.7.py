import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # Example: y = x

# Create the plot
plt.figure(figsize=(12, 4))

# Plot the interpolation line
plt.plot(x, y, linestyle='-', color='lightblue', linewidth=2, label='Interpolation')

# Overlay the actual data points
plt.plot(x, y, marker='o', linestyle='None', color='blue', markersize=4, label='Data Points')

# Add dashed horizontal lines at multiples of 16 (excluding 64)
for i in range(0, 129, 16):
    if i != 64:
        plt.axhline(y=i, color='gray', linestyle='--', linewidth=1)

# Dashed line at y = 127 if not already included
if 127 % 16 != 0:
    plt.axhline(y=127, color='gray', linestyle='--', linewidth=1)

# Solid gray line at y = 64
plt.axhline(y=64, color='gray', linestyle='-', linewidth=1.5)

# Set axis limits
plt.ylim(-1, 128)
plt.xlim(0, 128)

# Ticks
plt.xticks(range(0, 129, 8))
plt.yticks(range(0, 129, 16))

# Labels and layout
plt.title("Integer Points with Linear Interpolation")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True, axis='x')
plt.tight_layout()
plt.legend()

# Show the plot
plt.show()
