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
## Homing Adjustments




## Z-Steppers Auto-Alignment **not possible using Prusa Einsy Rambo Board**
Marlin Documentation can be found [here](https://marlinfw.org/docs/configuration/configuration.html#z-steppers-auto-alignment)  
-uncommented line 973 in Configuration_adv.h  
-line 981: #define Z_STEPPER_ALIGN_XY { {  30, 180 }, { 110,  30 }, { 180, 180 } }
## Z-Steppers Auto-Alignment - mechanically forced
The Einsy Rambo board of Prusa MK3 does not support "Z Steppers Auto-Alignment", as one stepper driver is used for both Z-steppers, meaning they are independent of each other.
Nonetheless the Auto-Alignment can be achieved by using [mechanically forced alignment](https://www.reddit.com/r/ender3v2/comments/oy0sct/comment/h7pttyc/?utm_source=share&utm_medium=web2x&context=3) via G-code which was previously M915 (deprecated) on Marlin:

```
; Align X Axis Gantry / Calibrate Dual Z Steppers

; Similar to M915: Mechanical Alignment

G28 ; Home all axes

G0 Z250 ; Go to Z Top Max

M211 S0 ; Disable Software Endstops

G91 ; Relative Positioning

G0 Z10 ; Move up 10 mm to push into mechanical endstops and align stepper steps

G0 Z-10 ; Move down 10 mm

G90 ; Absolute Positioning

M211 S1 ; Enable Software Endstops

G28 ; Home all axes

;G29 ; ABL - BLTouch

M18 S0 Z ; Prevents the idle disabling of the z-steppers
```

## Bed leveling
Bed leveling can be achieved by manual leveling through changing to bed_mesh_leveling in the marlin firmware. [Here](https://all3dp.com/2/mesh-bed-leveling-all-you-need-to-know/) is a tutorial on how it is done.
