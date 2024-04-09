M83 ; relative extrusion
M140 S0 ; set bed temp and continue
M104 S0 ; set hotend temp and continue
M190 S0 ; set bed temp and wait
M109 S0  ; set hotend temp and wait
M106 S0 ; set fan speed
G0 F8000 X10.0 Y30.0 Z0.1
G28
G29
M500
