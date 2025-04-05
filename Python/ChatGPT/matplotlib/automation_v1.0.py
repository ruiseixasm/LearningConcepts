import matplotlib.pyplot as plt

# Generate integer points from 0 to 127
x = list(range(128))
y = x  # In this case, y = x, just for demonstration

# Create the plot
plt.figure(figsize=(12, 4))
plt.plot(x, y, marker='o', linestyle='-', color='blue', markersize=4)

# Enhance the chart
plt.title("Integer Points from 0 to 127")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True)
plt.xticks(range(0, 128, 8))  # Optional: ticks every 8 for readability
plt.tight_layout()

# Show the plot
plt.show()
