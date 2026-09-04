# Manage partitions
Open the command line as Administrator, and start the partition tool
```sh
diskpart
```
Then in **DISKPART**, list all the existing disks in order to pick the right disk
```sh
list disk
```
Select the target disk, make sure it's the intended disk
```sh
select disk 1
```
List all existing partitions
```sh
list partition
```
Select the partition intended to be processed
```sh
select partition 1
```
Delete the selected partition
```sh
delete partition override
```
The parameter `override` is needed whenever it is a Recovery partition

Finally, exit the program
```sh
exit
```
