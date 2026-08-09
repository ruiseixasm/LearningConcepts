# Microsoft Visual C++ (MSVC)

## Visual Studio Code System Installer
Make sure the Visual Studio Code installed is the System Installer and NOT the User Installer. So, go to Insiders Edition and select the System Installer x64.

## Install Visual Studio Tools

Go to the page [https://visualstudio.microsoft.com/downloads/](https://visualstudio.microsoft.com/downloads/), and under **Tools for Visual Studio**, download **Build Tools for Visual Studio**.

In the **installation details** panel on the right, select the following:
1. C++ x64/x86 build tools
1. C++ CMake tools for Windows
1. If SDK not installed already, install Windows SDK

## Test the MSVC installation
1. **Start → Developer Command Prompt for VS 2022**
1. Type `cl` to see `Microsoft (R) C/C++ Optimizing Compiler Version 19.xx`
1. Type `cmake --version`, it should also work

## Configure the VS Code to use it
Do **Ctrl+Shift+P → CMake: Select Configure Preset** or **Ctrl+Shift+P → CMake: Select a Kit** if you're using the simpler CMake Tools workflow, You should see something similar to:
```
Visual Studio Build Tools 2022 Release - amd64
```
Select that in order to CMake use the `cl.exe` rather than any other.

## Remove old compiler references from VSCode

### Delete the CMake Tools cache
```shell
rmdir /s "%APPDATA%\Code\User\globalStorage\ms-vscode.cmake-tools"
```

### Delete project cache
```shell
cd C:\Users\rui\Documents\GitHub\JsonMidiPort
rmdir /s build
del CMakeCache.txt 2>nul
rmdir /s .vs 2>nul
```

