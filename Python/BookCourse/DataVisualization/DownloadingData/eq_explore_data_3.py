import json

# Explore the structure of the data.
filename = 'data/eq_data_1_day_m1.json'
with open(filename) as f:
    all_eq_data = json.load(f)

all_eq_dicts = all_eq_data['features'] # v.2

mags = [] # v.3
for eq_dict in all_eq_dicts: # v.3
    mag = eq_dict['properties']['mag']
    mags.append(mag)

print(mags[:10]) # v.2 v.3