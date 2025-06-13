import socket
import os
from datetime import datetime

LOG_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../logs'))
LOG_FILE = os.path.join(LOG_DIR, 'tcp_server.log')
HOST = '0.0.0.0'  # Escucha en todas las interfaces
PORT = 5000       # Puerto configurable
BUFFER_SIZE = 1024

LOG_DIR = os.path.join(os.path.dirname(__file__), '../logs')
os.makedirs(LOG_DIR, exist_ok=True)

def log_message(message: str):
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
    with open(LOG_FILE, 'a') as f:
        f.write(f'{timestamp} {message}\n')


def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen(1)
        print(f'Servidor escuchando en {HOST}:{PORT}')
        conn, addr = s.accept()
        with conn:
            print(f'Conexión establecida desde {addr}')
            while True:
                data = conn.recv(BUFFER_SIZE)
                if not data:
                    break
                msg = data.decode(errors='replace')
                print(f'Recibido: {msg}')
                log_message(f'RECIBIDO de {addr}: {msg}')

if __name__ == '__main__':
    start_server()