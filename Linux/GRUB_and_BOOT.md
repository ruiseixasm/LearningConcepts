# Change default Boot in Linux (GRUB)

- Type `sudo nano /etc/default/grub`
- Find the line that says `GRUB_DEFAULT=0`
- Change the value `0` to the value `1`, the second OS.
- Finally update the grub with `sudo update-grub`

# Enable Auto-Login
To enable the auto-login open the following configuration file:
```sh
sudo nano /etc/lightdm/lightdm.conf
```

And edit the following line:
```ini
autologin-user=rui
autologin-user-timeout=0
```
The last line avoids delays to start the user session

