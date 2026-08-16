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

To remove the useless initial folders Pictures, Music and Video, set:
```ini
root_container=B
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
Choose the one that works on your system bellow:
```sh
sudo service minidlna restart
sudo systemctl restart minidlna
```

# Check server status
In case the first doesn't work, try the second.
```sh
sudo systemctl status minidlna
sudo service minidlna status
```

# Rescan folders
In order to remove older folders, type:
```sh
sudo systemctl stop minidlna
sudo minidlnad -r
sudo systemctl start minidlna
```
or
```sh
sudo service minidlna stop
sudo minidlnad -r
sudo service minidlna start
```

Note: If you use -R instead, then it deletes the entire database and reconstructs it completely.
