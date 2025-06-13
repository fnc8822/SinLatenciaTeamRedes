import os
import socket
import time
import logging

# Configuration
SERVER_HOST = '192.168.100.8' 
SERVER_PORT = 5000        
GROUP_NAME = "SinLatenciaTeam"
PACKET_COUNT = 100
SEND_INTERVAL = 1  # Interval in seconds

LOG_DIR = os.path.join(os.path.dirname(__file__), "../logs")
os.makedirs(LOG_DIR, exist_ok=True)

# Setup logging
logging.basicConfig(
    filename=os.path.join(LOG_DIR, "tcp_client.log"),
    level=logging.INFO,
    format="%(asctime)s.%(msecs)03d - %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

def main():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((SERVER_HOST, SERVER_PORT))
        print(f"Connected to server at {SERVER_HOST}:{SERVER_PORT}")

        for i in range(1, PACKET_COUNT + 1):
            # Create a unique packet with a timestamp
            send_time = time.time()
            packet = f"{GROUP_NAME}_{i}"
            client_socket.sendall(packet.encode())
            print(f"Sent: {packet}")
            logging.info(f"Sent: {packet}")

            time.sleep(SEND_INTERVAL)

    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()