/*
ʵ�ֻҶ���ֵ�任�������㷨
1.��������ֵ�任 iterativeThreshold
2.OTSU���� otsuThreshold
3.����Ӧ��ֵ�ָ� adaptiveThreshold
*/

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

/*
 ��������ֵ�任 iterativeThreshold
����:

src: ����ͼ����Ҫ�ǻҶ�ͼ�񣨵�ͨ������
dst: ���ͼ�����ڴ洢��ֵ�������
initialThresh: ��ʼ��ֵ���ƣ��������̴����ֵ��ʼ��
threshDelta: ��ֵ�仯�ľ��ȣ���������������ֵ�仯С�����ֵʱֹͣ������
����ֵ: double��Ҳ���ǵ������������ֵ������ֱ���޸�dstͼ��
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
OTSU���� otsuThreshold
����:

grayImage: ����ĻҶ�ͼ��
����ֵ:

���ؼ���õ���������ֵ��
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
����Ӧ��ֵ�ָ� adaptiveThresholdSegmentation
*/

Mat adaptiveThresholdSegmentation(const cv::Mat& inputImage)
{
    // ȷ������ͼ���ǻҶ�ͼ��
    cv::Mat grayImage;
    if (inputImage.channels() > 1)
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    else
        grayImage = inputImage;

    // ��������Ӧ��ֵ����
    int blockSize = 11;   // �����С
    int C = 2;            // ������ƽ��ֵ�м�ȥ

    // Ӧ������Ӧ��ֵ
    cv::Mat binaryImage;
    cv::adaptiveThreshold(grayImage, binaryImage, 255,
        cv::ADAPTIVE_THRESH_GAUSSIAN_C,
        cv::THRESH_BINARY, blockSize, C);

    return binaryImage;
}


cv::Mat applyBestThreshold(const cv::Mat& src, double bestThreshold)
{
    // ����һ�����ͼ��������ͼ�������ͬ�Ĵ�С������
    cv::Mat dst;

    // ʹ�������ֵ���ж�ֵ������
    // �ڶ������������ֵ��������ֵ������ֵʱ���ᱻ����Ϊ���ֵ
    // �ڶ�ֵ���У�ͨ�����ֵ��255
    cv::threshold(src, dst, bestThreshold, 255, cv::THRESH_BINARY);
    
    // ���ش�����ͼ��
    return dst;
}


//����ط�
/*
����ͼ��ֱ��ͼ��
����ֱ��ͼ����ǰ���ͱ����ĸ��ʷֲ���
����ǰ���ͱ�������Ϣ�ء�
�������п��ܵ���ֵ���ҵ������Ϣ�ص���ֵ��
*/
double maximumEntropyThresholding(const cv::Mat& grayImage) 
{
    // 1. ����ֱ��ͼ
    int histSize = 256;
    cv::Mat hist;
    cv::calcHist(&grayImage, 1, 0, cv::Mat(), hist, 1, &histSize, 0);

    // 2. ��һ��ֱ��ͼ���õ����ʷֲ�
    double scale = 1.0 / grayImage.total();
    hist.convertTo(hist, CV_32F, scale);

    // 3. ��ʼ����Ϣ�غ������ֵ
    double maxEntropy = 0.0;
    double threshold = 0.0;
    double sumB = 0.0, sumF = 0.0; // ������ǰ�����ۼӸ���

    for (int t = 1; t < histSize; t++) {
        sumB += hist.at<float>(t - 1);
        sumF = 1.0 - sumB;

        // ������Ϣ��
        double entropy = -(sumB * log(sumB) + sumF * log(sumF));

        // ���������Ϣ�غ������ֵ
        if (entropy > maxEntropy) {
            maxEntropy = entropy;
            threshold = t - 0.5; // ��ֵ�������Ҷȼ�֮��
        }
    }

    return threshold;
}