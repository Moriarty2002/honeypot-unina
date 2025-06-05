import serial
import threading
import time

# config parameters
SERIAL_PORT = "COM7"
BAUD_RATE = 9600
OUTPUT_FILE = "credentials.txt"

# open serial port
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"[OK] Serial connection started")
    print(f"[OK] Connected to {SERIAL_PORT}")
except Exception as e:
    print(f"[ERROR] Failed to start serial connection: {e}")
    exit(1)

def receive_data():
    with open(OUTPUT_FILE, "a") as f:
        while True:
            try:
                data = ser.readline().decode(errors="ignore").strip()
                if data:
                    timestamp = time.strftime("[%Y-%m-%d %H:%M:%S]")
                    print(f"\n[<<] {data}")
                    f.write(f"{timestamp} {data}\n")
                    f.flush()
            except Exception as e:
                print(f"[ERROR] Failed to receive data: {e}")
                break

def send_command():
    try:
        while True:
            msg = input("[>>] ")
            if msg.lower() in ["exit", "quit"]:
                break
            if msg.lower() == "stop":
                msg = "stop_"
            if msg.lower() in ["start", "stop"]:
                ser.write((msg).encode())
            else:
                print(f"[ERROR] Command not available.")  
    except KeyboardInterrupt:
        pass

# start reception thread
receive_thread = threading.Thread(target=receive_data, daemon=True)
receive_thread.start()

# start main loop
send_command()

# close serial
ser.close()
print("\n[CLOSED] Serial connection closed.")
