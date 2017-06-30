#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.hpp"
#include "opencv/highgui.h"

#include "fbutils.hpp"

using namespace cv;

int   main(int   argc , char** argv)
{
#define CV_WIN_NAME "win1"
	if(argc != 4)
		return -1;
	Mat input = imread(argv[1]);
	if (input.empty())
		return -1;
	char buff[256];
	sprintf(buff , "%s:%s" , argv[2] , argv[3]);
	PutOnScreen(input , buff);
	return 0;
}
