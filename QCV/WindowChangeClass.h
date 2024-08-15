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
//槽函数声明
public slots:
	//灰度窗口变换
	void windowChange();

	//确定按钮
	void enterButton();

	//取消按钮
	void cancelButton();

private:
	Ui::WindowChangeClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图
	int L = 64, U = 191;		//上下限
};
