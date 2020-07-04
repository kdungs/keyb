---
title: Keyb from scratch
author: Kevin Dungs
date: 2020-07-04
---

# Parts

Ordered from [reichelt.de](https://reichelt.de):

 - 12 Cherry MX Clear switches
 - 12 1N4148 Diodes (TODO: find source article that recommended them)
 - 1 Teensy 4.1

Other stuff I had lying around:

 - Some screws
 - Keycaps (obviously)
 - Header pins for the Teensy
 - A breakout board
 - Wire
 - PLA for the printer

Tools

 - Soldering iron, 3rd hand, airflow thingy, solder
 - 3D printer (we have a CraftBot from
   [RuhrSource](https://www.ruhrsource.com/shop/) in the office)
 - Screwdriver
 - Computer with platformio
 - Micro USB cable


# Case

3D Model from Thingyverse user
[Laffy](https://www.thingiverse.com/laffy/about):
<https://www.thingiverse.com/thing:1312012>

I wanted to include a rotary encoder and LEDs as well but since I gave myself
only one weekend to build it and didn't want to spend all the time learning
Blender, I decided to go with the simple layout for the first version.

# Wiring

 - Thanks to
    - http://www.masterzen.fr/2018/12/16/handwired-keyboard-build-log-part-1/
    - https://matt3o.com/hand-wiring-a-custom-keyboard/.
 - It was a pain, next time I'm going with PCB.


# Lessons learned

Teensy doesn't show up as a device on the Mac, in fact as someone pointed out in a forum:

> There are posts here explaining that teensy uses a special USB protocol for
> downloading. Only if the downloaded program uses Serial will a COM port
> (windows) appear. This confuses AVR Arduino newbies.

Hand-wiring is fun and interesting but a real pain and probably not very
fault-tolerant. Next time around, I'll use a PCB.

3D-printed stuff is nice but I don't know enough about it to make it work at
high quality. So I either have to learn more about it or use laser-cut metal or
something the next time around.

Writing firmware is tricky, I don't think I understood the electronics (pull-up
resistors and diodes) well enough, so I just went trial and error with a
multimeter.


# What's next?

 - A better case
 - Use the rotary encoder
 - LEDs!
