import matplotlib.pyplot as plt

# Fewer, non-linear points
x = [0, 10, 25, 40, 60, 80, 100, 120]
y = [10, 50, 30, 90, 40, 70, 60, 100]

plt.figure(figsize=(12, 4))

# Stepped line connecting the points
plt.plot(x, y, linestyle='-', drawstyle='steps-post', color='lightblue', linewidth=2, label='Stepped Interpolation')

# Actual data points
plt.plot(x, y, marker='o', linestyle='None', color='blue', markersize=6, label='Data Points')

# Dashed horizontal lines at multiples of 16 (except 64)
for i in range(0, 129, 16):
    if i != 64:
        plt.axhline(y=i, color='gray', linestyle='--', linewidth=1)

# Solid line at y = 64
plt.axhline(y=64, color='gray', linestyle='-', linewidth=1.5)

# Axis limits
plt.ylim(-1, 128)
plt.xlim(0, 128)

# Ticks
plt.xticks(range(0, 129, 8))
plt.yticks(range(0, 129, 16))

# Labels
plt.title("Stepped Line Connecting Non-linear Points")
plt.xlabel("Index")
plt.ylabel("Value")
plt.grid(True, axis='x')
plt.tight_layout()
plt.legend()

plt.show()
