from plotly.graph_objs import Bar, Layout # v.3
from plotly import offline # v.3
from die import Die

# Create a D6.
die = Die()

# Make some rolls, and store results in a list.
results = []
for roll_num in range(1000): # v.2
    result = die.roll()
    results.append(result)

# Analyze the results.
frequencies = [] # v.2
for value in range(1, die.num_sides + 1): # v.2
    frequency = results.count(value)
    frequencies.append(frequency)


# Visualize the results.

# DATA
x_values = list(range(1, die.num_sides + 1)) # v.3
data = [Bar(x=x_values, y=frequencies)] # v.3

# LAYOUT
x_axis_config = {'title': 'Result'} # v.3
y_axis_config = {'title': 'Frequency of Result'} # v.3
my_layout = Layout(title='Results of rolling one D6 1000 times',
                   xaxis=x_axis_config, yaxis=y_axis_config) # v.3

# PLOT OFFLINE HTML
offline.plot({'data': data, 'layout': my_layout}, filename='d6.html') # v.3

print(frequencies) # v.2