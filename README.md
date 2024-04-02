# Introduction
This page is intended to assist in knowledge transfer between thesis students in the Sustainability Robotics group at EMPA working with the 3D printer.




# Instructions for Usage

## First steps
For G-Code generation use the Fullcontrol_xyz library on python.
Using Repetier you can connect your computer with the printer and manually control the position of your print head and other parameters. Through Repetier you can transfer your G-code to the printer and printing. 



## G-Code
### [G34](https://marlinfw.org/docs/gcode/G034-zsaa.html) - Z-Steppers Auto-Alignment
Using 2 stepper motors for Z-Axis control, both stepper motors need to be aligned:





# Performed Firmware Adjustments
## Z-Steppers Auto-Alignment
Marlin Documentation can be found [here](https://marlinfw.org/docs/configuration/configuration.html#z-steppers-auto-alignment).
-uncommented line 973 in Configuration_adv.h.
-line 981: #define Z_STEPPER_ALIGN_XY { {  30, 180 }, { 110,  30 }, { 180, 180 } }


## Bed leveling
Bed leveling can be achieved by manual leveling through changing to bed_mesh_leveling in the marlin firmware. [Here](https://all3dp.com/2/mesh-bed-leveling-all-you-need-to-know/) is a tutorial on how it is done.
