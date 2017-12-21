# Clock and digital frame

!Disclaimer!
No warrany, liability whatsoever.
Don't come crying complaining whining or suing me.
-----

Hi,
this is the code for creating a clock made of raspberry pi and display, every minute changing the image and the time.

HW:
---
* Rpi 2B (or rpi3, but I have not tested this option).
* WiFi dongle (WiPi. Trying to install a wifi dongle with "linux" on the box broke my heart. If it's a rpi 3 you don't need it).
* Micro SD
* Power adaptor
* 7" LCD acreen + case, https://www.talmir.co.il/product/23867.htm

The micro SD is for the RPI. Then you'll load the project etc.

3rd party:
----------
Have Make installed.
Install opencv http://www.pyimagesearch.com/2016/04/18/install-guide-raspberry-pi-3-raspbian-jessie-opencv-3/
*Skip* the virtual env/wrapper bit.

The code:
---------
rc.local is a file that runs on start. It calls alwaysdisplay.sh. These take care that the display
does not go to sleep. rc.local is in /etc/ directory.
Set the path to alwaysdisplay.sh well.

crontab.txt includes the line you should add using crontab -e.
It calls the script eachminute.pl.

eachminute.pl draws an image, records the time and calls the showtime executable to display it.
The script displays the big ben each half hour, you can change it so it always draws one of your 
images, as you want.

In the bin directory you have the source and Makefile for the showtime executable.
the executable gets the path to the image and the time.
Using OpenCV it reads the image and draws on it the time (only in the display, does not destroy
the original).

Have a look at the directories of the eachminute.pl script and change it accordingly.

I recommmend that the images are in .jpg format.

I use this clock together with this: http://www.instructables.com/id/Raspberry-Pi-Big-Ben-Clock/

I could not have accomplished this project without this great book:
https://cse.sc.edu/~jbakos/textbook/
Embedded Systems:
ARM Programming and Optimization
By Prof. Jason D. Bakos.


Good luck!
Enjoy!

U
