Yamaha Battery Dongle for use with
YAMAHA PW, PW-SE and PW-X Downtube Batteries (may work with intube aswell)
Suited for All PASB batteries with 3 Pins, usually found on Haibike ebikes.

Doesnt work with 5 pin Giant Batteries!, even tho they are Yamaha. they use can-bus (for no reason, they convert back to serial in the motor again..)


It immitates a original battery, so you are able to connect any 36V source you want.


Arduino firmware code in Code folder, to flash onto the dongle, you may require a arduino package that supports Attiny13's like https://github.com/MCUdude/MicroCore </br>you may need to adjust timings if your arduino board (like Attiny13 pcb's) doesnt have a calibrated clock. A sound card and audacity can be used for this in case you got no scope / logic analyzer.
Schematics for use with EasyEDA in schematics folder.

German discussion:
https://www.pedelecforum.de/forum/index.php?threads/yamaha-reverse-engineering.39480/
easyeda page: https://easyeda.com/gamerpaddy/yamaha-accu-dongle-v4
</br>
</br>
</br>

<h2><b>FAQ:</b></h2>

<b>Can i use rc hobby grade LiPos? </b>

Yes
</br>

<b>What Batteries can i use?</b>

if you stay within the voltage range of the original battery, you can use anything.. even a Diesel generator. 36V is 36V (27-42V is the usual range on li_ion 10S packs).
</br></br>

<b>How do i calibrate it?</b>

You need a oscilloscope, logic analyzer (the <5$ work just fine) or a sound card (be careful, limit the voltage before hooking it up) and a soundcard-oscilloscope program or audacity</br>
in the code are timings mentioned at the very top, try to edit these and reflash the firmware until they have the timings required.</br>

</br>

<b>Do i need to use this dongle hardware?</b></br>
No, you can use any Microcontroller, you may need to adjust the Pin definitions and timings depending on what you use. just replace sendChar with the serial write command your MCU uses. set your Serial to 2400 BAUD at 8 bits, Even parity, 1 stop bit. (2400_8E1 in arduino)</br>
ideally you use hardware serial (arduino uno, mini etc.) since its more stable and doesnt require calibration unlike software serial on the attiny13.  this code is intended for use with the dongle, which uses a Attiny13. take a look at the schematic to get a idea how to control the signal line</br></br>

<b>Does this work with my Bike?</b></br>
This works with most Yamaha ebikes having the PW series Motors. its important that the battery has 3 pins (or 7 for the intube battery). then it should work without problem.</br>
if it doesnt work (display turns off after 4 seconds again) check if your bike even works with a working battery, if yes or if you dont know, adjust the timings of this dongle as mentioned above.</br>
on most giant ebikes with yamaha it wont work, since they use CAN bus for communication</br></br>

<b>My battery wont go below 5% whats happening</b></br>
i capped the minimum to 5% since i estimate the leftover charge by the battery voltage, which sags under load. without this your motor might turn off in high load situations (going uphill etc.)
</br>
</br>
</br>
</br>



DISCLAIMER:

keep in mind, anything can happen. 
Many people have successfully built this and used it for many thousands of kilometers since 2016. 
But theres allways a chance of something going wrong. 
if something breaks, even if its you, <b>its your problem</b>.
