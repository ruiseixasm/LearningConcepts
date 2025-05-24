import requests
import json
from collections import defaultdict
import re
from packaging import version

def normalize_version(ver_string):
    """Handle special version formats in Arduino libraries"""
    # Remove common suffixes that break version parsing
    ver_string = re.sub(r'[-_](beta|rc|alpha|arduino|release|final|foxy|humble)', 
                       '', ver_string, flags=re.IGNORECASE)
    # Remove remaining non-numeric suffixes (e.g., '1.2.3-fork' -> '1.2.3')
    ver_string = re.sub(r'[-_][a-z].*$', '', ver_string, flags=re.IGNORECASE)
    return ver_string.strip()

def version_key(lib):
    """Extract version key with fallback for problematic versions"""
    ver = lib['version']
    try:
        # First try with normalized version
        return version.parse(normalize_version(ver))
    except:
        try:
            # Fallback to direct parsing
            return version.parse(ver)
        except:
            # Final fallback - use string comparison
            return ver

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
    skipped_count = 0
    
    for name, versions in libraries_by_name.items():
        try:
            # Sort by version using our special key function
            latest = max(versions, key=version_key)
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
            skipped_count += 1
            continue
    
    if skipped_count > 0:
        print(f"Note: Skipped {skipped_count} libraries with problematic version formats")
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
        