
//灰度拉伸

#include <opencv2/opencv.hpp>

/**
 * 对输入的灰度图像应用灰度拉伸变换。
 *
 * @param src 输入的灰度图像，必须是单通道图像。
 * @param x1 第一个转折点的灰度值，该值以下的像素将被映射到y1。
 * @param y1 第一个转折点的映射值，x1以下的像素将被拉伸到这个值。
 * @param x2 第二个转折点的灰度值，该值以上的像素将被映射到y2。
 * @param y2 第二个转折点的映射值，x2以上的像素将被拉伸到这个值。
 * @return dst 经过灰度拉伸变换后的图像，与输入图像具有相同的大小和类型。
 */
cv::Mat grayScaleStretching(const cv::Mat& src, int x1, int y1, int x2, int y2) 
{
    /*if (src.channels() != 1) {
        std::cerr << "Error: Source image must be grayscale." << std::endl;
        return cv::Mat();
    }*/

    cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC1);

    double m = static_cast<double>(y2 - y1) / (x2 - x1);
    double b = y1 - m * x1;

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int x = src.at<uchar>(i, j);
            uchar new_val;

            if (x <= x1) {
                new_val = static_cast<uchar>(y1);
            }
            else if (x >= x2) {
                new_val = static_cast<uchar>(y2);
            }
            else {
                new_val = static_cast<uchar>(m * (x - x1) + y1);
            }

            new_val = std::min(std::max(new_val, (uchar)0), (uchar)255);
            dst.at<uchar>(i, j) = new_val;
        }
    }
    return dst;
}