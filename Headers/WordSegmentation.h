/*
 * WordSegmentation.h
 *
 *  Created on: Jun 23, 2016
 *      Author: Anjan Dutta
 */

#ifndef HEADERS_WORDSEGMENTATION_H_
#define HEADERS_WORDSEGMENTATION_H_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

vector<Rect> WordSegmentationMorph(Mat image, int se_size);
vector<Rect> WordSegmentationScSp(Mat image, int se_size);
void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
void RemoveBorderElements(Mat src, Mat& dst);
void GetGaussianNLaplacianKernels(double sigma_ys, double sigma_xs, Mat& kernel_x, Mat& kernel_y, Mat& kernel_d2x, Mat& kernel_d2y);
char* GetTextFileName(char *str);

#endif /* HEADERS_WORDSEGMENTATION_H_ */
