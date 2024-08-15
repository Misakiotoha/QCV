#pragma once

#include <QWidget>
#include "ui_ThresholdClass.h"
#include <opencv2/opencv.hpp>
#include "DIPCD_DengLei.h"

class ThresholdClass : public QWidget
{
	Q_OBJECT

public:
	ThresholdClass(cv::Mat image,QWidget *parent = nullptr);
	~ThresholdClass();

//�ۺ�������
private slots:

	//��������ֵ�任
	void loopThers(bool checked);

	//OTSU���
	void OTSUThers(bool checked);

	//����Ӧ��ֵ�任
	void selfThers(bool checked);

	//�ֲ�����ط�
	void triangle();

	//ȷ����ť
	void enter_Buton();

	//ȡ����ť
	void cancel_Button();

	//�����ı�ֵ
	void updatethresValue();


private:
	Ui::ThresholdClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ
	int thres = 128;	//Ĭ����ֵ������������и��Ļ����㷨����Ӧ
	int bestThres;		//�����ֵ

private:
	int getEditvalue();
};
