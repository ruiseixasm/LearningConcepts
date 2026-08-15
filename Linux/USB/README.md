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

If the access is locked by other user, type:
```sh
sudo rm /etc/.fstab.swp
```

Adjust the configurations for each drive accordingly like this:
```
UUID=BLACK_DISK_UUID /mnt/wd_black ntfs defaults,nofail 0 0
UUID=BLUE_DISK_UUID /mnt/wd_blue ntfs defaults,nofail 0 0
```

The configuration above will use the obsolete and slow `ntfs-3g` via FUSE. To guarantee fast files access, use the `ntfs3` that is integrated in the kernel.

Check first if `ntfs3` is available in the system:
```sh
grep ntfs /proc/filesystems
```

If it returns nothing, then try:
```
modinfo ntfs3
```

Then enable it by rewriting the lines above as so:
```
UUID=BLACK_DISK_UUID /mnt/wd_black ntfs3 defaults,nofail 0 0
UUID=BLUE_DISK_UUID /mnt/wd_blue ntfs3 defaults,nofail 0 0
```

In case the `ntfs3` not being present in the Linux Kernel, then it is better to use `big_writes` on the `fstab` configuration file, to overcome the default of 4KB block limit, like so:
```ini
UUID=BLACK_DISK_UUID /mnt/wd_black ntfs defaults,big_writes,nofail 0 0
UUID=BLUE_DISK_UUID /mnt/wd_blue ntfs defaults,big_writes,nofail 0 0
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

