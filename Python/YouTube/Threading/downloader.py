# Youtube url: https://youtu.be/8C9IJEuQjhY?si=j5A8BWOkr_oZG-DH&t=335
"""Python threads aren't truly parallel, but are still useful for I/O bound tasks"""
import threading
import requests
from pathlib import Path

def download_file(url, filename):
    # In order to work run it in the command line on the same folder as this file
    print(f"Downloading {url} to {filename}")
    response = requests.get(url)
    Path(filename).write_bytes(response.content)
    print(f"Finished downloading {filename}")

base_url = "https://raw.githubusercontent.com/JacobCallahan/Understanding/5ce7a78e0af02abbf164a451ff79f63b6ddc88bb/Python/file_io"
urls = [
    f"{base_url}/binary_file",
    f"{base_url}/files.py",
    f"{base_url}/names.txt",
    f"{base_url}/new_file.txt"
]

threads = []
for url in urls:
    filename = "downloads/" + url.split("/")[-1]
    t = threading.Thread(target=download_file, args=(url, filename))
    t.start()
    threads.append(t)

[t.join() for t in threads]
