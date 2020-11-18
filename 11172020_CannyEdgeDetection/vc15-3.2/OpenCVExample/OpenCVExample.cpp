#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;
#define NORMAL_HT

int edgeThreshold = 100;
Mat image, gray, edge, cedge; //cedge is "colored edge", edge is "grayscale edge"
//Mat here represents image, an image is a matrix of pixel color intensity 

// define a trackbar callback
static void onTrackbar(int, void*)
{
	//blur grayscale image to edge image with a 5*5 matrix
	blur(gray, edge, Size(5, 5));

	//run the edge detector on grayscale
	//Canny Edge Detector: upper threshold is 2*threshold, lower threshold is threshold
	Canny(edge, edge, edgeThreshold, edgeThreshold * 2, 3);

	//set the scalar of colored edge matrix into 0
	cedge = Scalar::all(0);
	//used filtered edge as mask to copy edge data into cedge, and get a colored edge image
	image.copyTo(cedge, edge);

	imshow("Edge map", cedge);
	imshow("Grayscale Edge map", edge);
}

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

	//create a colored edge matrix with the size and type of the image
	cedge.create(image.size(), image.type());
	//convert image to grayscale image
	cvtColor(image, gray, COLOR_BGR2GRAY);

	// create a window of the edge map
	namedWindow("Edge map", 1);

	// create a trackbar
	createTrackbar("Canny threshold", "Edge map", &edgeThreshold, 200, onTrackbar);

	onTrackbar(0, 0);

	waitKey(0);

	return 0;
}