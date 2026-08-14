# USB Devices

## USB Driver
How to list all plugged drivers
```
lsblk
df -h
```

## How to mount drivers
### Mounting  directories
```
sudo mkdir -p /mnt/wd_black
sudo mkdir -p /mnt/wd_blue
sudo mkdir -p /mnt/wd_big
```

### How to get the UUID for each USB Drive
Obtain the UUID for each drive like this:
```
sudo blkid /dev/sdb1
sudo blkid /dev/sdc1
```

### Configure fstab to mount on start up
Open the configuration file in write mode
```
sudo nano /etc/fstab
```

Adjust the configurations for each drive accordingly like this:
```
UUID=BLACK_DISK_UUID /mnt/wd_black ntfs defaults,nofail 0 0
UUID=BLUE_DISK_UUID /mnt/wd_blue ntfs defaults,nofail 0 0
```



