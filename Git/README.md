# HELP
```sh
git --help
```

# CONFIG
## set username and email
```sh
git config --list --show-origin
git config --global user.name "ruiseixasm"
git config --global user.email "ruiseixasm@mail.com"
```

# AUTHENTICATION
## On GitHub
Make sure the `gh` command is installed
```sh
which gh
```
If not installed install it with this command
```sh
sudo apt install gh
```
Use it by typing
```sh
gh auth login
```

# REBASE VS MERGE
Now by default Git asks for the choice of `rebase` or `merge`, where rebase keeps a single brach line
but locks uncommitted pushes into it given the new hash that produces. To keep doing `merge` automatically,

type for global
```sh
git config --global pull.rebase false
```

but only for the repository, type
```sh
git config pull.rebase false
```

