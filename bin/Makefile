CC     = gcc
IDIR   = /home/pi/opencv-3.0.0/include
CFLAGS = -I. -I$(IDIR) -O3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7
LDIR   = -L/home/pi/opencv-3.0.0/build/lib
LIBS   = -lm -lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc
OBJ    = showtime.o fbutils.o

showtime: $(OBJ)
	$(CC) -o showtime $(OBJ) $(CFLAGS) $(LIBS) $(LDIR)
	
.PHONY: clean

clean:
	rm -f $(OBJ) 
	rm -f showtime
