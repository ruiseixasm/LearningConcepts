import json

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

print(mags[:10]) # v.2 v.3
print(lons[:5]) # v.4
print(lats[:5]) # v.4