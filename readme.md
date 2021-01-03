# CMOS Elementary Automata Visualization Board

This is an  open-source KiCad design files for a circuit that could generate and visualize [Elementary Automata](https://mathworld.wolfram.com/ElementaryCellularAutomaton.html) only by using common logic ICs. There are two versions available: Standard and Minimal. 

## Standard Version

![](pics/standard.png)

Standard version is a large board of size 247x127mm (9.7x5in), suitable for putting in a frame. Featuring:

 - 26 Logic ICs in DIP package. (Okay, I have an ATMEGA328 here but it's here just to drive the display. Its firmware is available here as well.)
 - 1.44 inch TFT display with a display driver which can draws a complete picture of that elementary automata rule.
 - Fully visualized 65-bit shift register so you can see how the data flows.
 - Fully selectable 8-bit automata rule input.
 - An LSFR pseudo-random rules generator.
 - Status display.
 - Drawing speed adjustment.
 - All through hole design. Should be relatively easy to solder.

We are currently at Revision 3. Changelog is below:

**Revision 3 (July 2020)**
 - Fixed all of the issues found in rev 2.
 - BOMs consolidated to lessen the unique parts count.
 - New LFSR circuit, the rare CD4006 is no longer required.
 - Updated all footprints to the latest version.
 - Minor changes to the appearances of the PCB.

**Revision 2 (May 2020)**
 - Fixed Connector orientation for the display and the DIP switch.
 - Connected GND to mounting holes
 - Change of parts in the power section due to sourcing issue.
 
**Revision 1 (January 2020)**
 - Initial Design

## Minimal Version

![](pics/minimal.png)

Minimal Version is a smaller board of size 129x72mm (5x3in). It is suitable for carrying around to show off. Featuring:

 - 23 Logic ICs in SOT, SOIC, TSSOP, and TQFP packages.
 - 1.44 inch TFT display.
 - Fully selectable 8-bit automata rule input.
 - An LSFR pseudo-random rules generator.
 - Status display.
 - Drawing speed adjustment.
 - Very challenging SMD soldering practice kit.
 - The PCB should be much cheaper to produce. It's still a little bit too large to fit in 10x10cm requirements for many cheap PCB fabs though, I might try to squeeze it down later.

We are currently at Revision 3. Changelog is below:

**Revision 3 (July 2020)**
 - Fixed all of the issues found in smd rev 2.
 - BOMs consolidated to lessen the unique parts count.
 - New LFSR circuit, the rare CD4006 is no longer required.
 - Updated all footprints to the latest version.
 - Minor changes to the appearances of the PCB.

**Revision 2 (May 2020)**
 - Fixed all of the issues found in rev 1 of the Standard version.
 - Change of parts in the power section due to sourcing issue.
 
**Revision 1 (April 2020)**
 - Initial Design (Based on Standard version)

## What is provided
The goal of this repository is to enable you to build this on your own as easy as possible (although I originally plan to sell this as a kit as well). **I've included all of the schematics, gerbers, BOMs, and display driver firmware for you to use.** And this work is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).

Unfortunately. I have to excluded the 3D models use to render the board in KiCAD because I don't know how each of them was licensed. They are all from GrabCad and you could search and download them by yourself.

**Note: Due to this, there might be a popup warning you about "3D model Search Path" in PCBNew. I honestly don't know how to fix this but it will not affect any KiCAD functionality.**

## Credits
 - DIP switch model by austfox: https://grabcad.com/library/dip-switches-1
 - 1.44inch LCD model by John: https://grabcad.com/library/1-44in-lcd-tft-1
 - Sliding switch model by Jonn: https://grabcad.com/library/selector-switch-assortment-1
 - Trimpot model by Markus Walter: https://grabcad.com/library/bourns-3362p-1-102lf
 - DIP ICs in socket models by Dirk Wouters: https://grabcad.com/library/ic-dip-packages-with-sockets-in-pitch-7-62mm-1
 - TO-220 package model by Egor Chugay: https://grabcad.com/library/to-220-transistor-package-1
 - DC Power Jack model by J. F. Gomez: https://grabcad.com/library/dc-power-jack-5-5mm-x-2-1mm-2-54mm-pitch-1
 - SMD 5032 Crystal 2-Pin model by Dirk Wouters: https://grabcad.com/library/smd-5032-crystal-2-pin-1
 - LED Bar Graph model by austfox: https://grabcad.com/library/led-bar-graph-2
 - 3306P1102, 3362P_1, NE555DR, OS102011MA1QN1, TO229P239X654X978-3P footprint symbols by SamacSys
