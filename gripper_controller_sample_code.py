from Arduino_com import send_gripper_command, connect_Arduino, close_serial_connection
import time


if __name__ == "__main__":
    # Arduino connection configuration
    port = '/dev/ttyACM0'           # for linux it is usually '/dev/ttyACM0' or '/dev/ttyACM1'
                                    # for Windows it would be like 'COM3', 'COM4', etc
    baudrate = 9600
    ser = connect_Arduino(port=port, baudrate=baudrate)

    # open the gripper; the second argument is the joint command:
    # [prismatic joint value in mm, 
    #   fingers rotation value in deg, 
    #   0(always zero, since the rotation of the fingers are considered synced together)]
    send_gripper_command(ser, [90,0,0])     # 90 mm, 0 deg
    time.sleep(5)

    # open the fingers
    send_gripper_command(ser, [90,30,0])    # 90 mm, 30 deg
    time.sleep(5)

    # close fingers & gripper 
    send_gripper_command(ser, [0,0,0])      # 0 mm, 0 deg
    time.sleep(5)

    close_serial_connection(ser)