import socket
import os
from datetime import datetime

LOG_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../logs'))
LOG_FILE = os.path.join(LOG_DIR, 'udp_server.log')
HOST = '0.0.0.0'  # Listen on all interfaces
PORT = 5000       # Configurable port
BUFFER_SIZE = 1024

os.makedirs(LOG_DIR, exist_ok=True)

def log_message(message: str):
    """Log a message with a timestamp to the log file."""
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
    with open(LOG_FILE, 'a') as f:
        f.write(f'{timestamp} {message}\n')

def start_server():
    """Start the UDP server."""
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((HOST, PORT))
        print(f'UDP server listening on {HOST}:{PORT}')
        while True:
            data, addr = s.recvfrom(BUFFER_SIZE)
            msg = data.decode(errors='replace')
            print(f'Received from {addr}: {msg}')
            log_message(f'RECIBIDO de {addr}: {msg}')

if __name__ == '__main__':
    start_server()