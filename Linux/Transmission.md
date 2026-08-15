# To install Transmission

## Installation
```sh
sudo apt install transmission-daemon transmission-cli -y
```

## Stop Transmission Service
Use one of the commands bellow accordingly to your OS.
```sh
sudo systemctl stop transmission-daemon
sudo service transmission-daemon stop
```

## Configuration
Open the configuration file:
```sh
sudo nano /etc/transmission-daemon/settings.json
```
Edit or add the lines missing bellow:
```json
{
    "download-dir": "/mnt/windows/LinuxShare/Torrent/Downloads",
	"incomplete-dir": "/mnt/windows/LinuxShare/Torrent/Incomplete",
    "rpc-password": "user_password",
	"rpc-username": "user_name",
	"rpc-whitelist": "127.0.0.1,192.168.1.*",
	"utp-enabled": true,
    "watch-dir": "/mnt/windows/LinuxShare/Torrent/Torrents",
    "watch-dir-enabled": true
}
```

## Open the firewall ports
Open the local Web server ports
```sh
sudo ufw allow from 192.168.1.0/24 to any port 9091
```
Open the Torrent Protocol ports
```sh
sudo ufw allow 51413/tcp
sudo ufw allow 51413/udp
sudo ufw reload
```

## Restart the Torrent service
Use one of the commands bellow accordingly to your OS.
```sh
sudo systemctl start transmission-daemon
sudo service transmission-daemon start
```

## Check the service is running
```sh
sudo service transmission-daemon status
```

## Access via web
Type on a browser the following address and do the login
```http
http://192.168.1.50:9091
```
