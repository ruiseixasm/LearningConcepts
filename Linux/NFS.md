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
Because there is no authentication in NFS, it's advisable to leave it as read-only (`ro`).

In case of writing files use the sftp instead, use the the address like so in the path field.
```path
sftp://user@host/
```

## Open the needed firewall ports
```sh
sudo ufw allow from 192.168.1.0/24 to any port nfs
```
To check all added ports to the firewall, type:
```sh
sudo ufw status numbered
```
Note: To remove any wrong set range of IPs, do:
```sh
sudo ufw delete allow from 192.168.2.0/24 to any port nfs
```

## Activate the share
```sh
sudo exportfs -arv
```

Restart the NFS server accordingly to the OS.
```sh
sudo systemctl restart nfs-kernel-server
sudo service nfs-kernel-server restart
```

## How to mount a NFS folder on the Client side

Install the NFS client common files
```sh
sudo apt update
sudo apt install nfs-common -y
```

Create the mount directory.
```sh
sudo mkdir -p /media/nfs_host
```

Mount the remote `nfs` share in it.
```sh
sudo mount -t nfs -o ro server_ip:/mnt/nfs_share /media/nfs_host
```

To a definitive mount, add this line to the `/etc/fstab`.
```ini
server_ip:/mnt/share_nfs  /media/nfs_host  nfs  ro,defaults,timeo=14,noatime,_netdev  0  0
```

Check everything is working with a list on the mount directory.
```sh
ls -la /media/nfs_host
```

Unmount it whenever needed.
```sh
sudo umount /media/nfs_host
```

