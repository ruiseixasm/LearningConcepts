import json
from plotly.graph_objs import Scattergeo, Layout # v.5
from plotly import offline # v.5

# Explore the structure of the data.
filename = 'data/eq_data_1_day_m1.json'
with open(filename) as f:
    all_eq_data = json.load(f)

all_eq_dicts = all_eq_data['features'] # v.2

mags, lons, lats = [], [], [] # v.3 v.4
for eq_dict in all_eq_dicts: # v.3
    mag = eq_dict['properties']['mag']
    lon = eq_dict['geometry']['coordinates'][0] # v.4
    lat = eq_dict['geometry']['coordinates'][1] # v.4
    mags.append(mag)
    lons.append(lon) # v.4
    lats.append(lat) # v.4

# Map the earthquakes.
data = [Scattergeo(lon=lons, lat=lats)] # v.5
my_layout = Layout(title='Global Earthquakes') # v.5

fig = {'data': data, 'layout': my_layout} # v.5
offline.plot(fig, filename='global_earthquakes.html') # v.5