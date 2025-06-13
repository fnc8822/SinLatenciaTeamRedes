import os
import re
from statistics import mean
import logging

# Paths to logs
LOG_DIR = os.path.join(os.path.dirname(__file__), "../logs")
TCP_CLIENT_LOG = os.path.join(LOG_DIR, "tcp_client.log")
TCP_SERVER_LOG = os.path.join(LOG_DIR, "tcp_server.log")
UDP_CLIENT_LOG = os.path.join(LOG_DIR, "udp_client.log")
UDP_SERVER_LOG = os.path.join(LOG_DIR, "udp_server.log")
RESULTS_LOG = os.path.join(LOG_DIR, "latencia_jitter_results.log")

# Setup logging for results
os.makedirs(LOG_DIR, exist_ok=True)
logging.basicConfig(
    filename=RESULTS_LOG,
    level=logging.INFO,
    format="%(message)s"
)

def parse_logs(client_log, server_log):
    """Parse client and server logs to extract timestamps and packet IDs."""
    if not os.path.exists(client_log) or not os.path.exists(server_log):
        print(f"Logs not found: {client_log} or {server_log}")
        return None, None

    # Extract sent timestamps from client log
    client_data = {}
    with open(client_log, "r") as f:
        for line in f:
            match = re.search(r"Sent: (SinLatenciaTeam_\d+) \| Timestamp: ([\d.]+)", line)
            if match:
                packet_id = match.group(1)
                timestamp = float(match.group(2))
                client_data[packet_id] = timestamp

    # Extract received timestamps from server log
    server_data = {}
    with open(server_log, "r") as f:
        for line in f:
            match = re.search(r"RECIBIDO.*: (SinLatenciaTeam_\d+)", line)
            if match:
                packet_id = match.group(1)
                timestamp_match = re.search(r"\[(.*?)\]", line)
                if timestamp_match:
                    timestamp = timestamp_match.group(1)
                    # Convert timestamp to seconds
                    timestamp_parts = timestamp.split(":")
                    seconds = float(timestamp_parts[-1])
                    server_data[packet_id] = seconds

    return client_data, server_data

def calculate_metrics(client_data, server_data):
    """Calculate latency metrics and jitter."""
    latencies = []
    for packet_id, sent_time in client_data.items():
        if packet_id in server_data:
            received_time = server_data[packet_id]
            latency = received_time - sent_time
            latencies.append(latency)

    if not latencies:
        print("No matching packets found between client and server logs.")
        return None

    # Calculate metrics
    avg_latency = mean(latencies)
    max_latency = max(latencies)
    min_latency = min(latencies)
    jitter = mean(abs(latencies[i] - latencies[i - 1]) for i in range(1, len(latencies)))

    return avg_latency, max_latency, min_latency, jitter

def process_logs(client_log, server_log, protocol):
    """Process logs for a specific protocol (TCP or UDP)."""
    print(f"Processing {protocol} logs...")
    client_data, server_data = parse_logs(client_log, server_log)
    if client_data and server_data:
        metrics = calculate_metrics(client_data, server_data)
        if metrics:
            avg_latency, max_latency, min_latency, jitter = metrics
            # Print results to console
            print(f"{protocol} Metrics:")
            print(f"  Average Latency: {avg_latency:.6f} seconds")
            print(f"  Maximum Latency: {max_latency:.6f} seconds")
            print(f"  Minimum Latency: {min_latency:.6f} seconds")
            print(f"  Jitter: {jitter:.6f} seconds")
            # Log results to file
            logging.info(f"{protocol} Metrics:")
            logging.info(f"  Average Latency: {avg_latency:.6f} seconds")
            logging.info(f"  Maximum Latency: {max_latency:.6f} seconds")
            logging.info(f"  Minimum Latency: {min_latency:.6f} seconds")
            logging.info(f"  Jitter: {jitter:.6f} seconds")
    else:
        print(f"Could not process {protocol} logs due to missing or invalid data.")
        logging.warning(f"Could not process {protocol} logs due to missing or invalid data.")

def main():
    # Process TCP logs
    if os.path.exists(TCP_CLIENT_LOG) and os.path.exists(TCP_SERVER_LOG):
        process_logs(TCP_CLIENT_LOG, TCP_SERVER_LOG, "TCP")
    else:
        print("TCP logs not found or incomplete.")
        logging.warning("TCP logs not found or incomplete.")

    # Process UDP logs
    if os.path.exists(UDP_CLIENT_LOG) and os.path.exists(UDP_SERVER_LOG):
        process_logs(UDP_CLIENT_LOG, UDP_SERVER_LOG, "UDP")
    else:
        print("UDP logs not found or incomplete.")
        logging.warning("UDP logs not found or incomplete.")

if __name__ == "__main__":
    main()