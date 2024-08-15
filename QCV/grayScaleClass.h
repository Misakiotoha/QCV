#pragma once

#include <QWidget>
#include "ui_grayScaleClass.h"
#include <opencv2/opencv.hpp>
#include "DIPCD_DengLei.h"

class grayScaleClass : public QWidget
{
	Q_OBJECT

public:
	grayScaleClass(cv::Mat image ,QWidget *parent = nullptr);
	~grayScaleClass();

//�ۺ���
private slots:
	//�Ҷ�����
	void grayScaleCore();
	//ȷ����ť
	void genterButton();
	//ȡ����ť
	void gcancelButton();

private:
	Ui::grayScaleClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ
	int x1, x2, y1, y2;	//�Ҷ�����ת�۵�
};
