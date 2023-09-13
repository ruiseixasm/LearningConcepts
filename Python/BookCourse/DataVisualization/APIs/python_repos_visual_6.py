import requests
from plotly.graph_objs import Bar # v.5
from plotly import offline # v.5

# Make an API call and store the response.
url = 'https://api.github.com/search/repositories?q=language:python&sort=stars'
headers = {'Accept': 'application/vnd.github.v3+json'}
r = requests.get(url, headers=headers)
print(f"Status code: {r.status_code}")

# Process results.
response_dict = r.json()
repo_dicts = response_dict['items'] # v.2
repo_names, stars = [], [] # v.5
for repo_dict in repo_dicts: # v.4
    repo_names.append(repo_dict['name']) # v.5
    stars.append(repo_dict['stargazers_count']) # v.5

# Make visualization.
data = [{
    'type': 'bar',
    'x': repo_names,
    'y': stars,
    'marker': {
        'color': 'rgb(60, 100, 150)',
        'line': {'width': 1.5, 'color': 'rgb(25, 25, 25)'}
    },
    'opacity': 0.6
}] # v.5 v.6

my_layout = {
    'title': 'Most-Starred Python Projects on GitHub',
    'titlefont': {'size': 28},
    'xaxis': {
        'title': 'Repository',
        'titlefont': {'size': 24},
        'tickfont': {'size': 14}
    },
    'yaxis': {
        'title': 'Stars',
        'titlefont': {'size': 24},
        'tickfont': {'size':14}
        }
} # v.5 v.6

fig = {'data': data, 'layout': my_layout} # v.5
offline.plot(fig, filename='python_repos.html') # v.5