/*
 * MainWordSegmentation.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: Anjan Dutta
 */

#include "../Headers/WordSegmentation.h"

int main( int argc, char** argv )
{

	int se_size = 7;
	Scalar color = Scalar( 255, 0, 0);
	FILE *fp;

	Mat image;

	image = imread( argv[1] , 1 );

	if( argc != 4 || !image.data )
	{
		printf( "No image data \n" );
		return -1;
	}

	// Call the word segmentation module

	// Word Segmentation based on Morphology
	//	vector<Rect> boundRect = WordSegmentationMorph(image, se_size);

	// Word Segmentation based on Scale Space
	vector<Rect> boundRect = WordSegmentationMorph(image, se_size);

	// Draw bounding rectangles
	Mat drawing = image.clone();

	//	char* TextFileName = GetTextFileName(argv[1]);

	fp = fopen( argv[2] , "w" );

	for( unsigned int i = 0; i < boundRect.size(); i++ )
	{
		rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		fprintf(fp,"x = %d, y = %d, w = %d, h = %d\n", boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height);
		//        printf("%d,%d,%d,%d\n",boundRect[i].x, boundRect[i].y,
		//        		boundRect[i].x+boundRect[i].width,boundRect[i].y+boundRect[i].height);
	}

	fclose(fp);

	imwrite( argv[3] , drawing );

	//  namedWindow( "Bounding Boxes", CV_WINDOW_AUTOSIZE );
	//	imshow( "Bounding Boxes", drawing );
	//	waitKey(0);

	return 0;
}
