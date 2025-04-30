import serial
import json
import time

ser = serial.Serial('COM4', 115200, timeout=1)

# 1. Send original request format (newline-terminated)
request = {"temp": 23.5}
ser.write(json.dumps(request).encode() + b'\n')

# 2. Receive response (same format)
start_reading = time.time()
while time.time() - start_reading < 5:
    response = ser.readline().decode().strip()
    if response:
        print("Received:", json.loads(response))

ser.close()
