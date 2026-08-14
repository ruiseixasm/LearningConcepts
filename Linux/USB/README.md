# USB Devices

## USB Driver
How to list all plugged drivers
```sh
lsblk
df -h
```

## How to mount drivers
### Mounting  directories
```sh
sudo mkdir -p /mnt/wd_black
sudo mkdir -p /mnt/wd_blue
sudo mkdir -p /mnt/wd_big
```

### How to get the UUID for each USB Drive
Obtain the UUID for each drive like this:
```sh
sudo blkid /dev/sdb1
sudo blkid /dev/sdc1
```

### Configure fstab to mount on start up
Open the configuration file in write mode
```sh
sudo nano /etc/fstab
```

Adjust the configurations for each drive accordingly like this:
```
UUID=BLACK_DISK_UUID /mnt/wd_black ntfs defaults,nofail 0 0
UUID=BLUE_DISK_UUID /mnt/wd_blue ntfs defaults,nofail 0 0
```

## How to do a SMART check on a drive
```sh
sudo smartctl -H /dev/sdX
```

## How to mount the added USB Devices
```sh
sudo mount -a
```

## Globally changing ownership
In case of an ext4 device, to update the ownership of the files, do:
```sh
sudo chown -R rui:rui /mnt/wd_black
```

To set full permissions if necessarilly, do:
```sh
sudo chmod -R 777 /mnt/wd_black
```

