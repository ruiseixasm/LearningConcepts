"""
YouTube url: https://youtu.be/SimNmTciQTs?si=mqTsj47Il9p45U51&t=256
"""

'''Socket Programming in Python'''
import socket
import sys

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('socket successfully created!')
    # ip = socket.gethostbyname('www.github.com')
    # print(ip)
except socket.error as err:
    print(f'socket creation failed with error {err}')

port = 80

try:
    host_ip = socket.gethostbyname('www.github.com')
except socket.gaierror:
    print('error resolving the host')
    sys.exit()
s.connect((host_ip, port))
print(f'Socket has successfully connected to GitHub on port == {host_ip}')
