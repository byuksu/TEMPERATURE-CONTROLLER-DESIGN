# Temperature Controller Design

## Introduction
The project is centered around constructing an efficient temperature control system that employs a precision temperature sensor for real-time temperature data capture. This data is used as input for the control system, which regulates the environment within a cardboard box using both a resistive heating pad and a Peltier device. The integration of these two components allows for flexibility in temperature adjustment and stability maintenance. To facilitate real-time monitoring and a user-friendly interface, we utilize a Nokia 5110 LCD driven by the SPI module. Additionally, GPIO pins are used for an onboard RGB LED, which serves as a visual indicator of the system's operational status, along with pushbuttons for user interactions.

## Problem Statement
In this project, the temperature level measured by the pressure and temperature sensor is displayed on the LCD screen, and the appropriate LEDs on the microcontroller board are illuminated. The system utilizes four input devices and four output devices:
- **Inputs**: Two push buttons, a BMP280 sensor, and a potentiometer.
- **Outputs**: A Nokia LCD screen, onboard RGB LEDs, a resistive heating pad, and a Peltier device.

The BMP280 sensor establishes serial communication with the microcontroller (TM4C123GH6PM) via I2C. It samples the temperature value into a 128-element array, with new data received three times per second and the oldest data discarded (FIFO). The average temperature is calculated from this data.

The potentiometer allows the user to set two threshold values for the temperature. The system operates based on these thresholds:
- **Red LED**: Lights up if the average temperature is below the lower threshold (heating mode).
- **Green LED**: Lights up if the temperature is within the defined thresholds (normal operation).
- **Blue LED**: Lights up if the average temperature is above the higher threshold (cooling mode).

The heating pad and Peltier device are controlled using MOSFET transistors, as the GPIO pins do not provide sufficient current for these outputs.

## Control Mechanism
The control mechanism begins with filling the FIFO buffer with ADC readings. The average temperature is calculated, and the LEDs are controlled based on the thresholds set by the user via push buttons. The system operates as follows:
- If the average temperature is less than the lower threshold, the heating pad is activated, and the red LED is turned on.
- If the average temperature exceeds the higher threshold, the Peltier device is activated, and the blue LED is illuminated.
- If the temperature is between the thresholds, the green LED is turned on, and no additional modules are activated aside from display and sensing.

## Displaying Outputs
The Nokia 5110 LCD screen is configured through GPIO settings, utilizing specific pins for SPI communication. The LCD displays the current temperature, lower and upper threshold values, and dynamically updates these values every second. Additionally, it features a graph that represents the current temperature over time, allowing for real-time visualization of temperature changes.

## Conclusion
In summary, the integrated temperature controller system using TM4C123GH6PMI combines a precision temperature sensor, a resistive heating pad, and a Peltier device for adaptable and stable temperature regulation. The Nokia 5110 LCD enhances user interaction by providing real-time monitoring, while onboard RGB LEDs visually indicate temperature intervals. Users can set temperature thresholds with a potentiometer, and the microcontroller processes these inputs effectively. This system delivers a user-friendly interface and versatile functionality, ensuring effective temperature control across various applications.

For more details, please refer to the documents [TEMPERATURE CONTROLLER.pdf](TEMPERATURE-CONTROLLER.pdf) and [447_pre_report.pdf](447_pre_reporr.pdf).
