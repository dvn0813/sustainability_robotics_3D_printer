# Note
The purpose of this page is to facilitate knowledge exchange among thesis students within the Sustainability Robotics group at EMPA who are working with the modified 3D printer. This repository was established by David Niu for his Bachelor's Thesis in Spring 2024.

Before proceeding, it is essential to ensure that VS Code is successfully installed. Please complete this prerequisite before continuing.



# Instructions for Usage



## First steps
### G-Code generation 
To generate G-Code, employ the [FullControlXYZ](https://fullcontrol.xyz/) library in Python. You might be familiar with FullControlXYZ from their popular ball challenge print or their conversion of a Prusa MK3 into a 5-axis printer. Access the FullControlXYZ GitHub repository [here](https://github.com/FullControlXYZ/fullcontrol). FullControlXYZ serves as a valuable tool for G-Code generation. By utilizing straightforward Python functions, you can sketch your print and convert it into G-Code effortlessly.
### Control over printer and G-Code uploading
Using [Repetier](https://www.repetier.com/) you can connect your computer with the printer. This allows for direct manual control over the position of your print head and other parameters. Furthermore it allows for fast uploading of the G-Code and a rough preview is depicted.

### Firmware
The control over the different components of the 3D printer is done by the firmware which can be compared how Arduino works. In the firmware standard procedures and parameters are controlled. Adjusting firmware allows for advanced usage of the 3d printer and modification. The original [Prusa Firmware](https://github.com/prusa3d/Prusa-Firmware) is based on the Marlin Firmware. The modified 3d printer uses the Marlin Firmware, which can be found [here](https://marlinfw.org/). The Marlin Firmware is preferred over the original Prusa Firmware due to its centralized adjustments. Nearly all adjustments can be performed via the two files Configuration.h and Configuration_adv.h. A guide on adjusting and flashing the firmware can be found [here](https://youtu.be/eq_ygvHF29I?si=oBdEPBt3eG3QWW10.)
The Marlin Firmware was adjusted to accomodate the needs and limitations of our print setup. All firmware changes deviating from the original "Marlin Prusa MK3" [configuration](https://github.com/MarlinFirmware/Configurations) are listed down below.

# Your first print
1. Write the code for your desired pattern on python using FullControlXYZ
2. Run your code to obtain the G-Code file
3. Connect your computer to the 3d printer
4. Insert your G-Code.
5. Automatically run Homing, Bed Leveling, Homing and Probe-Offset-Wizard without syringe.
6. When calibrating with Offset-Wizard, attach your syringe and move the syringe on top of the print bed using Repetier (Y:+10).
7. Calibrate with a piece of paper until adequate resistance
8. Start with your print

# Required G-Code Headers
## Complete Calibration (without syringe at the beginning)
```
M83 ; relative extrusion
M140 S0 ; set bed temp and continue
M104 S0 ; set hotend temp and continue
M190 S0 ; set bed temp and wait
M109 S0  ; set hotend temp and wait
M106 S0 ; set fan speed


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

G28 ; Homing
G29 ; Bed leveling
M0 [attach syringe] ; 
M851 ; Homing and then Probe-Offset-Wizard
```
## Homing and Probe-Offset-Wizard
```
M83 ; relative extrusion
M140 S0 ; set bed temp and continue
M104 S0 ; set hotend temp and continue
M190 S0 ; set bed temp and wait
M109 S0  ; set hotend temp and wait
M106 S0 ; set fan speed

M851 ; Homing and then Probe-Offset-Wizard
```
# Required FullControlXYZ headers
Any FullControlXYZ .py file can be taken as example. The printer_name is taken as "generic" as the Marlin firmware is used.
The following G-Code header will be automatically added by FullControlXYZ when using 




## Retraction settings
Retraction settings can be managed through the firmware. In our case it is beneficial to adjust retraction through the G-Code as adjustments need to be made for different printing materials. The G-Code ```M207 S0.01 F30``` is used to set the amount and speed of retraction. The G-Code ```M208 S0.1 F30``` is used to set the surplus amount and speed of unretraction.
```
steps.append(fc.ManualGcode(text = 'M207 S0.01 F30'))
steps.append(fc.ManualGcode(text = 'M208 S0.1 F30'))
```


# CAD syringe pump
The STL(CAD) files can be found in the folders




# Ystruder
