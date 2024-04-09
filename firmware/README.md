
# Performed Firmware Adjustments
## Notes
Marlin Firmware stands as a continually evolving cornerstone of 3D printing, marked by its perpetual updates and collaborative development. Its modular architecture and open-source ethos ensure adaptability and innovation, empowering users to push the boundaries of additive manufacturing. Therefore, meticulous documentation of firmware adjustments is crucial, enabling smooth transitions to newer versions of Marlin Firmware.

## Extruder Adjustments
Because the extruding mechanism is different, this has to be adjusted in the Firmware. 



````
#if ENABLED(GEARBOX_BEAR)
  #define DEFAULT_AXIS_STEPS_PER_UNIT { 100, 100, 3200/8, 490 }
#else
  #define DEFAULT_AXIS_STEPS_PER_UNIT { 100, 100, 3200/8, ***800*** }
#endif

````

## Bed Size Adjustments
In Configuration.h, line 1753 "geometry section", the values are adjusted according to the syringe position and the syringe holder.
```
// @section geometry

// The size of the printable area
#define X_BED_SIZE 225
#define Y_BED_SIZE 200

// Travel limits (linear=mm, rotational=°) after homing, corresponding to endstop positions.
#define X_MIN_POS 1.5
#define Y_MIN_POS -20
#define Z_MIN_POS 0
#define X_MAX_POS 226.5
#define Y_MAX_POS 220
```

1756 in Configuration.h 
Due to the size of the syringe holder, the printable bed size is limited. The X_Bed_Size is reduced from 250 mm to 230 mm. The Y_Bed_Size




## Homing Adjustments
### Note
Please note that the Z-Axis adjustments are dependent on the position of the PINDA (Prusa INDuktion Autoleveling Sensor). Should the syringe holding part be changed or the PINDA be reattached, after-homing-values will need to be adjusted accordingly. Also note that the PINDA uses induction to detect the print bed, meaning it can only detect conducting (metallic) print beds. When using a non-metallic print substrate, adjust the distance accordingly with Z_OFFSET_WIZARD, which will be covered down below.
### Safe Homing
Homing can be performed while the syringe tip is attached (Bed Leveling must not be done with attached syringe or tip). To ensure safe homing, "Z_SAFE_HOMING" is enabled. The Z-Homing position is set at a point where the syringe is outside of the bed. This enables homing with the syringe even though the syringe tip is protruding compared to the probe. The code for Z_SAFE_HOMING can be found in Configuration.h in line 2156.
```
#define Z_SAFE_HOMING

#if ENABLED(Z_SAFE_HOMING)
  #define Z_SAFE_HOMING_X_POINT 100  // (mm) X point for Z homing
  #define Z_SAFE_HOMING_Y_POINT 0  // (mm) Y point for Z homing
#endif
```
Additionally by defining the height before and after homing, bumping of syringe tip and print bed is prevented. The responsible code is in Configuration.h in line 1736.

```
#define Z_HOMING_HEIGHT  20      // (mm) Minimal Z height before homing (G28) for Z clearance above the bed, clamps, ...
                                  // Be sure to have this much clearance over your Z_MAX_POS to prevent grinding.

#define Z_AFTER_HOMING  20      // (mm) Height to move to after homing Z
```
### Adjusting Offset between Probe and Needle Tip - Offset Wizard
Using the PROBE_OFFSET_WIZARD function, the calibration of the offset between probe and needle can be done. Additionally this allows for calibration before a print when the print substrate cannot be detected by the PINDA. The code can be found in Configuration_adv.h in line 1382. Use an initial offset, "PROBE_OFFSET_WIZARD_START_Z", greater than the expected offset and adjust via LCD menu. When printing on the print bed provided by Prusa, an initial offset of 12 mm was chosen. When printing with additional non-metallic substrates, increase the initial offset accordingly. Afterwards use the LCD menu: Motion -> Z Probe Wizard, to fine-tune the distance. The method used, which is also quite a common method in robotics, is to put a sheet of paper underneath the syringe tip and adjust the tip so that there is adequate resistance when trying to remove the paper.
This method allows you to keep all of the previously performed steps such as Bed Leveling and Homing, which would be otherwise deleted when pressing "Notstopp" in the Repetier program. PROBE_OFFSET_WIZARD can be called using the M851 G-Code.


```
#if HAS_BED_PROBE && EITHER(HAS_MARLINUI_MENU, HAS_TFT_LVGL_UI)
  #define PROBE_OFFSET_WIZARD       // Add a Probe Z Offset calibration option to the LCD menu
  #if ENABLED(PROBE_OFFSET_WIZARD)
    /**
     * Enable to init the Probe Z-Offset when starting the Wizard.
     * Use a height slightly above the estimated nozzle-to-probe Z offset.
     * For example, with an offset of -5, consider a starting height of -4.
     */
    #define PROBE_OFFSET_WIZARD_START_Z 12

    // Set a convenient position to do the calibration (probing point and nozzle/bed-distance)
    X_CENTER = 100
    Y_CENTER = 100
    #define PROBE_OFFSET_WIZARD_XY_POS { X_CENTER, Y_CENTER }
  #endif
#endif
```

When enabling ```PROBE_OFFSET_WIZARD_XY_POS { X_CENTER, Y_CENTER }```, disable in **draw_z_offset_wizard.cpp (with the path: \Marlin-2.1.2.2\Marlin\src\lcd\extui\mks_ui\draw_z_offset_wizard.cpp)** line 115 and 116. This prevents a z-homing move when the probe offset wizard goes to its XY_POS.




```
#if HOMING_Z_WITH_PROBE && defined(PROBE_OFFSET_WIZARD_START_Z)
        //set_axis_never_homed(Z_AXIS); // On cancel the Z position needs correction
        //queue.inject_P(PSTR("G28Z"));

```




## Z-Steppers Alignment

### Z-Steppers Auto-Alignment *not possible using Prusa Einsy Rambo Board*
If 2 stepper drivers were available, meaning if separate control over the Z-Steppers was available, the Alignment can be easily done using firmware-built-in procedures. Marlin Documentation can be found [here](https://marlinfw.org/docs/configuration/configuration.html#z-steppers-auto-alignment). Unfortunately this is not possible with our printer.
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
Bed leveling can be achieved using different methods. In Configuration.h, line 1937, the leveling type can be set. The manual leveling through bed_mesh_leveling using the syringe tip might be the most precise (a detailed tutorial can be found [here](https://all3dp.com/2/mesh-bed-leveling-all-you-need-to-know/)), but due to practicality the 3-point leveling method(AUTO_BED_LEVELING_3POINT) was chosen. **This leveling method must not be performed while the syringe tip is attached!**. Enabling line 1954 in Configuration.h ```#define RESTORE_LEVELING_AFTER_G28```, bed leveling will be restored when performing homing after bed leveling.


by manual leveling through changing to bed_mesh_leveling in the marlin firmware. [Here](https://all3dp.com/2/mesh-bed-leveling-all-you-need-to-know/) is a tutorial on how it is done.



```
#if EITHER(AUTO_BED_LEVELING_3POINT, AUTO_BED_LEVELING_UBL)
  #define PROBE_PT_1_X 30
  #define PROBE_PT_1_Y 200

  #define PROBE_PT_2_X 200
  #define PROBE_PT_2_Y 200
  
  #define PROBE_PT_3_X 200
  #define PROBE_PT_3_Y 30
#endif
```