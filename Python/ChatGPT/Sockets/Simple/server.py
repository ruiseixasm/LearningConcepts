import socket

# Run 1st as 'python server.py'

# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Define host and port
host = '127.0.0.1'  # Localhost
port = 12345

# Bind the socket to the address
server_socket.bind((host, port))

# Enable the server to accept connections (up to 5 clients)
server_socket.listen(5)
print(f"Server is listening on {host}:{port}")

while True:
    # Accept a connection from a client
    client_socket, client_address = server_socket.accept()
    print(f"Connection established with {client_address}")

    # Send a message to the client
    client_socket.send(b"Hello from the server!")

    # Receive and print data from the client
    client_data = client_socket.recv(1024).decode()
    print(f"Received from client: {client_data}")

    # Close the connection
    client_socket.close()
    print(f"Connection with {client_address} closed")
