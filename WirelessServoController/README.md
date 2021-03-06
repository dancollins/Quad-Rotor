Quad Rotor
========================

This source was designed for the PIC18F87J11 PIM for the PICDEM PIC18 Explorer available from microchip.


Contents
--------

* Source for Wireless Servo Control


Description
-----------


To control the servo, I have created a timer interrupt to see when the period should be over (ever 20ms), and when the servo control wire should be high or low (between 1ms and 2ms).  The microcontroller runs at 10MHz, which drivers the timer at 2.5MHz.  This allows for a minimum refresh rate (or the interrupt) of 0.4uS.  Interrupting this often would cause severe interruption to the operation of the main program.  I tuned it for as fast as possible, but a higher clock rate will certainly improve this.  The faster the timer, the higher the resolution can be obtained for the servo position.  The Quad Rotor will be clocked with a 20MHz crystal, which will mean a 5MHz timer.  Hopefully this will provide a much smoother servo and ESC control.

Copyright [Dan Collins](http://dancollins.github.com/) 2011.  Released under the POPL licence (see LICENCE.TXT)
