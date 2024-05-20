# Smart Home Monitoring and Control System

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Technologies Used](#technologies-used)
4. [Hardware Requirements](#hardware-requirements)
5. [Software Requirements](#software-requirements)
6. [Installation](#installation)
7. [Usage](#usage)
8. [Contributing](#contributing)

## Project Overview
The Smart Home Monitoring and Control System is a web-based application designed to monitor and control various home appliances. It provides real-time information about temperature and humidity, and allows users to control LEDs and a buzzer. The system is also equipped to automatically trigger a buzzer if humidity levels are high and activate a ventilator when the temperature exceeds a certain threshold.

## Features
- **Real-time Temperature and Humidity Monitoring**: Displays current temperature and humidity levels.
- **LED Control**: Turn on/off LEDs through the web interface.
- **Buzzer Control**: Manually activate the buzzer through the web interface.
- **Automated Buzzer Activation**: Automatically sounds the buzzer if humidity exceeds a predefined level.
- **Automated Ventilator Control**: Automatically turns on the ventilator if the temperature is too high.
- **Responsive Web Interface**: User-friendly web interface accessible from any device.

## Technologies Used
- **Frontend**: HTML, CSS, JavaScript
- **Microcontroller**: Arduino
- **Sensors**: DHT11 (Temperature and Humidity sensor)
- **Actuators**: LED, Buzzer, Ventilator (Fan)

## Hardware Requirements
- Arduino board
- DHT11 temperature and humidity sensor
- LEDs
- Buzzer
- Fan or ventilator
- Connecting wires
- Breadboard

## Software Requirements
- Arduino IDE
- Web server (e.g., XAMPP, WAMP) for serving the web interface files
- Git (optional, for version control)

## Installation
1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/smart-home-system.git
   cd smart-home-system
## Usage
Monitor Environment:

Visit the web interface to view real-time temperature and humidity data.
Control Devices:

Use the web controls to turn LEDs on or off.
Manually activate the buzzer if needed.
Automated Controls:

The buzzer will sound automatically if humidity levels are too high.
The ventilator will turn on automatically if the temperature exceeds a certain threshold.
## Contributing
Contributions are welcome! Please fork the repository and create a pull request with your changes. Ensure your code adheres to the project's coding standards and includes appropriate tests.
