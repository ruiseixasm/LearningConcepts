import requests

# Make an API call and store the response.
url = 'https://api.github.com/search/repositories?q=language:python&sort=stars'
headers = {'Accept': 'application/vnd.github.v3+json'}
r = requests.get(url, headers=headers)
print(f"Status code: {r.status_code}")

# Store API response in a variable.
response_dict = r.json()
print(f"Total repositories: {response_dict['total_count']}") # v.2

# Explore information about the repositories.
repo_dicts = response_dict['items'] # v.2
print(f"Repositories returned: {len(repo_dicts)}") # v.2

# Examine the first repository.
repo_dict = repo_dicts[0] # v.2
print(f"\nKeys: {len(repo_dict)}") # v.2
for key in sorted(repo_dict.keys()): # v.2
    print(key)