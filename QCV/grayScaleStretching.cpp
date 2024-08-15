
//�Ҷ�����

#include <opencv2/opencv.hpp>

/**
 * ������ĻҶ�ͼ��Ӧ�ûҶ�����任��
 *
 * @param src ����ĻҶ�ͼ�񣬱����ǵ�ͨ��ͼ��
 * @param x1 ��һ��ת�۵�ĻҶ�ֵ����ֵ���µ����ؽ���ӳ�䵽y1��
 * @param y1 ��һ��ת�۵��ӳ��ֵ��x1���µ����ؽ������쵽���ֵ��
 * @param x2 �ڶ���ת�۵�ĻҶ�ֵ����ֵ���ϵ����ؽ���ӳ�䵽y2��
 * @param y2 �ڶ���ת�۵��ӳ��ֵ��x2���ϵ����ؽ������쵽���ֵ��
 * @return dst �����Ҷ�����任���ͼ��������ͼ�������ͬ�Ĵ�С�����͡�
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