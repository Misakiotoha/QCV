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

//槽函数
private slots:
	//灰度拉伸
	void grayScaleCore();
	//确定按钮
	void genterButton();
	//取消按钮
	void gcancelButton();

private:
	Ui::grayScaleClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图
	int x1, x2, y1, y2;	//灰度拉伸转折点
};
