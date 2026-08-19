# Installation
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

# Mount
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

## Mount in a Windows machine
To associate to a mounting driver
```sh
net use Z: \\david\WD_Black /user:rui *
```

# Troubleshoot
## Logs monitoring
Open the Samba config file
```sh
sudo nano /etc/samba/smb.conf
```

Then add this line
```ini
# Set the log level, by default is 1
   log level = 5
```

Make sure the smbclient is installed
```sh
sudo apt update
sudo apt install smbclient
which smbclient
```

Try to login to the self machine
```sh
sudo smbclient -L localhost -U rui
```

Start monitoring the logs of the respective machine, like so
```sh
sudo ls -l /var/log/samba
sudo tail -f /var/log/samba/log.192.168.1.213
```
Note, for failed logins the log registers by IP

Check authentication database
```sh
sudo pdbedit -L -v | grep -A 20 '^Unix username:.*rui'
```

## Check Linux client computers
```sh
which smbclient
```
If it isn't installed, install it as shown above.

Try to login to the Samba server
```sh
smbclient -L //david -U rui
```

Enter in command line
```sh
smbclient //david/WD_Black -U rui
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

Check all the kept keys
```sh
cmdkey /list
```

Delete a specific key
```sh
cmdkey /delete:david
cmdkey /list | findstr /I "david"
```

User parameters
```sh
whoami
whoami /user
```

Delete all exiting cached Samba logins
```sh
net use * /delete /y
```


