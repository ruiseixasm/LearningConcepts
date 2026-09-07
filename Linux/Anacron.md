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

The given script should be in a save place in order to not be tampered with, so, this is the safe place:
```ini
7    10    weekly.backup_to    /usr/local/sbin/BackupRed.sh
```
10 min of delay to make sure the system starts correctly if off

Given that the anacron runs the script as root, the target script should be writable only by root and owned by it, like so:
```sh
sudo chown root:root /usr/local/sbin/BackupRed.sh
sudo chmod 755 /usr/local/sbin/BackupRed.sh
```

Check the last runs for each task
```sh
$ ls -l /var/spool/anacron/
total 16
-rw------- 1 root root 9 set  7 07:57 cron.daily
-rw------- 1 root root 9 ago 14 13:27 cron.monthly
-rw------- 1 root root 9 set  4 08:26 cron.weekly
-rw------- 1 root root 9 set  6 15:27 weekly.backup_to
```
Note that `9` is the size of the file and not the month, '20260907' are 8 charancters (8 bytes) plus the '\n' one.
