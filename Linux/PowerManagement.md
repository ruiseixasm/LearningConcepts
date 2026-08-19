# Power Management

## Power Button
### With systemctl
Open the login configuration file.
```sh
sudo nano /etc/systemd/logind.conf
```

Search for the field `HandlePowerKey` make it like so:
```ini
HandlePowerKey=suspend
```

Restart the service to apply the changes.
```sh
sudo systemctl restart systemd-logind
```

### Via XFCE
Open the login configuration file.
```sh
sudo nano /etc/acpi/events/powerbtn
```

Add the following configuration
```ini
event=button/power
#action=/etc/acpi/powerbtn.sh
action=/usr/sbin/pm-suspend
```

Restart the service
```sh
sudo service acpid restart
```

### Troubleshooting
In case of a suspend after waking up, double waking up needed.

#### Solution 1
If you are using a laptop, Linux often misreads the physical lid state upon resume. Forcing the kernel to assume the lid is open at startup stops this loop.
```sh
sudo nano /etc/default/grub
```

Add `button.lid_init_state=open` to the end of the parameters inside the quotes. For example:
```ini
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash button.lid_init_state=open"
```

Update your bootloader so the changes take effect:
```sh
sudo update-grub
```

#### Solution 2
If you are using MX Linux with systemd enabled (or its shim), `logind` might be fighting your desktop environment (like XFCE, KDE, or Fluxbox) over who gets to sleep the computer. You should let your desktop control it instead.
```sh
sudo nano /etc/systemd/logind.conf
```

Change these lines to ignore and remove the `#` symbol if present:
```ini
HandleLidSwitch=ignore
HandleLidSwitchExternalPower=ignore
```

Then restart the logind service (or just reboot your computer):
```sh
sudo systemctl restart systemd-logind
sudo service acpid restart
```

You can view what devices are allowed to trigger power states by running:
```sh
cat /proc/acpi/wakeup
```

#### Solution 3
Check the power logs
```sh
sudo grep -E -i "suspend|wake|acpi|button|thermal|crit" /var/log/syslog | tail -n 20
```

Manage the LightDM
```sh
sudo nano /etc/lightdm/lightdm.conf
```

Add the following configuration line in the section `[LightDM]`:
```ini
lock-screen-on-suspend=false
```

Apply the configurations:
```sh
sudo service lightdm restart
```

#### Solution 4 (XFCE redundant suspend command)
Because XFCE is already sending the suspend command.

So, the acpi command isn't needed anymore.
```sh
sudo nano /etc/acpi/events/powerbtn
```

Comment the line
```ini
#action=/usr/sbin/pm-suspend
```

Restart the `acpid`
```sh
sudo service acpid restart
```

On the other hand, it's possible to edit the XFCE configuration instead.

Search for the targeted configuration
```sh
grep -i -C 2 'button' ~/.config/xfce4/xfconf/xfce-perchannel-xml/xfce4-power-manager.xml
```
Edit it like so:
```sh
~/.config/xfce4/xfconf/xfce-perchannel-xml/xfce4-power-manager.xml
```
Then edit the respective field to `0`
```ini
<property name="power-button-action" type="uint" value="1"/>
```

Finally restart the XCFE power management
```sh
xfce4-power-manager --restart
```

## Suspend command
To suspend the computer remotely, do one of the following commands
```sh
systemctl suspend
sudo pm-suspend
```
