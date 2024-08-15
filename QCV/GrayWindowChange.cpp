#include <opencv2/opencv.hpp>


// 灰度窗口变换函数
/**
 * 对图像进行灰度窗口变换，将指定灰度区间 [L, U] 内的像素值设为255，其他像素值保持不变。
 *
 * @param src 原始的单通道灰度图像。
 * @param L 窗口变换的下限阈值。
 * @param U 窗口变换的上限阈值。
 * @return 变换后的灰度图像。
 */
cv::Mat grayWindowTransform(const cv::Mat& src, int L, int U) 
{
    // 创建一个与源图像相同大小和类型的新图像
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());

    // 遍历图像中的每个像素
    for (int y = 0; y < src.rows; ++y) {
        for (int x = 0; x < src.cols; ++x) {
            // 获取当前像素的灰度值
            uchar pixelValue = src.at<uchar>(y, x);

            // 检查像素值是否在窗口的下限和上限之间
            if (pixelValue >= L && pixelValue <= U) {
                // 如果在范围内，将像素值设置为一个特定的值，例如255
                dst.at<uchar>(y, x) = 255;
            }
            else {
                // 如果不在范围内，保留原始像素值
                dst.at<uchar>(y, x) = pixelValue;
            }
        }
    }

    return dst;
}