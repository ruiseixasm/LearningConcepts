# Linux Configuration
## Startup program
### Via `autostart`
Create and open the `autostart` file
```sh
vi ~/.config/autostart/vnc-server.desktop
```
Add the following lines
```ini
[Desktop Entry]
Type=Application
Name=VNC Server Start
Exec=vnc-start
Icon=dialog-information
X-GNOME-Autostart-enabled=true
```

### Via `systemd`
To start up as a service do
```sh
mkdir -p ~/.config/systemd/user/
vi ~/.config/systemd/user/vnc.service
```
Add the following lines to it
```ini
[Unit]
Description=Start VNC after graphical login
# Requires that the user session starts
Requires=graphical-session.target
After=graphical-session.target

[Service]
Type=simple
ExecStart=/usr/bin/vnc-start
Restart=on-failure
# SAFETY PARAMETERS TO AVOID ENLDESS LOOP:
RestartSec=10s
StartLimitIntervalSec=100s
StartLimitBurst=3

[Install]
WantedBy=graphical-session.target
```
Enable and start the service
```sh
systemctl --user enable vnc.service
systemctl --user start vnc
systemctl --user status vnc
```

### Via `SysVinit`
Add the needed `init` file
```sh
sudo vi /etc/init.d/vnc-server
```
Add the following lines
```sh
#!/bin/sh
### BEGIN INIT INFO
# Provides:          vnc-server
# Required-Start:    $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
### END INIT INFO

case "$1" in
  start)
    echo "Starting VNC Server..."
    # Executes in background as user rui
    su - rui -c "/usr/bin/vnc-start &"
    ;;
  stop)
    echo "Stoping VNC Server..."
    killall vnc-start
    ;;
  restart)
    $0 stop
    $0 start
    ;;
  *)
    echo "Use: /etc/init.d/vnc-server {start|stop|restart}"
    exit 1
    ;;
esac

exit 0
```
Enable the new start up script
```sh
sudo chmod +x /etc/init.d/vnc-server
sudo update-rc.d vnc-server defaults
```
And finally, start the service
```sh
sudo service vnc-server start
```


