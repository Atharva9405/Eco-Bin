# Eco-Bin: Ultrasonic Waste Management System

This project aims to develop an efficient waste management system using an ESP8266 microcontroller, ultrasonic sensors, and an Arduino Uno for external power supply. The system is designed to monitor the waste level in a bin and provide real-time updates to users through an MQTT client app.

## Components

- ESP8266 microcontroller
- Ultrasonic sensor (HC-SR04)
- LEDs (Green, Yellow)
- Buzzer
- Arduino Uno (for external 5V power supply to the ultrasonic sensor)
- Breadboard
- Jumper wires

## Functionality

The eco-bin is equipped with an ultrasonic sensor mounted at the top of the bin. The sensor measures the distance between the sensor and the waste level inside the bin. The system operates as follows:

1. **Initial State**: When the bin is empty, the green LED is lit, indicating that the bin is ready to receive waste.

2. **Warning Stage**: As the waste level rises and reaches between 15-5 cm from the top, the yellow LED turns on, indicating that the bin is getting full, and users should start disposing of waste more cautiously.

3. **Critical Stage**: When the waste level reaches within 5 cm from the top, the buzzer beeps, alerting users that the bin is almost full and immediate action is required.

4. **Notification**: At each stage, the system sends real-time updates to an MQTT client app, notifying users about the waste level and the corresponding action required.

5. **Monitoring**: Users can monitor the waste level readings through the MQTT client app, enabling efficient waste collection planning and prioritization.

## Future Enhancements

In future iterations, the eco-bin system can be scaled up and integrated into municipal waste management systems. By deploying these smart bins across cities, waste collection agencies can monitor the waste levels in real-time and optimize their collection routes and schedules accordingly, leading to improved efficiency and cost savings.

## Getting Started

To set up and run the eco-bin project locally, follow these steps:

1. Clone the repository: `git clone https://github.com/your-username/eco-bin.git`
2. Install the required libraries and dependencies.
3. Connect the components according to the provided circuit diagram.
4. Upload the code to the ESP8266 microcontroller.
5. Configure the MQTT client app with the appropriate server details.
6. Monitor the waste level readings and notifications through the app.