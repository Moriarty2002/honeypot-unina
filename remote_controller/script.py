import serial
import threading
import time
import argparse
import sys

def parse_arguments():
    # parse arguments via command line
    parser = argparse.ArgumentParser(description='Script for serial communication')
    
    # os parameter
    parser.add_argument('-os', '--operating-system', 
                       choices=['linux', 'win', 'mac'],
                       default='win',
                       help='Select Operating System (linux, win, mac)')
    
    # port parameter
    parser.add_argument('-port', '--port',
                       type=int,
                       default=7,
                       help='Select serial port number')
    
    return parser.parse_args()
    
def configure_serial_port(os_type, port_num):
    # configure serial port based on os
    if os_type == 'linux':
        return f"/dev/rfcomm{port_num}"
    elif os_type == 'win':
        return f"COM{port_num}"
    elif os_type == 'mac':
        return f"/dev/tty.rfcomm{port_num}"
    else:
        raise ValueError(f"[ERROR] Operating System not supported: {os_type}")

def main():
    args = parse_arguments()
    
    # config parameters
    BAUD_RATE = 9600
    OUTPUT_FILE = "credentials.txt"
    SERIAL_PORT = configure_serial_port(args.operating_system, args.port)
    
    print(f"[STARTED] Script for serial communication.")
    print(f"[INFO] Operating System: {args.operating_system}")
    print(f"[INFO] Serial Port: {SERIAL_PORT}")

    # open serial connection
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"[OK] Serial connection started")
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
                if msg.lower() in ["start", "stop_"]:
                    ser.write((msg + "\n").encode())
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
    
if __name__ == "__main__":
    main()
