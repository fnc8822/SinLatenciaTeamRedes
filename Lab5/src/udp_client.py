import os
import socket
import time
import logging
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.backends import default_backend

# Configuration
SERVER_HOST = '192.168.100.8'  # Replace with the server's IP address
SERVER_PORT = 5000            # Replace with the server's port
GROUP_NAME = "SinLatenciaTeam"
PACKET_COUNT = 100
SEND_INTERVAL = 1  # Interval in seconds
AES_KEY = b"verysecurekey!!!"  # 16 bytes key for AES-128

LOG_DIR = os.path.join(os.path.dirname(__file__), "../logs")
os.makedirs(LOG_DIR, exist_ok=True)

# Setup logging
logging.basicConfig(
    filename=os.path.join(LOG_DIR, "udp_client.log"),
    level=logging.INFO,
    format="%(asctime)s.%(msecs)03d - %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

def encrypt_message(message: str) -> bytes:
    """Encrypt the message using AES encryption."""
    backend = default_backend()
    cipher = Cipher(algorithms.AES(AES_KEY), modes.ECB(), backend=backend)
    encryptor = cipher.encryptor()

    # Pad the message to be a multiple of the block size
    padder = padding.PKCS7(algorithms.AES.block_size).padder()
    padded_data = padder.update(message.encode()) + padder.finalize()

    # Encrypt the padded data
    encrypted_message = encryptor.update(padded_data) + encryptor.finalize()
    return encrypted_message

def main():
    try:
        # Create a UDP socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print(f"UDP client ready to send packets to {SERVER_HOST}:{SERVER_PORT}")

        for i in range(1, PACKET_COUNT + 1):
            # Create a unique packet
            packet = f"{GROUP_NAME}_{i}"
            encrypted_packet = encrypt_message(packet)  # Encrypt the packet

            # Send the encrypted packet
            client_socket.sendto(encrypted_packet, (SERVER_HOST, SERVER_PORT))
            print(f"Sent encrypted packet: {encrypted_packet}")
            logging.info(f"Sent encrypted packet: {encrypted_packet}")

            # Wait for the configured interval
            time.sleep(SEND_INTERVAL)

        print("All packets sent successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()
        print("Socket closed.")

if __name__ == "__main__":
    main()