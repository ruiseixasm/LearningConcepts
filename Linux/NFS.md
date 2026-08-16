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
/mnt/share_nfs  192.168.1.*(rw,sync,no_subtree_check)
```

## Open the needed firewall ports
```sh
sudo ufw allow from 192.168.1.0/24 to any port nfs
```

## Activate the share
```sh
sudo exportfs -arv
```


