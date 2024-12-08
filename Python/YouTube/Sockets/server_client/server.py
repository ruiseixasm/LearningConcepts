"""
YouTube url: https://youtu.be/SimNmTciQTs?si=DhaI7lNnxTOgQ7Ph&t=545
"""

'''Server Client example in Python'''
'''Use telnet to connect >>> telnet 127.0.0.1 56789'''  # also localhost works too
import socket
s = socket.socket()
print('Socket successfully created')
port = 56789
s.bind(('', port))
print(f'socket binded to port{port}')
s.listen(5) # Limit of connecting clients
print('Socket is listening')
while True:
    c, addr = s.accept()
    print('Got connection from', addr)
    message = ('Thank you for connecting')
    c.send(message.encode())    # sends in bytes
    c.close()
