# Network File System

## Installation
```sh
sudo apt update
sudo apt install nfs-kernel-server -y
```

## Set share permissions
Open the configuration file like so:
```sh
sudo nano /etc/exports
```

Then, add one line per access like so:
```ini
/mnt/share_nfs  192.168.1.*(ro,sync,no_subtree_check)
```
Because there is no authentication in NFS, it's advisable to leave it as read-only (`ro`)

In case of writing files use the sftp instead, use the the address like so in the path field.
```path
sftp://user@host/
```

## Open the needed firewall ports
```sh
sudo ufw allow from 192.168.1.0/24 to any port nfs
```

## Activate the share
```sh
sudo exportfs -arv
```


