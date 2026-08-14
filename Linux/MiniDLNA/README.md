# Installation of the MiniDLNA
```
sudo apt update
sudo apt install minidlna -y
```

# Configuration of the MiniDLNA
Open the configuration file like so:
```
sudo nano /etc/minidlna.conf
```
Look for the line with `media_dir=` and set it as:
```
media_dir=V,/mnt/nas_disco
```

To have a friendly fire it's possible to edit it here>
```
friendly_name=NAS_MiniDLNA
```

To the DLNA server detect new files set:
```
inotify=yes
```

# Allow the service by the Firewall
```
sudo ufw allow 1900/udp
sudo ufw allow 8200/tcp
```

# Restart the DLNA server
```
sudo service minidlna restart
```
