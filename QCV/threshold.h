#pragma once

#include <opencv2/opencv.hpp>

double iterativeThreshold(cv::Mat& src, cv::Mat& dst, double initialThresh, double threshDelta=254.0);	//Ä¬ÈÏµü´úµ½254

double otsuThreshold(const cv::Mat& grayImage);

Mat adaptiveThresholdSegmentation(const cv::Mat& inputImage);

cv::Mat applyBestThreshold(const cv::Mat& src, double bestThreshold);

double maximumEntropyThresholding(const cv::Mat& grayImage);