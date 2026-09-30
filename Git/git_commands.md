# Cloning a repository
```sh
git clone https://github.com/ruiseixasm/JsonTalkie.git
```

# When .gitignore still doesn't ignore
```sh
git ls-files
```
On specific file
```sh
git rm --cached unwanted_file
```
All files altogether in `.`
```sh
git rm -r --cached .
git add .
```

# configure user credentials
```sh
git config --list --show-origin						# shows all the origin configuration
git config --global user.name "Rui Monteiro"		# sets the user name
git config --global user.email johndoe@example.com	# sets the user email
```

# Add a token:
```sh
git remote set-url origin <address token>
```

# Update remote repository
```sh
git add .						# stage all files
git status						# confirm files were staged
git commit -m "new changes"
git push origin main			# or simple git push
```

# Third party authentication if NOT automatically done or if problematic
```sh
gh auth status
sudo apt install gh
gh auth login
```

# Executing a git pull from a different directory
```sh
git -C <git-working-directory> pull <git remote>
git -C checkout/myApp/ pull
git -C ~/GitHub/JsonMidiPlayer pull
git -C ~/GitHub/JsonMidiCreator pull
git -C ~/GitHub/LearningConcepts pull
```

# Create a new branch
```sh
git branch
git switch -c <branch_name>
git push origin -u <branch_name>
```

# Fetch branches on 3rd local repositories
```sh
git fetch --all
git checkout main
git pull origin main
git checkout <branch_name>
```

# Merge a new branch on main branch
```sh
git switch main
git merge <branch_name>
git push
```

# Revert to a given commit
## Check for the commit hashes
```sh
git log --oneline
git log --oneline -5
```
## Do a commit for each revert
```sh
git revert e8b907c6 e0127393 fff5ebbf ec77b52d 36cee43f
```
## Revert everything in a single commit
```sh
git revert --no-commit e8b907c6 e0127393 fff5ebbf ec77b52d 36cee43f
git commit -m "Revert: Key class changes and related commits"
```

## Check the Conflict
### Open the conflicted file (src/operand_generic.py in your case). You’ll see conflict markers like:
```
<<<<<<< HEAD
Current code (from later commits)
=======
Code being reverted (from the commit you're undoing)
>>>>>>> parent of fff5ebbf... Added _owner_pitch to the class Key
```

## Resolve the Conflict Manually, goal: Keep the version of the code you want (usually the current state or a mix of both).
### Edit the file to:
```
Remove conflict markers (<<<<<<<, =======, >>>>>>>).
Keep the correct code (or merge changes logically).
```
### Example:
# Before resolution:
```
<<<<<<< HEAD
def some_method(self):
    return self._owner_pitch  # Newer code
=======
def some_method(self):
    return None  # Older code (being reverted)
>>>>>>> parent of fff5ebbf...
```

# After resolution (if you want to keep the newer code):
```py
def some_method(self):
    return self._owner_pitch
```

## Mark the Conflict as Resolved
```sh
git add src/operand_generic.py
```

## Continue the Revert, Git will proceed with the next revert commit. Repeat conflict resolution if needed.
```sh
git revert --continue
```

## If You Get Stuck, abort the revert
```sh
git revert --abort
```

### Skip a problematic commit (Use sparingly—only if you’re sure the commit isn’t critical.):
```sh
git revert --skip
```

# At any moment check the status if necessary to see the files that still need resolution:
```sh
git status
```

# When `force` doesn't force it
## Typical forced pull
```sh
git pull --force
```
## Truly force it (hard)
```sh
git merge --abort
git fetch origin
git reset --hard origin/main
```

