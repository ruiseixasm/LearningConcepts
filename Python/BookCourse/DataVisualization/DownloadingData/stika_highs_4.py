import csv
import matplotlib.pyplot as plt # v.4

filename = 'data/sitka_weather_07-2018_simple.csv'
with open(filename) as f:
    reader = csv.reader(f)
    header_row = next(reader)

    # Get high temperatures from this file.
    highs = [] # v.3
    for row in reader: # v.3
        high = int(row[5])
        highs.append(high)

# Plot the high temperatures.
plt.style.use('seaborn') # v.4
fig, ax = plt.subplots() # v.4
ax.plot(highs, c='red') # v.4

# Format plot.
ax.set_title("Daily high temperatures, July 2018", fontsize=24) # v.4
ax.set_xlabel('', fontsize=16) # v.4
ax.set_ylabel("Temperature (F)", fontsize=16) # v.4
ax.tick_params(axis='both', which='major', labelsize=16) # v.4

plt.show() # v.4