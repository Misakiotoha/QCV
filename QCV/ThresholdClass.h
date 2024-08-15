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

//槽函数声明
private slots:

	//迭代法阈值变换
	void loopThers(bool checked);

	//OTSU大津法
	void OTSUThers(bool checked);

	//自适应阈值变换
	void selfThers(bool checked);

	//局部最大熵法
	void triangle();

	//确定按钮
	void enter_Buton();

	//取消按钮
	void cancel_Button();

	//滑动改变值
	void updatethresValue();


private:
	Ui::ThresholdClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图
	int thres = 128;	//默认阈值，根据输入进行更改或者算法自适应
	int bestThres;		//最佳阈值

private:
	int getEditvalue();
};
