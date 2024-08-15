#pragma once

#include <QWidget>
#include "ui_TRSClass.h"
#include <opencv2/opencv.hpp>
#include "DIPCD_DengLei.h"



class TRSClass : public QWidget
{
	Q_OBJECT

public:
	TRSClass(cv::Mat image,QWidget *parent = nullptr);
	~TRSClass();

	// ƽ��ͼ��
	cv::Mat translateImage(const cv::Mat& srcImage, int xOffset, int yOffset);

	// ��תͼ��
	cv::Mat rotateImage(const cv::Mat& src, double angle, double scale=1.0);

	// ����ͼ�񣨵ȱ����ţ�
	cv::Mat scaleImage(const cv::Mat& src, double scale);


//�ۺ���
private slots:
	//ƽ��
	void PY();

	//��ת
	void XZ();

	//����
	void SF();

	//ȷ��
	void enterButton();

	//ȡ��
	void cancelButton();

private:
	Ui::TRSClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ
};
