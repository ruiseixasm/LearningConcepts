from typing import Dict, Any
import time
import random


from broadcast_socket_udp import *


if __name__ == "__main__":
    messages: tuple[bytes, bytes] = (
        b'{"m": 0, "t": "*"}',
        b'{"m": 5, "t": "*"}',
        b'{"m": 0, "f": "Talker-40", "i": 3921942051, "c": 28235}',
        b'{"m": 5, "f": "Talker-40", "i": 3921986557, "c": 24906}'
    )
    broadcast_socket: BroadcastSocket = BroadcastSocket_UDP()
    try:
        broadcast_socket.open()

        # Main loop
        message_time = time.time()
        while True:
            if time.time() - message_time > 10:
                message: str = messages[random.randint(0, len(messages) - 1)]
                print(f"\tSending {message}")
                broadcast_socket.send(message)
                message_time = time.time()
    except KeyboardInterrupt:
        print("\tShutting down...")
    finally:
        broadcast_socket.close()  # Ensures socket cleanup
