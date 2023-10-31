# Rubiks-costume

Code for a 2022 halloween costume!

## Parts needed:
- Arduino Nano Every. [Link](https://www.amazon.se/-/en/gp/product/B07VX7MX27/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1).
- WS2812b LED strip. [Link](https://www.amazon.se/-/en/gp/product/B08T89S7C3/ref=ppx_yo_dt_b_asin_title_o04_s01?ie=UTF8&psc=1).
- A button and a 10k resistor
- A 5V battery or power supply. 
- Micro USB cable.
- Some stuff to make it into a cube that can be worn: cardboard, translucent plastic panels, conduit, wires, duct tape, electric tape, velcro, paper, glue, etc...

## Dependencies:
- FastLED library (can be downladed using Arduino IDE)

## Constraints:
- Each square on the cube is expected to have 3 consecutively connected LEDs.
- The LED strips can be arranged in any order but the mapping between LED number and square number needs to be manually added.

## Operation
The program is executed cyclically, cycle time is 50-100ms. 
Each cycle it checks which state it should be in by checking if the button was pressed

The cube will transition state at each button press, as follows: 
- SLEEP --> SHUFFLING --> SHUFFLED --> SHUFFLING --> SOLVED --> SHUFFLING 

The cube will only transition to the SLEEP state if left Idle for 1000 cycles. (approximately 1 min)
- Any state --> SLEEP

**States:**
- SHUFFLING: A random shuffle is selected from a pre-defined list of shown every 150ms.
- SHUFFLED: A random shuffle is shown. Stays in this state until the button is pressed.
- SOLVED: A solved cube.
- SLEEP: Turns off the LEDs if the cube has not changed state for 1 min.

## Development environment
### IDE
VSCode on Ubunto was used. Doxygen used for the documentation. 
Install the Arduino extension: vsciot-vscode.vscode-arduino
Configure your board and download FastLed library

Note that writing from the serial port is not permitted by default on Ubuntu.
To enable it, use the below command (assuming ttyACM0 is the serial port you have):
sudo chmod a+rw /dev/ttyACM0