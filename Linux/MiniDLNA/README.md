# Installation of the MiniDLNA
```sh
sudo apt update
sudo apt install minidlna -y
```

# Configuration of the MiniDLNA
Open the configuration file like so:
```sh
sudo nano /etc/minidlna.conf
```

Look for the line with `media_dir=` and set it as:
```ini
media_dir=V,/mnt/nas_video
media_dir=A,/mnt/nas_music
```

To have a friendly fire it's possible to edit it here:
```ini
friendly_name=NAS_MiniDLNA
```

To the DLNA server detect new files set:
```ini
inotify=yes
```

Alow the following of sym links to open the files on other folders outside the media_dirs
```ini
wide_links=yes
```

# Create symbolic links

To make the name of folders more explicit, use symbolic links, like so:
```sh
ln -s [target_file] [link_name]
```
The `link_name` can be the entire path.

# Allow the service by the Firewall
```sh
sudo ufw allow 1900/udp
sudo ufw allow 8200/tcp
```

# Restart the DLNA server
```sh
sudo service minidlna restart
```

# Check server status
In case the first doesn't work, try the second.
```sh
sudo systemctl status minidlna
sudo service minidlna status
```

