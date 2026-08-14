# Install SSH

The commands bellow do the following:
- Update the available repositories
- Install the last ssh version
- Initiate the local service
- Adds as a startup service for future reboots
- Opens the ssh port in the firewall

```
sudo apt update
sudo apt install openssh-server -y
sudo service ssh start
sudo update-rc.d ssh enable
sudo ufw allow ssh
```
