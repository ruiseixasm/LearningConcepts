import requests
import json

# Make an API call, and store the response.
# From: https://github.com/HackerNews/API
url = 'https://hacker-news.firebaseio.com/v0/item/8863.json'
r = requests.get(url)
print(f"Status code: {r.status_code}")

# Explore the structure of the data.
response_dict = r.json()
readable_file = 'readable_hn_data.json' # output file
with open(readable_file, 'w') as f:
    json.dump(response_dict, f, indent=4)