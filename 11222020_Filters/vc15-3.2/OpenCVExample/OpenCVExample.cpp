#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;
#define NORMAL_HT

Mat image, avg33, avg55, gau33, gau55, mid3, mid5, mid9;
//Mat here represents image, an image is a matrix of pixel color intensity

int main(int argc, char** argv)
{	
	//if got the input of 2 strings, the filename is the 2nd input string
	//otherwise, the default file name is "image01.jpg"
	string filename = "image01.jpg";
	if (argc == 2) {
		filename = argv[1];
	}

	//load the image with the filename into image
	//the second parameter is "is a colored image?"
	image = imread(filename, 1);

	//if that image doesn't exist, return error
	if (image.empty())
	{
		printf("Cannot read image file: %s\n", filename.c_str());
		return -1;
	}

	//average filter
	blur(image, avg33, Size(3, 3));
	blur(image, avg55, Size(5, 5));
	//gaussian filter
	GaussianBlur(image, gau33, Size(3, 3), 0);
	GaussianBlur(image, gau55, Size(5, 5), 0);
	//median filter
	medianBlur(image, mid3, 3);
	medianBlur(image, mid5, 5);
	medianBlur(image, mid9, 9);

	// create windows of images
	namedWindow("Input", 1);
	namedWindow("Average Smooth, kernel size 3x3", 1);
	namedWindow("Average Smooth, kernel size 5x5", 1);
	namedWindow("Gaussian Smooth, kernel size 3x3", 1);
	namedWindow("Gaussian Smooth, kernel size 5x5", 1);
	namedWindow("Median Smooth, ksize = 3", 1);
	namedWindow("Median Smooth, ksize = 5", 1);
	namedWindow("Median Smooth, ksize = 9", 1);

	//show images
	imshow("Input", image);
	imshow("Average Smooth, kernel size 3x3", avg33);
	imshow("Average Smooth, kernel size 5x5", avg55);
	imshow("Gaussian Smooth, kernel size 3x3", gau33);
	imshow("Gaussian Smooth, kernel size 5x5", gau55);
	imshow("Median Smooth, ksize = 3", mid3);
	imshow("Median Smooth, ksize = 5", mid5);
	imshow("Median Smooth, ksize = 9", mid9);

	waitKey(0);

	return 0;
}