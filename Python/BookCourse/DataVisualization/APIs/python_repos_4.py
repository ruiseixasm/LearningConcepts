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

print("\nSelected information about each repository:") # v.3 v.4
for repo_dict in repo_dicts: # v.4
    print(f"\nName: {repo_dict['name']}") # v.3 v.4
    print(f"Owner: {repo_dict['owner']['login']}") # v.3
    print(f"Stars: {repo_dict['stargazers_count']}") # v.3
    print(f"Repository: {repo_dict['html_url']}") # v.3
    print(f"Created: {repo_dict['created_at']}") # v.3
    print(f"Updated: {repo_dict['updated_at']}") # v.3
    print(f"Description: {repo_dict['description']}") # v.3