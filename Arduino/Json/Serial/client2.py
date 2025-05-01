import serial
import json
import time

ser = serial.Serial('COM4', 9600, timeout=1)
time.sleep(3.5)  # Then wait for Arduino to initialize

# 1. Send original request format (newline-terminated)
request = {"temp": 23.5}
ser.write(json.dumps(request).encode() + b'\n')  # Critical: \n must be part of same write

# 2. Receive response (same format)
start_reading = time.time()
while time.time() - start_reading < 5:
    response = ser.readline().decode().strip()
    if response:
        print("Received:", json.loads(response))
        break

ser.close()
