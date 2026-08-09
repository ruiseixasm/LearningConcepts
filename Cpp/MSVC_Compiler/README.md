# Microsoft Visual C++ (MSVC)

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
