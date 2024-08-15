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

	//底层处理函数
	static cv::Mat histogramEqualization(const cv::Mat& src);
//槽函数
private slots:
	//直方图均衡化
	void histogramButton();

	//退出按钮
	void exitButton();

private:
	Ui::histogramClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图
};
