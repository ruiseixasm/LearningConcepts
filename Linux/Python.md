# How to install
Follow these commands to install
```sh
sudo apt update
sudo apt install python3-full python3-pip
```

Important note on 32-bit environments, if you try to use pip install globally, you will get an externally-managed-environment error. Always create a virtual environment first:
```sh
python3 -m venv myenv
source myenv/bin/activate
pip install package_name
```
