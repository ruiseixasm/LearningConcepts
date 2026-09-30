# Command Examples

* ['chmod'](#chmod)
* ['chown'](#chown)
* [`find`](#find)

## `chmod`
Changes all permissions with the write removed to other users than the owner
```sh
chmod 755 --recursive .
```
* read  - 100 = 4
* write - 010 = 2
* run   - 001 = 1
Adding the binary values together, or `|` operation, gives the final configuration

## `chown`
Changes the ownership of all files inside the present folder
```sh
sudo chown rui:rui --recursive .
```

## `find`
### Find a file
Finds the file with the expression *alien* in it
```sh
find . -type f -iname '*alien*'
```
### Remove all empty Directories
```sh
find /mnt/data/Directory/ -type d -empty -delete
```


