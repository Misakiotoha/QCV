#pragma once

#include <QWidget>
#include "ui_CuteClass.h"
#include <opencv2/opencv.hpp>
#include "DIPCD_DengLei.h"

class CuteClass : public QWidget
{
	Q_OBJECT

public:
	CuteClass(cv::Mat image, QWidget* parent = nullptr);
	~CuteClass();

	// 油画效果
	cv::Mat oilPaintingEffect(const cv::Mat& src);

	// 铅笔画效果
	cv::Mat pencilSketch(const cv::Mat& src);

	// 卡通效果
	cv::Mat cartoonEffect(const cv::Mat& src);


//槽函数
private slots:
	// 油画效果选项
	void YH();

	// 铅笔画效果选项
	void QB();

	// 卡通效果选项
	void KT();

	//确定按钮
	void enterButton();

	//取消按钮
	void cancelButton();


private:
	Ui::CuteClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图

};
