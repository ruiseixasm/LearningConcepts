# cron/anacron
To add a job in MX Linux do
```sh
sudo nano /etc/anacrontab
```
Then add the following lines
```ini
7    5    weekly-backup    /path/to/backup.sh
```
For
```
period    delay    job-id    command
```
Where
```
7 → every 7 days
5 → wait at least 5 minutes after anacron starts
weekly-backup → unique job identifier
/path/to/backup.sh → your backup script
```

Typical example
```ini
7    10    weekly-backup_to    /mnt/red/BashScripts/BackupRed.sh
```
10 min of delay to make sure the system starts correctly if off
