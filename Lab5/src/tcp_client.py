import os
import socket
import time
import logging

# Configuration
SERVER_HOST = '192.168.100.3' 
SERVER_PORT = 5000        
GROUP_NAME = "SinLatenciaTeam"
PACKET_COUNT = 100
SEND_INTERVAL = 1  # Interval in seconds

LOG_DIR = os.path.join(os.path.dirname(__file__), "../logs")
os.makedirs(LOG_DIR, exist_ok=True)

# Setup logging
logging.basicConfig(
    filename=os.path.join(LOG_DIR, "client_log.txt"),  # Use LOG_DIR for the log file path
    level=logging.INFO,
    format="%(asctime)s - %(message)s"
)

def main():
    try:
        # Create a TCP socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((SERVER_HOST, SERVER_PORT))
        print(f"Connected to server at {SERVER_HOST}:{SERVER_PORT}")

        for i in range(1, PACKET_COUNT + 1):
            # Create a unique packet
            packet = f"{GROUP_NAME}_{i}"
            timestamp = time.time()

            # Send the packet
            client_socket.sendall(packet.encode())
            print(f"Sent: {packet}")

            # Log the sent packet
            logging.info(f"Sent: {packet} | Timestamp: {timestamp}")

            # Wait for the configured interval
            time.sleep(SEND_INTERVAL)

        print("All packets sent successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()