import requests
import json
from collections import defaultdict
from packaging import version

def get_latest_library_descriptions():
    # Download the library index JSON
    url = "https://downloads.arduino.cc/libraries/library_index.json"
    response = requests.get(url)
    data = response.json()
    
    # Group libraries by name
    libraries_by_name = defaultdict(list)
    
    for library in data['libraries']:
        libraries_by_name[library['name']].append(library)
    
    latest_libraries = {}
    
    for name, versions in libraries_by_name.items():
        try:
            # Sort by version using packaging library for proper version comparison
            latest = max(versions, key=lambda x: version.parse(x['version']))
            latest_libraries[name] = {
                'name': latest['name'],
                'version': latest['version'],
                'author': latest.get('author', ''),
                'maintainer': latest.get('maintainer', ''),
                'sentence': latest.get('sentence', ''),
                'paragraph': latest.get('paragraph', ''),
                'website': latest.get('website', ''),
                'category': latest.get('category', ''),
                'architectures': latest.get('architectures', []),
                'dependencies': latest.get('dependencies', []),
                'repository': latest.get('repository', '')
            }
        except Exception as e:
            print(f"Skipping library '{name}' due to version parsing error: {e}")
            continue
    
    return latest_libraries

def save_to_json(data, filename="arduino_libraries_latest.json"):
    with open(filename, 'w') as f:
        json.dump(data, f, indent=2)

if __name__ == "__main__":
    print("Fetching Arduino libraries data...")
    try:
        libraries = get_latest_library_descriptions()
        save_to_json(libraries)
        print(f"Saved {len(libraries)} libraries to 'arduino_libraries_latest.json'")
        print("\nExample entry:")
        print(json.dumps(list(libraries.values())[0], indent=2))
    except Exception as e:
        print(f"Error: {e}")
        