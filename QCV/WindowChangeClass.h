#pragma once

#include <QWidget>
#include "ui_WindowChangeClass.h"
#include <opencv2/opencv.hpp>
#include "DIPCD_DengLei.h"

class WindowChangeClass : public QWidget
{
	Q_OBJECT

public:
	WindowChangeClass(cv::Mat image,QWidget *parent = nullptr);
	~WindowChangeClass();
//�ۺ�������
public slots:
	//�Ҷȴ��ڱ任
	void windowChange();

	//ȷ����ť
	void enterButton();

	//ȡ����ť
	void cancelButton();

private:
	Ui::WindowChangeClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ
	int L = 64, U = 191;		//������
};
