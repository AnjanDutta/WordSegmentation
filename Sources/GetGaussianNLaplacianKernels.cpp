/*
 * GetGaussianNLaplacianKernels.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: Anjan Dutta
 */
#include "../Headers/WordSegmentation.h"

void GetGaussianNLaplacianKernels(double sigma_ys, double sigma_xs, Mat& kernel_x, Mat& kernel_y, Mat& kernel_d2x, Mat& kernel_d2y)
{
	// Sizes of Gaussian and Laplacian kernels
	int halfsize_x = floor(ceil(8*sigma_xs)/2);
	int halfsize_y = floor(ceil(8*sigma_ys)/2);
	int ksize_x = 2*halfsize_x+1;
	int ksize_y = 2*halfsize_y+1;

	// Gaussian kernels
	kernel_x = getGaussianKernel(ksize_x, sigma_xs, CV_32F);
	kernel_y = getGaussianKernel(ksize_y, sigma_ys, CV_32F);

	// Multiplication factor for strange "Laplacian" (please refer to the Matlab code of Manmatha et al.)
	Mat mult_factor_x = Mat::zeros(ksize_x, 1, CV_32F);
	Mat mult_factor_y = Mat::zeros(ksize_y, 1, CV_32F);

	int x = -halfsize_x;
	for(int k = 0; k<ksize_x; k++,x++)
	mult_factor_x.at<float>(k,0) = (pow(x,2) - pow(sigma_xs,2))/(pow(sigma_xs,2)+0.00001);

	int y = -halfsize_y;
	for(int k = 0; k<ksize_y; k++,y++)
	mult_factor_y.at<float>(k,0) = (pow(y,2) - pow(sigma_ys,2))/(pow(sigma_ys,2)+0.00001);

	// Strange "Laplacian" kernels (please refer to the Matlab code of Manmatha et al.)
	kernel_d2x = mult_factor_x.mul(kernel_x);
	kernel_d2y = mult_factor_y.mul(kernel_y);
}
