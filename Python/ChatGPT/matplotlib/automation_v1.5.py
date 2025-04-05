import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # Example: y = x

# Create the plot
plt.figure(figsize=(12, 4))
plt.plot(x, y, marker='o', linestyle='-', color='blue', markersize=4)

# Add dashed horizontal lines at multiples of 16 (including 127)
for i in range(0, 129, 16):
    plt.axhline(y=i, color='gray', linestyle='--', linewidth=1)
# Also add one at y=127 to match others
if 127 % 16 != 0:
    plt.axhline(y=127, color='gray', linestyle='--', linewidth=1)

# Solid green line at y = 64
plt.axhline(y=64, color='green', linestyle='-', linewidth=2)

# Set limits with symmetric vertical padding and exact x-range
plt.ylim(-1, 128)
plt.xlim(0, 128)

# Ticks
plt.xticks(range(0, 129, 8))
plt.yticks(range(0, 129, 16))

# Labels and layout
plt.title("Integer Points with Horizontal Lines Every 16")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True, axis='x')
plt.tight_layout()

# Show the plot
plt.show()
