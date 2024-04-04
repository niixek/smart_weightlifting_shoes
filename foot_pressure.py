import serial
from datetime import datetime
from pynput import keyboard
import csv

def on_esc_pressed(key):
    if key == keyboard.Key.esc:
        return False

# Define the serial port and baud rate (make sure to match the one in your Arduino sketch)
ser = serial.Serial('/dev/cu.usbserial-1130', 9600)
# Open a csv file for writing the data (change this to not overwrite previous data!)
file_path = 'footdata3.csv'

try_read = False
read = False
counter = 0
try:
    with keyboard.Listener(on_press = on_esc_pressed) as listener:
        with open(file_path, 'w') as f_foot:
            print("Logging Data!")
            while True:
                #Wait for serial to connect
                writer = csv.writer(f_foot, delimiter=',')
                if not try_read:
                    print("Trying to Read Serial...")
                    try_read = True
                
                data_i = ser.readline().decode().strip()
                if not read:
                    print("Serial Read!")
                    read = True
                
                #Log data
                f_foot.write(datetime.now().strftime("%H:%M:%S.%f") + ',')
                f_foot.write(data_i + '\n')
                counter += 1
                if not listener.running:
                    print("Data points logged: " + str(counter))
                    break
except KeyboardInterrupt:
    print("Data points logged: " + str(counter))
    # Clean up and exit gracefully when 'CTRL + C' is pressed
    pass
