#include <opencv2/opencv.hpp>


// �Ҷȴ��ڱ任����
/**
 * ��ͼ����лҶȴ��ڱ任����ָ���Ҷ����� [L, U] �ڵ�����ֵ��Ϊ255����������ֵ���ֲ��䡣
 *
 * @param src ԭʼ�ĵ�ͨ���Ҷ�ͼ��
 * @param L ���ڱ任��������ֵ��
 * @param U ���ڱ任��������ֵ��
 * @return �任��ĻҶ�ͼ��
 */
cv::Mat grayWindowTransform(const cv::Mat& src, int L, int U) 
{
    // ����һ����Դͼ����ͬ��С�����͵���ͼ��
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());

    // ����ͼ���е�ÿ������
    for (int y = 0; y < src.rows; ++y) {
        for (int x = 0; x < src.cols; ++x) {
            // ��ȡ��ǰ���صĻҶ�ֵ
            uchar pixelValue = src.at<uchar>(y, x);

            // �������ֵ�Ƿ��ڴ��ڵ����޺�����֮��
            if (pixelValue >= L && pixelValue <= U) {
                // ����ڷ�Χ�ڣ�������ֵ����Ϊһ���ض���ֵ������255
                dst.at<uchar>(y, x) = 255;
            }
            else {
                // ������ڷ�Χ�ڣ�����ԭʼ����ֵ
                dst.at<uchar>(y, x) = pixelValue;
            }
        }
    }

    return dst;
}