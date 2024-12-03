import socket

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Define server address
server_host = '127.0.0.1'  # Localhost
server_port = 12345

# Connect to the server
client_socket.connect((server_host, server_port))

# Receive the image data
image_data = b""
while True:
    chunk = client_socket.recv(4096)  # Receive in chunks of 4096 bytes
    if not chunk:
        break
    image_data += chunk

# Save the received image
with open("received_image.png", "wb") as image_file:
    image_file.write(image_data)
    print("Image saved as 'received_image.png'")

# Close the connection
client_socket.close()
