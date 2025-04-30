import serial, json

ser = serial.Serial('COM4', 9600)
data = {"temp": 23.5}

# Add newline terminator (like Python's print())
ser.write(json.dumps(data).encode() + b'\n')  # <-- THE FIX
