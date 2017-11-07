# PEW
Sources for the "Projectile Emulation Weapon" and the associated IR Targets.


## /target
Targets were designed to be as inexpensive as possible. Primarily requires a servo, IR Receiver, and an Adafruit Trinket Pro. Initial PCBs were produced by hand-soldering perfboard. 

### /pcb
Custom PCB was designed in Fritzing and produced by OSH Park
* [View Project on OSH Park](https://oshpark.com/shared_projects/PB0EKyyT)

### /sketch
* **PEW-Hub** contains code for the master Arduino which coordinates the functionality of the targets connected over i2c.
* **PEW-Target** is the code that operates each individual target. 

### /target template
Adobe Illustrator file for cutting out the individual target boxes using a laser cutter. Designed for 5mm plywood, other thicknesses will require significant template modification. The rubber band hook on the target flap needs revisiting to improve ease of use.

## /weapon

### /sketch
* **PEW-Weapon** This code is primarily based on example sketch that ships with Ken Sherriff's [IR Remote](https://github.com/z3t0/Arduino-IRremote) library.
