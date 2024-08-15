#pragma once

#include <QWidget>
#include "ui_FilterClass.h"
#include "DIPCD_DengLei.h"
#include <opencv2/opencv.hpp>


class FilterClass : public QWidget
{
	Q_OBJECT

public:
	FilterClass(cv::Mat image, QWidget *parent = nullptr);
	~FilterClass();

	//应用3*3算子到图像的函数
	cv::Mat applyCustomFilter(const cv::Mat& src, const cv::Mat& filter);

	//转化算子
	cv::Mat toFilter();

	// 反色变换
	cv::Mat invertColor(const cv::Mat& src);

	// 平滑/模糊 - 均值模糊
	static cv::Mat meanBlur(const cv::Mat& src);

	// 高斯模糊
	cv::Mat gaussianBlur(const cv::Mat& src);

	// 锐化 - 使用拉普拉斯算子
	cv::Mat sharpen(const cv::Mat& src);

	// 边缘检测 - 使用Sobel算子
	cv::Mat edgeDetection(const cv::Mat& src);

	// 浮雕效果
	cv::Mat emboss(const cv::Mat& src);

	// 改变亮度 - 通过添加常数值
	cv::Mat adjustBrightness(const cv::Mat& src, int value);

	// 改变对比度 - 通过调整系数（斜率）
	cv::Mat adjustContrast(const cv::Mat& src, double alpha);

//槽函数
private slots:


	//反色
	void invert();

	//均值模糊
	void mean();

	//高斯模糊
	void gauss();

	// 锐化 - 使用拉普拉斯算子
	void sharp();

	// 边缘检测 - 使用Sobel算子
	void edge();

	// 浮雕效果
	void em();

	// 改变亮度 - 通过添加常数值
	void adjustB();

	// 改变对比度 - 通过调整系数（斜率）
	void adjustC();

	//使用给出的算子进行处理图像
	void withPic();

	//确定按钮
	void enterButton();

	//取消按钮
	void cancelButton();

	//预览图像
	void viewP();

	//恢复图像
	void recP();

private:
	Ui::FilterClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图


};
