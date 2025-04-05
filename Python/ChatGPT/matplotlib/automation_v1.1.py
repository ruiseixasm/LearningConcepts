import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # Just using y = x for this example

# Create the plot
plt.figure(figsize=(12, 4))
plt.plot(x, y, marker='o', linestyle='-', color='blue', markersize=4)

# Add horizontal lines
plt.axhline(y=64, color='gray', linestyle='--', linewidth=1.5, label='Midpoint (64)')
plt.axhline(y=127, color='red', linestyle='-', linewidth=2, label='Max (127)')

# Enhance the chart
plt.title("Integer Points from 0 to 127")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True)
plt.xticks(range(0, 128, 8))
plt.legend()
plt.tight_layout()

# Show the plot
plt.show()
