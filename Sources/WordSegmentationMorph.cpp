/*
 * WordSegmentationMorph.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: Anjan Dutta
 */

#include "../Headers/WordSegmentation.h"

vector<Rect> WordSegmentationMorph(Mat image, int erosion_size)
{
	Mat gray_image, erosion_image, binary_image;

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	cvtColor( image, gray_image, CV_BGR2GRAY );

	Mat element = getStructuringElement( MORPH_CROSS,
		  Size( 2*erosion_size + 1, erosion_size ),
		  Point( erosion_size+1, (erosion_size-1)/2 ) );

	erode( gray_image, erosion_image, element );

	threshold(erosion_image,binary_image,0,255,THRESH_BINARY_INV|THRESH_OTSU);

	findContours( binary_image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	for( unsigned int i = 0; i < contours.size(); i++ )
	{
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
	}

	return boundRect;

}

