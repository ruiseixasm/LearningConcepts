import matplotlib.pyplot as plt
import numpy as np

# Define the range of x values
x = np.linspace(-10, 10, 100)

# Compute the corresponding y values
y = x**2

# Plot the function
plt.plot(x, y)
plt.title('Graph of y = x^2')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True)
plt.show()
