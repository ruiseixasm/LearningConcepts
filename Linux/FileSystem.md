# File System
## Drives health status and other info
Nowadays HDD aren't CMR anymore, they are SMR, meaning they aren't reliable and can't be mounted with the parameter `big_writes` in `fstab`.
To know if an HDD is CMR or SMR use the `smartctl`.
```sh
sudo apt update && sudo apt install smartmontools -y
lsblk
sudo smartctl -i /dev/sdc
sudo smartctl -d sat -x /dev/sdc
```
If it has TRIM support then it is SMR, the newer and worse kind.

This happens because the industry is all in in SSDs, and so they made the old
HDD ultra cheap and thus unreliable.

Nevertheless, it is possible to connect and external SSD to an old computer
without AHCI support because the internal enclosure board uses the simpler
UASP (USB Attached SCSI Protocol).

How to do a SMART check on a drive
```sh
sudo smartctl -H /dev/sdX
```

## Mount drivers
### List all plugged drivers
```sh
lsblk
df -h
```

### Mounting directories
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
```txt
UUID=BLACK_DISK_UUID /mnt/wd_black ntfs defaults,nofail 0 0
UUID=BLUE_DISK_UUID /mnt/wd_blue ntfs defaults,nofail 0 0
```

The configuration above will use the obsolete and slow `ntfs-3g` via FUSE. To guarantee fast files access, use the `ntfs3` that is integrated in the kernel.

Check first if `ntfs3` is available in the system:
```sh
grep ntfs /proc/filesystems
```

If it returns nothing, then try:
```sh
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
**IMPORTANT NOTE**: Avoid `big_writes` in SMR type of HDDs!

In case it's an *exFAT* drive format, then the configuratio is the following:
```ini
UUID=GREEN_DISK_UUID /mnt/wd_green exfat defaults,umask=000,nofail 0 0
```
Just make sure *exFAT* is installed in your system
```sh
cat /proc/filesystems | grep exfat
```
The system some times needs to be reboot to load `exfat` into kernel after detecting `exfat` drives.
If the system hasn't loaded the exfat yet, type de following:
```sh
sudo modprobe exfat
cat /proc/filesystems | grep exfat
```

### How to mount and unmount added USB devices
To mount drives use one of the following:
```sh
sudo mount -a
sudo mount /dev/sdb1 /media/Destiny/Folder
sudo mount -t ntfs /dev/sdb1 /media/Destiny/Folder
sudo mount -t ntfs -o big_writes /dev/sdb1 /media/Destiny/Folder
```

To get information of an existing mount, type one of the following:
```sh
findmnt /media/Destiny/Folder
findmnt /dev/sdb1
```

To unmount drives use one of the following:
```sh
sudo umount /media/Destiny/Folder
sudo umount /dev/sdb1
```

## Globally changing ownership
In case of an ext4 device, to update the ownership of the files, do:
```sh
sudo chown -R rui:rui /mnt/wd_black
```

To set full permissions if necessarily, do:
```sh
sudo chmod -R 777 /mnt/wd_black
```

## Copying and moving files with rsync
To **copy** a folder from one place to another, do:
```sh
rsync -avh --progress --append-verify /media/Source/Folder/ /media/Destiny/Folder/
```
`rsync` automatically creates the destiny directory `Folder` if non existing.

You can always **test** it first with `dry-run` like so:
```sh
rsync -avh --dry-run --progress --ignore-existing --ignore-errors /media/Source/Folder/ /media/Destiny/Folder/
```

To **move** the command is this instead:
```sh
rsync -avh --progress --append-verify --remove-source-files /media/Source/Folder/ /media/Destiny/Folder/
find /media/Source/Folder/ -type d -empty -delete
```
Because the `rsync` preserves the empty directories (`d`), it is needed to remove those directories afterwards.

## Getting full structure tree
To get the file system tree
```sh
sudo apt install tree
tree /path/to/folder
tree /path/to/folder > structure.txt
```

## How to set drive partitions
Start the graphical partition tool and select the menus accordingly
```sh
sudo cfdisk /dev/sda
```
Don't forget to select **Write** at the end of the process to create the partition.

Finally check the creation of the partition
```sh
sudo lsblk
```

For the targeted partition format it like so
```sh
sudo mkfs.ext4 /dev/sdaX
```

