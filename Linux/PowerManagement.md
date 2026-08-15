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

