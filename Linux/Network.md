# Multiple Network configurations

## Change the Computer name
In order for the computer be seen with a specific name, do the following:
```sh
sudo hostnamectl set-hostname david
```

Or for older OS, edit the `hostname` file by replacing the existing name.
```sh
sudo nano /etc/hostname
```

Then, update the `hosts` files accordingly.
```sh
sudo nano /etc/hosts
```

Update the new name with this command without rebooting:
```sh
sudo hostname david
```

