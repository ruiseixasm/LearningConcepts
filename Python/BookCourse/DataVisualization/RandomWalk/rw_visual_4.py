import matplotlib.pyplot as plt
from random_walk import RandomWalk


# Keep making new walks, as long as the program is active.
while True: # v.2
    # Make a random walk.
    rw = RandomWalk()
    rw.fill_walk()

    # Plot the points in the walk.
    plt.style.use('classic')
    fig, ax = plt.subplots()
    point_numbers = range(rw.num_points) # v.3
    ax.scatter(rw.x_values, rw.y_values, c=point_numbers, cmap=plt.cm.Blues, edgecolors='none', s=15) # v.3

    # Emphasize the first and last point.
    ax.scatter(0, 0, c='green', edgecolors='none', s=100) # v.4
    ax.scatter(rw.x_values[-1], rw.y_values[-1], c='red',edgecolors='none', s=100) # v.4

    plt.show()

    keep_running = input("Make another walk? (y/n): ") # v.2
    if keep_running == 'n': # v.2
        break