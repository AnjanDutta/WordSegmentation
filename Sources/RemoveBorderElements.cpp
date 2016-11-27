/*
 * RemoveBorderElements.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: Anjan Dutta
 */
#include "../Headers/WordSegmentation.h"
void RemoveBorderElements(const Mat src, Mat& dst)
{
	dst = src.clone();

	int height = dst.rows;
	int width = dst.cols;

	// First check the borders along the left and right side (two pixels each side)
	for(int i = 0; i<height; i++)
	{
		if(dst.at<uchar>(i,0)==255)
			floodFill(dst, Point(0,i), Scalar(0));

		if(dst.at<uchar>(i,1)==255)
			floodFill(dst, Point(1,i), Scalar(0));

		if(dst.at<uchar>(i,width-1)==255)
			floodFill(dst, Point(width-1,i), Scalar(0));

		if(dst.at<uchar>(i,width-2)==255)
			floodFill(dst, Point(width-2,i), Scalar(0));
	}
	// First check the borders along the left and right side (two pixels each side)
	for(int j = 0; j<width; j++)
	{
		if(dst.at<uchar>(0,j)==255)
			floodFill(dst, Point(j,0), Scalar(0));

		if(dst.at<uchar>(1,j)==255)
			floodFill(dst, Point(j,1), Scalar(0));

		if(dst.at<uchar>(height-1,j)==255)
			floodFill(dst, Point(j,height-1), Scalar(0));

		if(dst.at<uchar>(height-2,j)==255)
			floodFill(dst, Point(j,height-2), Scalar(0));
	}

}
