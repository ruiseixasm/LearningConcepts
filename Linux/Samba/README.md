# File sharing with Samba

## Installation of Samba
```
sudo apt update
sudo apt install samba samba-common-bin -y
sudo smbpasswd -a rui
```

## Opening Firewall
```
sudo ufw allow samba
```

## Sharing folders

Type the command:
```
sudo nano /etc/samba/smb.conf
```

Edit as follows:
```
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
```
sudo service smbd restart
sudo service nmbd restart
```

