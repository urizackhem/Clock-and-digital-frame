# Clock and digital frame

!Disclaimer!
No warrany, liability whatsoever.
Don't come crying complaining whining or suing me.
-----

Hi,
this is the code for creating a clock made of raspberry pi and display, every minute changing the image and the time.

HW:
---
* Rpi 2B
* WiFi dongle
* Micro SD
* Power adaptor
* 7" LCD acreen + case, https://www.talmir.co.il/product/23867.htm

I used a RPI 2 but RPI 3 may do as well and then you don't need the wifi dongle.
The micro SD is for the RPI. Then you'll load the project etc.

3rd party:
----------
Have Make installed.
Install opencv http://www.pyimagesearch.com/2016/04/18/install-guide-raspberry-pi-3-raspbian-jessie-opencv-3/
Skip the virtual env/wrapper bit.

The code:
---------
rc.local is a file that runs on start. It calls alwaysdisplay.sh. These take care that the display
does not go to sleep. rc.local is in /etc/ directory.
Set the path to alwaysdisplay.sh well.

