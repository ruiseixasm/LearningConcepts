import csv
from datetime import datetime # v.5
import matplotlib.pyplot as plt # v.4

filename = 'data/sitka_weather_2018_simple.csv' # v.6
with open(filename) as f:
    reader = csv.reader(f)
    header_row = next(reader)

    # Get dates, and high and low temperatures from this file.
    dates, highs, lows = [], [], [] # v.3 v.4 v.l.1
    for row in reader: # v.3
        current_date = datetime.strptime(row[2], '%Y-%m-%d') # v.5
        high = int(row[5])
        low = int(row[6]) # v.l.1
        dates.append(current_date) # v.5
        highs.append(high)
        lows.append(low)

# Plot the high and low temperatures.
plt.style.use('seaborn') # v.4
fig, ax = plt.subplots() # v.4
ax.plot(dates, highs, c='red') # v.4 v.5
ax.plot(dates, lows, c='blue') # v.l.1

# Format plot.
ax.set_title("Daily high and low temperatures - 2018", fontsize=24) # v.4 v.6 v.l.1
ax.set_xlabel('', fontsize=16) # v.4
fig.autofmt_xdate() # v.5
ax.set_ylabel("Temperature (F)", fontsize=16) # v.4
ax.tick_params(axis='both', which='major', labelsize=16) # v.4

plt.show() # v.4