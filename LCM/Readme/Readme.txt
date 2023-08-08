This code is a continuation of the stock Floatwheel LCM (Light Control Module). This version offers added features. On the side off the LCM an expended messaging structure was added (to work in combination with the Comm bridge that was created in a custom Float Package).
EEPROM writes and reads, store settings on the LCM without having to flash again. This brings some features such as changing the preset lighting profiles, remembering which profile was last used, changing boot animation and cell type and more.

TODO and/or in the works:
Include Float package buzzer support (let the vesc controll the buzzer).
Add a delay for switching the direction of the main lights.
Add a fade / transition to the lights when switching direction. 

Quick write up for compiling the LCM code:

1: Install Keil μVision
2: Ignore the package manager of keil, you dont need aditional packages
3: Ignore the One or more Device Family Pack Devices are not present
4: In project go to Options for target (Alt + F7) -> In the target window, switch the Arm compiler (V6.19 works)
5: Start the compiling by going to project -> build target (F7)

Download Keil μVision from here
https://www.keil.com/demo/eval/arm.htm
LCM (stock) code:
https://github.com/contactsimonwilson/floatwheel