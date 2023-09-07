from plotly.graph_objs import Bar, Layout # v.3
from plotly import offline # v.3
from die import Die

# Create two D6 dice.
die_1 = Die() # v.4
die_2 = Die() # v.4


# Make some rolls, and store results in a list.
results = []
for roll_num in range(1000): # v.2
    result = die_1.roll() + die_2.roll() # v.4
    results.append(result)

# Analyze the results.
frequencies = [] # v.2
max_result = die_1.num_sides + die_2.num_sides # v.4
for value in range(2, max_result + 1): # v.2 v.4
    frequency = results.count(value)
    frequencies.append(frequency)


# Visualize the results.

# DATA
x_values = list(range(2, max_result + 1)) # v.3 v.4
data = [Bar(x=x_values, y=frequencies)] # v.3

# LAYOUT
x_axis_config = {'title': 'Result', 'dtick': 1} # v.3 v.4
y_axis_config = {'title': 'Frequency of Result'} # v.3
my_layout = Layout(title='Results of rolling two D6 dice 1000 times',
                   xaxis=x_axis_config, yaxis=y_axis_config) # v.3 v.4

# PLOT OFFLINE HTML
offline.plot({'data': data, 'layout': my_layout}, filename='d6_d6.html') # v.3 v.4

print(frequencies) # v.2