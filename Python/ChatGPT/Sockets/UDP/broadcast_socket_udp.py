import socket
from typing import Optional, Tuple, Dict

from broadcast_socket import BroadcastSocket

class BroadcastSocket_UDP(BroadcastSocket):
    """UDP broadcast socket with explicit lifecycle control."""
    
    def __init__(self, port: int = 5005):
        self._port = port
        self._socket = None  # Not initialized until open()
    
    def open(self) -> bool:
        """Initialize and bind the socket."""
        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self._socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Critical!
            self._socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            self._socket.bind(('', self._port))
            self._socket.setblocking(False)
            return True
        except Exception as e:
            print(f"Socket open failed: {e}")
            return False
    
    def close(self):
        """Release socket resources."""
        if self._socket:
            self._socket.close()
            self._socket = None
    
    def send(self, data: bytes, device_address: Tuple[str, int] = None) -> bool:
        """Broadcast data if socket is active."""
        if not self._socket:
            return False
        try:
            if device_address:
                self._socket.sendto(data, device_address)
            else:
                self._socket.sendto(data, ('255.255.255.255', self._port))
            return True
        except Exception as e:
            print(f"Send failed: {e}")
            return False
    
    def receive(self) -> Optional[Tuple[bytes, Tuple[str, int]]]:
        """Non-blocking receive."""
        if not self._socket:
            return None
        try:
            data_ip_port: Optional[Tuple[bytes, Tuple[str, int]]] = self._socket.recvfrom(4096)
            if data_ip_port is not None and data_ip_port[1][1] == self._port:
                return data_ip_port
            return None
        except BlockingIOError:
            return None
        except Exception as e:
            print(f"Receive error: {e}")
            return None
        
