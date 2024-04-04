# Note
This page's intention is to assist in the transfer of knowledge between thesis students at the Sustainability Robotics group at EMPA working with the modified 3d printer.
This repository was established by David Niu Bachelor Thesis Spring 2024

A prerequisite for the usage is the successful installation of VS code. Please do that before continuing.




# Instructions for Usage



## First steps
### G-Code generation 
For G-Code generation use the [FullControlXYZ](https://fullcontrol.xyz/) library on python. You may have heard of FullControlXYZ via their viral ball challenge print or their modification of a Prusa MK3 into a 5 axis printer. The FullControlXYZ GitHub repository with can be found [here](https://github.com/FullControlXYZ/fullcontrol). FullControlXYZ is a useful tool to generate G-Code. Using simple python functions, you can draw out your print and translate it into G-Code.
### Control over printer and G-Code uploading
Using [Repetier](https://www.repetier.com/) you can connect your computer with the printer. This allows for direct manual control over the position of your print head and other parameters. Furthermore it allows for fast uploading of the G-Code and a rough preview is depicted.

### Firmware
The control over the different components of the 3D printer is done by the firmware which can be compared how Arduino works. In the firmware standard procedures and parameters are controlled. Adjusting firmware allows for advanced usage of the 3d printer and modification. The original [Prusa Firmware](https://github.com/prusa3d/Prusa-Firmware) is based on the Marlin Firmware. The modified 3d printer uses the Marlin Firmware, which can be found [here](https://marlinfw.org/). The Marlin Firmware is preferred over the original Prusa Firmware because the adjustments are more centralized, allow for more flexibility. A guide on adjusting and flashing the firmware is seen [here](https://youtu.be/eq_ygvHF29I?si=oBdEPBt3eG3QWW10.)
The Marlin Firmware was adjusted to accomodate the limitations and needs of our print setup. All firmware changes deviating from the original "Marlin Prusa MK3" [configuration](https://github.com/MarlinFirmware/Configurations) are listed down below.


# Required G-Code Headers

# Performed Firmware Adjustments
## Homing Adjustments


## Z-Steppers Alignment

### Z-Steppers Auto-Alignment *not possible using Prusa Einsy Rambo Board*
If 2 stepper drivers were available, meaning if separate control over the Z-Steppers was available, the Alignment can be easily done using firmware built-in procedures:
Marlin Documentation can be found [here](https://marlinfw.org/docs/configuration/configuration.html#z-steppers-auto-alignment)  
-uncommented line 973 in Configuration_adv.h  
-line 981: #define Z_STEPPER_ALIGN_XY { {  30, 180 }, { 110,  30 }, { 180, 180 } }
### Z-Steppers Auto-Alignment - mechanically forced
The Einsy Rambo board of Prusa MK3 does not support "Z Steppers Auto-Alignment". Only one stepper driver is used for both Z-steppers, meaning they are independent of each other and are always activated at the same time.
Nonetheless the Auto-Alignment can be achieved using [mechanically forced alignment](https://www.reddit.com/r/ender3v2/comments/oy0sct/comment/h7pttyc/?utm_source=share&utm_medium=web2x&context=3) via G-code which was previously M915 (deprecated) on Marlin. The following G-Code can be added prior to the actual print:

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

# CAD syringe pump
The STL(CAD) files can be found in the folders




# Ystruder
