"""
YouTube url: https://youtu.be/SimNmTciQTs?si=6WAur7eFHetmFBLd&t=1112
"""

'''Chat Room Connection - Client-To-Client'''
import threading    # https://youtu.be/8C9IJEuQjhY?si=2YFaTv5ZKdqp8jTP
import socket
host = '127.0.0.1'
# Run netstat to choose an available port
port = 63000    # Must be from 1024 to 65535 (2**16)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()
clients: list[socket.socket] = []
aliases: list[str] = []

def broadcast(message):
    for client in clients:
        client.send(message)

# Function to handle clients' connections
def handle_client(client):
    while True:
        try:
            message = client.recv(1024)
            broadcast(message)
        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()
            alias = aliases[index]
            broadcast(f'{alias} has left the chat room!'.encode())
            aliases.remove(alias)
            break

# Main function to receive the clients connection
def receive():
    while True:
        print('Server is running and listening ...')
        client, address = server.accept()
        print(f'connection is established with {str(address)}')
        client.send('alias?'.encode())
        alias = client.recv(1024).decode()
        aliases.append(alias)
        clients.append(client)
        print(f'The alias of this client is {alias}')
        broadcast(f'{alias} has connected to the chat room'.encode())
        client.send('you are now connected!'.encode())
        thread = threading.Thread(target=handle_client, args=(client,)) # it has to have a , in (client,) to be a tuple
        thread.start()

if __name__ == '__main__':
    receive()
