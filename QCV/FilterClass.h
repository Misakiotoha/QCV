#pragma once

#include <QWidget>
#include "ui_FilterClass.h"
#include "DIPCD_DengLei.h"
#include <opencv2/opencv.hpp>


class FilterClass : public QWidget
{
	Q_OBJECT

public:
	FilterClass(cv::Mat image, QWidget *parent = nullptr);
	~FilterClass();

	//Ӧ��3*3���ӵ�ͼ��ĺ���
	cv::Mat applyCustomFilter(const cv::Mat& src, const cv::Mat& filter);

	//ת������
	cv::Mat toFilter();

	// ��ɫ�任
	cv::Mat invertColor(const cv::Mat& src);

	// ƽ��/ģ�� - ��ֵģ��
	static cv::Mat meanBlur(const cv::Mat& src);

	// ��˹ģ��
	cv::Mat gaussianBlur(const cv::Mat& src);

	// �� - ʹ��������˹����
	cv::Mat sharpen(const cv::Mat& src);

	// ��Ե��� - ʹ��Sobel����
	cv::Mat edgeDetection(const cv::Mat& src);

	// ����Ч��
	cv::Mat emboss(const cv::Mat& src);

	// �ı����� - ͨ����ӳ���ֵ
	cv::Mat adjustBrightness(const cv::Mat& src, int value);

	// �ı�Աȶ� - ͨ������ϵ����б�ʣ�
	cv::Mat adjustContrast(const cv::Mat& src, double alpha);

//�ۺ���
private slots:


	//��ɫ
	void invert();

	//��ֵģ��
	void mean();

	//��˹ģ��
	void gauss();

	// �� - ʹ��������˹����
	void sharp();

	// ��Ե��� - ʹ��Sobel����
	void edge();

	// ����Ч��
	void em();

	// �ı����� - ͨ����ӳ���ֵ
	void adjustB();

	// �ı�Աȶ� - ͨ������ϵ����б�ʣ�
	void adjustC();

	//ʹ�ø��������ӽ��д���ͼ��
	void withPic();

	//ȷ����ť
	void enterButton();

	//ȡ����ť
	void cancelButton();

	//Ԥ��ͼ��
	void viewP();

	//�ָ�ͼ��
	void recP();

private:
	Ui::FilterClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ


};
