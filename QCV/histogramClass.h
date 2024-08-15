#pragma once

#include <QWidget>
#include "ui_histogramClass.h"
#include <opencv2/opencv.hpp>
#include "DIPCD_DengLei.h"

class histogramClass : public QWidget
{
	Q_OBJECT

public:
	histogramClass(cv::Mat image, QWidget *parent = nullptr);
	~histogramClass();

	//�ײ㴦����
	static cv::Mat histogramEqualization(const cv::Mat& src);
//�ۺ���
private slots:
	//ֱ��ͼ���⻯
	void histogramButton();

	//�˳���ť
	void exitButton();

private:
	Ui::histogramClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ
};
