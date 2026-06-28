# 📏 Ultrasonic Distance Measurement using 8051 (AT89S52)

A microcontroller-based distance measuring system that uses an ultrasonic sensor to detect object distance and displays the result in centimeters on a 16x2 LCD — with a buzzer alert for close-range objects.

## 📖 Overview

Distance measurement is a common requirement in applications like car parking sensors, robotics, water level monitoring, industrial automation, and smart home systems. This project uses the **HC-SR04 ultrasonic sensor** to measure distance and the **8051 (AT89S52) microcontroller** to process the sensor data and drive a **16x2 LCD** display.

The sensor sends out an ultrasonic pulse and waits for the echo to return. The microcontroller measures the time taken for the echo, calculates the distance, and shows it on the LCD in real time.

## 🛠️ Components Used

| Component | Purpose |
|---|---|
| 8051 Microcontroller (AT89S52) | Main processing unit |
| Ultrasonic Sensor (HC-SR04) | Distance sensing via sound waves |
| 16x2 LCD Display | Shows measured distance |
| Crystal Oscillator (11.0592 MHz) | Clock source for the microcontroller |
| Capacitors (33pF, 10µF) | Oscillator stabilization |
| Potentiometer (10KΩ) | LCD contrast control |
| Breadboard & Jumper Wires | Circuit connections |
| Power Supply (5V DC) | Power source |

## ⚙️ How It Works

1. The microcontroller sends a short trigger pulse to the HC-SR04's **TRIG** pin.
2. The sensor emits a 40 kHz ultrasonic pulse and waits for it to reflect off an object.
3. The reflected pulse is received on the **ECHO** pin.
4. The 8051's Timer0 measures the time between sending and receiving the pulse.
5. Distance is calculated using:

   ```
   Distance = (Time × Speed of Sound) / 2
   ```

   The result is divided by 2 because the pulse travels to the object **and back**.
6. The calculated distance is displayed on the LCD in centimeters.
7. If the object is within **5 cm**, a buzzer is triggered as a proximity alert.

## 🔌 Circuit

<p align="center">
  <img src="images/circuit_board_annotated.png" width="500" alt="8051 Development Board - labeled"/>
</p>

<p align="center">
  <img src="images/hardware_setup.jpg" width="400" alt="Actual hardware setup with breadboard, sensor and LCD"/>
</p>

## 💻 Code

Full source: [`distance_measurement.c`](./distance_measurement.c)

Written in Embedded C (Keil/SDCC compatible, uses `reg51.h`).

## 🚀 Applications

- Parking assistance in cars
- Obstacle detection in robots
- Water level monitoring
- Blind stick navigation aid
- Industrial automation (position/distance sensing)
- Touchless height measurement
- Security/intrusion detection systems
- Automatic door opening systems
- Garbage bin fill-level monitoring
- Drone obstacle avoidance

## 👤 Author

**Govind Tard**
Enrollment No. 2022BTECE005
B.Tech ECE, Central University of Rajasthan (CURAJ)

*Project completed as part of the Embedded and Microcontrollers Lab, under the guidance of Dr. Kapil Saraswat, Department of Electronics and Communications Engineering, CURAJ.*

## 📄 License

This project is open-source and available for educational use.
