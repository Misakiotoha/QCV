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

	// 平移图像
	cv::Mat translateImage(const cv::Mat& srcImage, int xOffset, int yOffset);

	// 旋转图像
	cv::Mat rotateImage(const cv::Mat& src, double angle, double scale=1.0);

	// 缩放图像（等比缩放）
	cv::Mat scaleImage(const cv::Mat& src, double scale);


//槽函数
private slots:
	//平移
	void PY();

	//旋转
	void XZ();

	//缩放
	void SF();

	//确定
	void enterButton();

	//取消
	void cancelButton();

private:
	Ui::TRSClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图
};
