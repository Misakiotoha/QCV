#pragma once

#include <QMainWindow>
#include "ui_AllUseClass.h"
#include "opencv2/opencv.hpp"
#include "DIPCD_DengLei.h"
#include <stack>

class AllUseClass : public QMainWindow
{
	Q_OBJECT

public:
	AllUseClass(cv::Mat image, QWidget *parent = nullptr);
	~AllUseClass();

	// ���Ͳ���
	cv::Mat dilateImage(const cv::Mat& src, int iterations);

	// ��ʴ����
	cv::Mat erodeImage(const cv::Mat& src, int iterations);

	// �չز���
	cv::Mat closeImage(const cv::Mat& src, int iterations);

	// ��������
	cv::Mat openImage(const cv::Mat& src, int iterations);

	// ��ñ����
	cv::Mat tophatImage(const cv::Mat& src, int iterations);

	// ��ñ����
	cv::Mat blackHatImage(const cv::Mat& src, int iterations);

	// ��ֵ�ָ��
	cv::Mat thresholdImage(const cv::Mat& src, double threshold, double maxVal, int thresholdType = cv::THRESH_BINARY);

	// ������ͨ�������������
	void analyzeConnectedComponents(const cv::Mat& binaryImage, int& objectCount, cv::Rect& boundingBox, double& area, double& perimeter, cv::Point& centroid);


	// ���ζ�
	cv::Mat calculateAndDrawMaxRectangularity(const cv::Mat& inputImage);

	//���Բ
	cv::Mat HoughCircle(const cv::Mat& src, int minRadius, int maxRadius);

	//��������
	cv::Mat countObjectsInImage(const cv::Mat& inputImage);

	//��������ܳ�
	cv::Mat findLargestPerimeter(const cv::Mat& src);

	//���Բ�ζ�
	cv::Mat drawLargestObjectContour(const cv::Mat& inputImage);

	//��������
	cv::Mat calculateAndDrawCenterOfMass(const cv::Mat& inputImage);

	//����������
	cv::Mat findLargestObject(const cv::Mat& src);

//�ۺ���
private slots:
	//����
	void ctrlZ();
	//ȡ��
	void cancelButton();

	//Ԥ����
//ƽ��ȥ��
	void phqz();
	//�Ҷ�����
	void hdls();
	//�ָ�ͼ��
	//OTSU
	void otsu();
	//��̬ѧ����
	//����
	void pz();
	//��ʴ
	void fs();
	//�չ�
	void bg();
	//����
	void kq();
	//��ñ
	void dm();
	//��ñ
	void hm();
	//����
	//Բ��
	void wt();
	//�ܳ�
	void zc();
	//Բ�ζ�
	void yxd();
	//���ζ�
	void jxd();
	//����
	void zx();

	//������
	void zwt();

	//����������
	void maxArea();

private:
	Ui::AllUseClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ
	std::stack<Mat> bak;	//ָ��Mat��ջָ�룬������ɳ�������
};
