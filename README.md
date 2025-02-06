
# 3-DOF Gripper Controller

This repository contains code to control a **3 Degrees of Freedom (3DOF) gripper** using an **Arduino UNO**. The system allows communication between a **PC** and the **Arduino** via **serial communication**, enabling precise control over the gripper's prismatic and rotational movements.

## Features

-   **Serial communication** between PC and Arduino
-   **Control of a prismatic joint** (linear actuation) and **two synchronized rotational joints**
-   **Simple Python interface** for sending movement commands

----------

## Repository Structure

```
.
├── Arduino_com.py          # Python module for serial communication with Arduino
├── gripper_controller.py   # Sample Python script to send commands to the Arduino
└── Arduino_UNO_code.ino    # Arduino sketch for processing gripper commands

```

----------

## Hardware Requirements

-   **Arduino UNO**
-   **Gripper mechanism with**:
    -   One **prismatic joint** (linear actuator)
    -   Two synchronized **rotational joints**
- **12V power supply**
-   **USB cable** for communication between PC and Arduino

----------

## Installation & Setup

### 1. Upload the Arduino Code

*  Upload `Arduino_UNO_code.ino` to the board using Arduino IDE

### 2. hon Dependencies

Ensure you have  the follosing Python library installed:

```sh
pip install pyserial

```

### 3. Connect to the Arduino

Modify the `port` in `gripper_controller.py` according to your operating system:

-   **Linux:** `/dev/ttyACM0` or `/dev/ttyACM1`
	- available ports can be listed using: `l /dev | grep ttyACM`
-   **Windows:** `COM3`, `COM4`, etc.

----------

## Wiring the Arduino Board

Connect the stepper motor drivers to the Arduino UNO as follows:

-   **Right Finger Motor (M1)**:
    -   Direction Pin: **D4**
    -   Step Pin: **D5**
-   **Prismatic Joint Motor (M2)**:
    -   Direction Pin: **D2**
    -   Step Pin: **D3**
-   **Left Finger Motor (M3)**:
    -   Direction Pin: **D6**
    -   Step Pin: **D7**

Ensure the stepper motor drivers are powered correctly and that the **ground (GND) connections** between the Arduino and drivers are properly established.

----------

## Usage

Run the main Python script to control the gripper:

```sh
python gripper_controller.py

```

### Example Commands

The gripper accepts three values:

1.  **Prismatic joint position (mm)**
2.  **Finger rotation (degrees)**
3.  **Always set to ****`0`** (since fingers rotate together)

```python
send_gripper_command(ser, [90, 0, 0])   # Open gripper (90 mm, 0°)
send_gripper_command(ser, [90, 30, 0])  # Open fingers (90 mm, 30°)
send_gripper_command(ser, [0, 0, 0])    # Close gripper (0 mm, 0°)

```

----------

## Serial Communication Process

The Python script performs the following steps:

1.  **Establishes a connection** with the Arduino (`connect_Arduino()`)
2.  **Sends movement commands** (`send_gripper_command()`)
3.  **Closes the connection** when finished (`close_serial_connection()`)

----------

## Troubleshooting

-   **Port not found?**  
    Ensure the correct port (`/dev/ttyACM*` or `COM*`) is selected.
    
-   **Permission denied (Linux)?**  
    Run the following command to add your user to the dialout group:
    
    ```sh
    sudo usermod -a -G dialout $USER
    
    ```
    

----------
