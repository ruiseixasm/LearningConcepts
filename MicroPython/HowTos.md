# How to install Micro Python
1. Connect the Pico board via Micro USB WHILE pressing the BOOT button
2. Open the drive "E:\RPI-RP2"
3. Go to the web site https://micropython.org/
4. Download the firmware for the board "Raspberry Pico W" (Ex.: "v1.25.0 (2025-04-15) .uf2")
5. Drag and drop the ".uf2" file above to the Pico drive "E:\RPI-RP2" (the board will auto reboot)


# How to program the board in Micro Python (and run programs in it)
1. Go to the web site https://thonny.org/
2. Download the file version for your system and install it
3. Open the program Thonny previously installed
4. Select the board in the bottom right corner associated to a COM port
5. Test the installed MicroPython by running in the console "print('Hello World!')"


# How to execute scripts
1. Write the following scrypt
```
a = 7
b = 2
c = a * b
print(c)
```
2. On thonny, go to "Run->Configure interpreter..." and uncheck the box at the bottom (restart before running script)
3. Run the previous scrypt by typing "%Run -c $EDITOR_CONTENT" or by pressing the Play button (F5)


# How to program the Blinking sketch
1. Write the following script
```
from machine import Pin
from time import sleep
myLED = Pin('LED', Pin.OUT)
while True:
    myLED.value(0)
    sleep(0.5)
    myLED.value(1)
    sleep(0.5)
```
2. Press the Play button(F5) to test it


# How to upload a sketch to the board
1. Stop any running script by pressing the button Stop (Ctrl+F2)
2. Press Ctrl+S or select "File->Save"
3. Select "Raspberry Pi Pico"
4. Save the scrypt with the name "main.py" to run on boot
5. Unplug and plug the board to load the saved script


