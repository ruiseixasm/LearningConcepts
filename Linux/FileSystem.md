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

## Copying and moving files with rsync


To **copy** a folder from one place to another, do:
```sh
rsync -avh --progress --append-verify /media/Source/Folder/ /media/Destiny/Folder/
```

You can always **test** it first by doing so:
```sh
rsync -avh --progress --ignore-existing --ignore-errors /media/Source/Folder/ /media/Destiny/Folder/
```

To **move** the command is this instead:
```sh
rsync -avh --progress --append-verify --remove-source-files /media/Source/Folder/ /media/Destiny/Folder/
find /media/Source/Folder/ -type d -empty -delete
```
Because the `rsync` preserves the empty directories (`d`), it is needed to remove those directories afterwards.
