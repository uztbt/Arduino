# Steps

Source: https://www.youtube.com/watch?v=uMO651YS0y4

1. Unscrew the candy container (Top, Bottom)
1. Rip off

- the wire connecting the circuit board and the touch button
- the wires from the motor
- the wire from the circuit board

1. Unscrew the bottom of the candy container
1. Take off the rubber mashrooms and the screws from the base
1. Rip off the wire of the little switch from the board of the base
1. Discard

- the switch away
- the base board

1. Take off the wire connected to the base of the container

- All wires have been gone away by this step

1. Put the candy container and base together by screwing them back
1. Screw with an electric drill right between the two screws we have just fastened
1. Separate the container and the base again

1. Outline the E-paper module on the base with a pen
1. Mark the screw holes of he E-paper module to make it untouched
1. Cut the bottom along the line
1. Screw the top edge of the E-paper module into the base
1. Screw the lower edge of the E-paper module even it is outside of the base

1. Bend outward the GPIO pins of the ESP32 for use

- EN for reset
- 27
- GND
- 3.3v
- 4
- 5
- 21
- 22
- 23
- 5V (for Lipo)
- GND (for Lipo)

1. Open a hole next to the top right corner of the E-paper module using a soldering iron
1. Make a reset botton sit on the ridge of the hole
1. Screw back the base of the container
1. Take off the golden
1. Solder two jumper wires onto the motor
1. Thread a wire from the top of the base to the bottom and connect it to the ground GPIO pin
1. Do the same thing for the 3V GPIO pin
1. Connect the ground to the motor
1. Bridge the 3V wire and the motor's power in with a transistor

- Positive to the 3v
- Emitter to the other motor
- Base to the GPIO to GPIO 27

1. Put back

- the top of the container
- the candy driver
- the funnel

1. Connect the E-paper module with the ESP32

- SDI to 23
- Clock to 18
- CS to 5
- DC to 22
- RST to 21
- Busy to 4

1. Solder

- 3V from ESP32, the positive from the transistor, and 3V from E-paper module
- GND from ESP32, E-paper module, the motor, and one of the pins of the reset button

1. Connect EN pin to another pin of the reset button
