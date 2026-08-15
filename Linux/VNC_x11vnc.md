# How to install the VNC x11vnc

## Installation
```sh
sudo apt update
sudo apt install x11vnc -y
```

## Configuration
```sh
x11vnc -storepasswd
```

## Open the firewall port 5900
```sh
sudo ufw allow 5900/tcp
```

## Starting up
```sh
x11vnc -auth guess -forever -loop -noxdamage -repeat -rfbauth ~/.vnc/passwd -rfbport 5900 -shared
```

## Create a handy script to start it on demand
```sh
nano ~/vnc-start
```

Edit the script like so:
```sh
#!/bin/bash
echo "A iniciar o servidor VNC seguro na porta 5900..."
x11vnc -auth guess -forever -loop -noxdamage -repeat -rfbauth ~/.vnc/passwd -rfbport 5900 -shared -bg
```

Set the file as executable.
```sh
chmod +x ~/vnc-start
```

To be able to call it from any place and not just from Scripts, move it to bin.
```sh
sudo mv ~/vnc-start /usr/local/bin/
```

