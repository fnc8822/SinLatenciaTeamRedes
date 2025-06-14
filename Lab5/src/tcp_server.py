import socket
import os
from datetime import datetime
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.backends import default_backend

LOG_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../logs'))
LOG_FILE = os.path.join(LOG_DIR, 'tcp_server.log')
HOST = '0.0.0.0'  # Listen on all interfaces
PORT = 5000       # Configurable port
BUFFER_SIZE = 1024
AES_KEY = b"verysecurekey!!!"  # 16 bytes key for AES-128

os.makedirs(LOG_DIR, exist_ok=True)

def log_message(message: str):
    """Log a message with a timestamp to the log file."""
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
    with open(LOG_FILE, 'a') as f:
        f.write(f'{timestamp} {message}\n')

def decrypt_message(encrypted_message: bytes) -> str:
    """Decrypt the message using AES."""
    backend = default_backend()
    cipher = Cipher(algorithms.AES(AES_KEY), modes.ECB(), backend=backend)
    decryptor = cipher.decryptor()

    # Decrypt the message
    padded_data = decryptor.update(encrypted_message) + decryptor.finalize()

    # Remove padding
    unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder()
    data = unpadder.update(padded_data) + unpadder.finalize()
    return data.decode()

def start_server():
    """Start the TCP server."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen(1)
        print(f'Server listening on {HOST}:{PORT}')
        conn, addr = s.accept()
        with conn:
            print(f'Connection established from {addr}')
            while True:
                data = conn.recv(BUFFER_SIZE)
                if not data:
                    break
                try:
                    # Decrypt the received message
                    decrypted_message = decrypt_message(data)
                    print(f"Received and decrypted: {decrypted_message}")
                    log_message(f'RECEIVED from {addr}: {decrypted_message}')
                except Exception as e:
                    print(f"Failed to decrypt message from {addr}: {e}")
                    log_message(f"FAILED to decrypt message from {addr}: {e}")

if __name__ == '__main__':
    start_server()