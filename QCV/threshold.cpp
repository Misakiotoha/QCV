/*
实现灰度阈值变换的三个算法
1.迭代法阈值变换 iterativeThreshold
2.OTSU方法 otsuThreshold
3.自适应阈值分割 adaptiveThreshold
*/

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

/*
 迭代法阈值变换 iterativeThreshold
参数:

src: 输入图像，需要是灰度图像（单通道）。
dst: 输出图像，用于存储二值化结果。
initialThresh: 初始阈值估计，迭代过程从这个值开始。
threshDelta: 阈值变化的精度，当连续迭代的阈值变化小于这个值时停止迭代。
返回值: double，也就是迭代出的最佳阈值，函数直接修改dst图像。
*/
double iterativeThreshold(cv::Mat& src, cv::Mat& dst, double initialThresh, double threshDelta) 
{
    cv::Mat mask;
    double T = initialThresh;
    double Tprev = 0.0;
    cv::threshold(src, dst, T, 255, cv::THRESH_BINARY);

    while (true) {
        cv::threshold(src, mask, T, 255, cv::THRESH_BINARY);
        double u1 = cv::mean(src, mask)[0];
        double u2 = cv::mean(src, ~mask)[0];
        T = (u1 + u2) / 2.0;

        if (std::abs(T - Tprev) < threshDelta) {
            break;
        }

        Tprev = T;
        cv::threshold(src, dst, T, 255, cv::THRESH_BINARY);
    }
    return T;
}


/*
OTSU方法 otsuThreshold
参数:

grayImage: 输入的灰度图像。
返回值:

返回计算得到的最优阈值。
*/
double otsuThreshold(const cv::Mat& grayImage) 
{
    int histSize = 256;
    int hist_w = histSize;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    cv::Mat hist;
    // Calculate histogram
    cv::calcHist(&grayImage, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    // Apply OTSU's method
    double total = grayImage.total();
    double maxVar = 0;
    double bestThresh = 0;
    double sumB = 0;
    double sumF = 0;
    double wB = 0, wF = 0;
    double mB = 0, mF = 0;

    for (int i = 0; i < histSize; i++) {
        sumB += i * hist.at<float>(i);
        wB += hist.at<float>(i);
        if (wB == 0) continue;

        mB = sumB / wB;
        sumF += (i * (histSize - i)) * hist.at<float>(i);
        wF += hist.at<float>(i);
        if (wF == 0) continue;

        mF = sumF / wF;
        double varBetween = wB * wF * (mB - mF) * (mB - mF);
        double varRatio = varBetween / (wB + wF);

        if (varRatio > maxVar) {
            maxVar = varRatio;
            bestThresh = i;
        }
    }

    return bestThresh;
}


/*
自适应阈值分割 adaptiveThresholdSegmentation
*/

Mat adaptiveThresholdSegmentation(const cv::Mat& inputImage)
{
    // 确保输入图像是灰度图像
    cv::Mat grayImage;
    if (inputImage.channels() > 1)
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    else
        grayImage = inputImage;

    // 定义自适应阈值参数
    int blockSize = 11;   // 邻域大小
    int C = 2;            // 常数从平均值中减去

    // 应用自适应阈值
    cv::Mat binaryImage;
    cv::adaptiveThreshold(grayImage, binaryImage, 255,
        cv::ADAPTIVE_THRESH_GAUSSIAN_C,
        cv::THRESH_BINARY, blockSize, C);

    return binaryImage;
}


cv::Mat applyBestThreshold(const cv::Mat& src, double bestThreshold)
{
    // 创建一个输出图像，与输入图像具有相同的大小和类型
    cv::Mat dst;

    // 使用最佳阈值进行二值化处理
    // 第二个参数是最大值，当像素值大于阈值时，会被设置为这个值
    // 在二值化中，通常这个值是255
    cv::threshold(src, dst, bestThreshold, 255, cv::THRESH_BINARY);
    
    // 返回处理后的图像
    return dst;
}


//最大熵法
/*
计算图像直方图。
根据直方图计算前景和背景的概率分布。
计算前景和背景的信息熵。
遍历所有可能的阈值，找到最大化信息熵的阈值。
*/
double maximumEntropyThresholding(const cv::Mat& grayImage) 
{
    // 1. 计算直方图
    int histSize = 256;
    cv::Mat hist;
    cv::calcHist(&grayImage, 1, 0, cv::Mat(), hist, 1, &histSize, 0);

    // 2. 归一化直方图，得到概率分布
    double scale = 1.0 / grayImage.total();
    hist.convertTo(hist, CV_32F, scale);

    // 3. 初始化信息熵和最佳阈值
    double maxEntropy = 0.0;
    double threshold = 0.0;
    double sumB = 0.0, sumF = 0.0; // 背景和前景的累加概率

    for (int t = 1; t < histSize; t++) {
        sumB += hist.at<float>(t - 1);
        sumF = 1.0 - sumB;

        // 计算信息熵
        double entropy = -(sumB * log(sumB) + sumF * log(sumF));

        // 更新最大信息熵和最佳阈值
        if (entropy > maxEntropy) {
            maxEntropy = entropy;
            threshold = t - 0.5; // 阈值在两个灰度级之间
        }
    }

    return threshold;
}