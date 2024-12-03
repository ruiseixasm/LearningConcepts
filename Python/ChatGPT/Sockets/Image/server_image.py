import socket

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

    # Open and send an image file
    with open("example.png", "rb") as image_file:
        image_data = image_file.read()
        client_socket.sendall(image_data)
        print("Image sent to the client.")

    # Close the connection
    client_socket.close()
    print(f"Connection with {client_address} closed")
