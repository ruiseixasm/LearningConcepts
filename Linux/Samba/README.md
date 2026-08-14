# File sharing with Samba

## Installation of Samba
```sh
sudo apt update
sudo apt install samba samba-common-bin -y
sudo smbpasswd -a rui
```

## Opening Firewall
```sh
sudo ufw allow samba
```

## Sharing folders
Type the command:
```sh
sudo nano /etc/samba/smb.conf
```

Edit as follows:
```ini
[NAS]
   comment = MX Linux file server
   path = /home/rui/Videos
   browseable = yes
   read only = no
   guest ok = no
   create mask = 0775
   directory mask = 0775
   valid users = rui
```

## Reboot the service
```sh
sudo service smbd restart
sudo service nmbd restart
```

## Verify the installation
```sh
sudo service nmbd status
sudo service smbd status
```

## Enable the NetBIOS in other distros
In order to make the share discoverable, add the NetBIOS to the running services, like so:
```sh
sudo systemctl enable --now nmb
```

