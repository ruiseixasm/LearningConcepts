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

Start by giving the workgroup name like so:
```ini
[global]

## Browsing/Identification ###

# Change this to the workgroup/NT-domain name your Samba server will part of
   workgroup = WORKGROUP
```

Edit Add your shares as follows:

```ini
[MY_Share]
   comment = MX Linux file server
   path = /home/rui/Videos
   browseable = yes
   read only = no
   guest ok = no
   create mask = 0775
   directory mask = 0775
   valid users = rui
```

## Restart the services
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

## Check Windows client PCs workgroups
Open the Windows command line and type:
```sh
net config workstation
```
Check if the names match, if doesn't match, change it like so:
```sh
sysdm.cpl
```

## Mount on other Linux machines
Create a windows mount point
```sh
sudo mkdir /mnt/david
```

Place the login credential in the safe folder `root`
```sh
sudo touch /root/.david_credentials
sudo chmod 600 /root/.david_credentials
sudo nano /root/.david_credentials
```

Add the username and password to the file above
```ini
username=name
password=1234
```

Open the `fstab` file
```sh
sudo nano /etc/fstab
```

Add this line to the `fstab`
```ini
/DAVID/share /mnt/david cifs credentials=/root/.david_credentials,_netdev,nofail 0  0
```

