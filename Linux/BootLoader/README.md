# Change default Boot in Linux (GRUB)

- Type `sudo nano /etc/default/grub`
- Find the line that says `GRUB_DEFAULT=0`
- Change the value `0` to the value `1`, the second OS.
- Finally update the grub with `sudo update-grub`

