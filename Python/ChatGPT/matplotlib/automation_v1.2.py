import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # Using y = x for demonstration

# Create the plot
plt.figure(figsize=(12, 4))
plt.plot(x, y, marker='o', linestyle='-', color='blue', markersize=4)

# Add horizontal grid lines at multiples of 16
for i in range(0, 128, 16):
    plt.axhline(y=i, color='gray', linestyle='--', linewidth=1)

# Add a bold top line at 127
plt.axhline(y=127, color='red', linestyle='-', linewidth=2, label='Max (127)')

# Enhance the chart
plt.title("Integer Points from 0 to 127 with Horizontal Lines Every 16")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True, axis='x')  # Only vertical grid for x, since we manually add horizontal lines
plt.xticks(range(0, 128, 8))
plt.yticks(range(0, 128, 16))
plt.tight_layout()

# Show the plot
plt.show()
