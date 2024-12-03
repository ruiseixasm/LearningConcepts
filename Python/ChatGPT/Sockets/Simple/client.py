import socket

# Run 2nd as 'python server.py'

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Define server address
server_host = '127.0.0.1'  # Localhost
server_port = 12345

# Connect to the server
client_socket.connect((server_host, server_port))

# Receive a message from the server
server_message = client_socket.recv(1024).decode()
print(f"Received from server: {server_message}")

# Send a response to the server
client_socket.send(b"Hello from the client!")

# Close the connection
client_socket.close()
