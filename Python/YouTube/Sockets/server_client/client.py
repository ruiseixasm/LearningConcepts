"""
YouTube url: https://youtu.be/SimNmTciQTs?si=DhaI7lNnxTOgQ7Ph&t=545
"""

'''Server Client example in Python'''
import socket
s = socket.socket()
port = 56789
s.connect(('localhost', port))  # or 127.0.0.1 also works
print(s.recv(1024).decode()) # 1024 is the buffer size
s.close()

