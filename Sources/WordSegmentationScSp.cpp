/*
 * WordSegmentationScSp.cpp
 *
 *  Created on: Jun 29, 2016
 *      Author: Anjan Dutta
 */

#include "../Headers/WordSegmentation.h"

vector<Rect> WordSegmentationScSp(Mat image, int se_size)
{
	Mat gray_image;
	double eta = 4.0, *sigma_xs, *sigma_ys, contour_area, thresh_contour_area = 200;
	int nsigmas = 24, nonz_pixs, max_nonz_pixs = 0, index_max_nonz_pixs = 0, thresh = 2;

	Mat binary_images[nsigmas];

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<int> small_blobs;

	// Convert the image to gray scale
	cvtColor( image, gray_image, CV_BGR2GRAY );

	// Set the sigmas (scales) for Gaussian filter
	sigma_ys = new double[nsigmas];
	sigma_xs = new double[nsigmas];
	for(int i = 0; i<nsigmas; i++)
	{
		sigma_ys[i] = 1 + (double)i*0.3;
		sigma_xs[i] = eta * sigma_ys[i];
	}

//	namedWindow( "Gray Image", CV_WINDOW_AUTOSIZE );
//	imshow( "Gray Image", gray_image );

	max_nonz_pixs = 0;

	for(int i = 0; i<nsigmas; i++)
	{
		// Get Gaussian and Laplacian kernels
		Mat kernel_x, kernel_y, kernel_d2x, kernel_d2y;
		GetGaussianNLaplacianKernels(sigma_ys[i], sigma_xs[i],
				kernel_x, kernel_y, kernel_d2x, kernel_d2y);

		// Convolution
		Mat gauss_x, lapl_gauss_x, lapl_y, gauss_lapl_y;
		filter2D(gray_image,gauss_x,CV_32F,kernel_x);
		filter2D(gauss_x,lapl_gauss_x,CV_32F,kernel_d2x);
		filter2D(gray_image,lapl_y,CV_32F,kernel_d2y);
		filter2D(lapl_y,gauss_lapl_y,CV_32F,kernel_y);

		// Final Laplacian
		Mat lapl_gauss = lapl_gauss_x+gauss_lapl_y;

		// Thresholding
		binary_images[i] = lapl_gauss > thresh;

		// Remove elements on the boundary
//		RemoveBorderElements(binary_images[i],binary_images[i]);

		// Count number of white pixels for maximizing
		nonz_pixs = countNonZero(binary_images[i]);

		if (nonz_pixs > max_nonz_pixs)
		{
			max_nonz_pixs = nonz_pixs;
			index_max_nonz_pixs = i;
		}

	}

	delete sigma_ys;
	delete sigma_xs;

	Mat binary_image = binary_images[index_max_nonz_pixs];

	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(2*se_size+1,2*se_size+1),Point(-1,-1));

	dilate(binary_image, binary_image, se);

	// Contour analysis for small blobs removal and getting the bounding boxes around the bigger ones
	findContours( binary_image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// First eliminate the contours whose area is less than a threshold 'thresh'
	if (!contours.empty())
	{
	    for (size_t t=0; t<contours.size(); )
	    {
	        contour_area = -contourArea(contours[t],true);
	        if (contour_area < thresh_contour_area)
	        	contours.erase(contours.begin() + t);
	        else
	        	t++;
	    }
	}

//	Approximate remaining contours to polygons + get bounding rectangles
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	int i = 0;
	for(size_t t=0; t < contours.size(); t++, i++ )
	{
		approxPolyDP( Mat(contours[t]), contours_poly[t], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[t]) );
	}

	return boundRect;

}
