import serial
import time

def connect_Arduino(port, baudrate):
    # Initialize serial communication
    ser = serial.Serial(port, baudrate)
    time.sleep(2)
    return ser

def send_gripper_command(ser, double_values):
    ## Convert the double values to a string
    data_string = ','.join(map(str, double_values)) # Join values with commas
    
    # Send the string
    ser.write((data_string + '\n').encode())        # Add newline to mark the end of the string


def close_serial_connection(ser):
    ser.close()
