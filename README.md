# Rubiks-costume

Code for a 2022 halloween costume!

## Parts needed:
- Arduino Nano Every. [Link](https://www.amazon.se/-/en/gp/product/B07VX7MX27/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1).
- WS2812b LED strip. [Link](https://www.amazon.se/-/en/gp/product/B08T89S7C3/ref=ppx_yo_dt_b_asin_title_o04_s01?ie=UTF8&psc=1).
- Some stuff to make it into a cube that can be worn: Cardboard, conduit, wires, duct tape, electric tape, velcro, etc...
- A button and a 100k resistor

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
