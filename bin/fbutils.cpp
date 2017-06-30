#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "opencv/cv.hpp"
#include "opencv/highgui.h"

#define FB_FILENAME "/dev/fb0"

using namespace cv;

static int   FillSceenInfo(void* si)
{
	int   fd;
	fd = open(FB_FILENAME , O_RDWR);
	if(-1 == fd)
	{
		perror("Could not open FB\n");
		return -1;
	}
	if(ioctl(fd , FBIOGET_VSCREENINFO , si) == -1)
	{
		perror("Could not get screen info\n");
		close(fd);
		return -2;
	}
	close(fd);
	return 0;
}

static unsigned char* MapScreen(fb_var_screeninfo* si , int&  ofd , unsigned int&   oscreensize)
{
	int   fd;
	fd = open(FB_FILENAME , O_RDWR);
	if(-1 == fd)
	{
		ofd = -1;
		perror("Could not open FB\n");
		return NULL;
	}	
	ofd = -1;
	unsigned int    screensize = si->xres * si->yres * si->bits_per_pixel / 8;//<= to bytes
	unsigned char* fb = (unsigned char*)mmap(0 , screensize , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0);
	if(!fb){
		perror("Could not allocate FB\n");
		ofd = -1;
		close(fd);
	}
	oscreensize = screensize;
	return fb;
}

static void   FinishMapScreen(unsigned char* fb , const int   ofd , unsigned int   screensize)
{
	munmap(fb , screensize);
	close(ofd);
}

void  PutOnScreen(Mat&  inputImage , char buff[])
{
	struct fb_var_screeninfo vinfo;
	if(FillSceenInfo(&vinfo) < 0)
		return;
	float ratiox = (float)vinfo.xres / (float)inputImage.cols;
	float ratioy = (float)vinfo.yres / (float)inputImage.rows;
	float ratio  = ratiox < ratioy ? ratiox : ratioy;
	Size targetSize((int)(ratio * inputImage.cols) , (int)(ratio * inputImage.rows));
	Mat resized;
	resize(inputImage , resized , targetSize);
	putText(resized , buff , Point(resized.cols / 16 , resized.rows / 3) , FONT_HERSHEY_DUPLEX , 3.0 , Scalar(0 , 0 , 255) , 3);
	int   fd = -1;
	unsigned int   screenbytes;
	unsigned char* fbb = MapScreen(&vinfo , fd , screenbytes);
	if(!fbb)
		return;
	memset(fbb , 0 , screenbytes);
	unsigned short* ush_fbb = (unsigned short*)fbb;
	const int   rowSize4ush = vinfo.xres * vinfo.bits_per_pixel / 8 / sizeof(unsigned short);
	// Draw the image
	int   n_rows = resized.rows < vinfo.yres ? resized.rows : vinfo.yres;
	int   n_cols = resized.cols < vinfo.xres ? resized.cols : vinfo.xres;
	for (int   irow = 0 ; irow < n_rows ; irow++)
	{
		const unsigned char* row = resized.ptr<unsigned char>(irow);
		unsigned short*     orow = &ush_fbb[irow * rowSize4ush];
		for (int   icol = 0 , ipix = 0 ; icol < n_cols ; icol++ , ipix += 3)
		{
			const unsigned char* pixel = &row[ipix];
			unsigned short blue  = (unsigned short)pixel[0];
			unsigned short green = (unsigned short)pixel[1];
			unsigned short red   = (unsigned short)pixel[2];
			unsigned short combined = ((red >> 3) << 11) | ((green >> 2) << 5) | ((blue >> 3) << 0);
			orow[icol] = combined;
		}
	}
	FinishMapScreen(fbb , fd , screenbytes);
}
