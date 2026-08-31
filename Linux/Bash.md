# Bash Configuration
## `.bashrc`
Edit the bash configuration like so to add a cd path
```sh
nano ~/.bashrc
```

### **CDPATH**
Search inside the `/mnt` directory
```sh
CDPATH=:/mnt
```
To open the directory `red` inside `/mnt`, one only need to type:
```sh
cd red
```
Add the following line to the file
```sh
export CDPATH=".:/mnt:$HOME/documentos/codigo:$HOME/.config"
```
Then load the updated content
```sh
source ~/.bashrc
```

