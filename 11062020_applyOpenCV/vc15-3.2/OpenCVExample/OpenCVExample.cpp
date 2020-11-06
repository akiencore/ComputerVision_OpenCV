#ifdef _CH_
#pragma package <opencv>
#endif

#include "opencv\cv.h"
#include "opencv\highgui.h"

int main(int argc, char** argv)
{
	//create 2 images
	IplImage* image = 0, * resizedImage = 0;
	
	//if got the input of 2 strings, the filename is the 2nd input string
	//otherwise, the default file name is "image01.jpg"
	char* filename = argc == 2 ? argv[1] : (char*)"image01.jpg";

	//load the image with the filename into image
	image = cvLoadImage(filename, 1);

	//if that image doesn't exist, return error
	if (image == 0)
		return -1;

	//show size and channels of the image
	printf("Image width %d \nImage height %d\nchannels %d \n", image->width, image->height, image->nChannels);

	//create a new image size
	int scale_percent = 70;
	int width = (image->width * scale_percent / 100);
	int height = (image->height * scale_percent / 100);

	//set size, depth, and channels of the resized image
	resizedImage = cvCreateImage(cvSize(width, height), image->depth, image->nChannels);
	//convert the image into a new size, and assign it to the resized image
	cvResize(image, resizedImage, 1);

	//show size and channels of the resized image
	printf("Resized image width %d \nResized image height %d\nchannels %d \n", resizedImage->width, resizedImage->height, resizedImage->nChannels);

	//create windows
	cvNamedWindow("Source", 1);
	cvNamedWindow("Resize", 1);

	//show images in windows
	cvShowImage("Source", image);
	cvShowImage("Resize", resizedImage);

	//wait for a key stroke, and close all windows
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&resizedImage);
	cvDestroyWindow("Source");
	cvDestroyWindow("Resize");

	return 0;
}