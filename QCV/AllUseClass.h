#pragma once

#include <QMainWindow>
#include "ui_AllUseClass.h"
#include "opencv2/opencv.hpp"
#include "DIPCD_DengLei.h"
#include <stack>

class AllUseClass : public QMainWindow
{
	Q_OBJECT

public:
	AllUseClass(cv::Mat image, QWidget *parent = nullptr);
	~AllUseClass();

	// 膨胀操作
	cv::Mat dilateImage(const cv::Mat& src, int iterations);

	// 腐蚀操作
	cv::Mat erodeImage(const cv::Mat& src, int iterations);

	// 闭关操作
	cv::Mat closeImage(const cv::Mat& src, int iterations);

	// 开启操作
	cv::Mat openImage(const cv::Mat& src, int iterations);

	// 顶帽操作
	cv::Mat tophatImage(const cv::Mat& src, int iterations);

	// 黑帽操作
	cv::Mat blackHatImage(const cv::Mat& src, int iterations);

	// 阈值分割函数
	cv::Mat thresholdImage(const cv::Mat& src, double threshold, double maxVal, int thresholdType = cv::THRESH_BINARY);

	// 计算连通区域的轮廓特征
	void analyzeConnectedComponents(const cv::Mat& binaryImage, int& objectCount, cv::Rect& boundingBox, double& area, double& perimeter, cv::Point& centroid);


	// 矩形度
	cv::Mat calculateAndDrawMaxRectangularity(const cv::Mat& inputImage);

	//检测圆
	cv::Mat HoughCircle(const cv::Mat& src, int minRadius, int maxRadius);

	//几个物体
	cv::Mat countObjectsInImage(const cv::Mat& inputImage);

	//最大物体周长
	cv::Mat findLargestPerimeter(const cv::Mat& src);

	//最大圆形度
	cv::Mat drawLargestObjectContour(const cv::Mat& inputImage);

	//重心坐标
	cv::Mat calculateAndDrawCenterOfMass(const cv::Mat& inputImage);

	//最大物体面积
	cv::Mat findLargestObject(const cv::Mat& src);

//槽函数
private slots:
	//撤销
	void ctrlZ();
	//取消
	void cancelButton();

	//预处理
//平滑去噪
	void phqz();
	//灰度拉伸
	void hdls();
	//分割图像
	//OTSU
	void otsu();
	//形态学处理
	//膨胀
	void pz();
	//腐蚀
	void fs();
	//闭关
	void bg();
	//开启
	void kq();
	//顶帽
	void dm();
	//黑帽
	void hm();
	//杂项
	//圆形
	void wt();
	//周长
	void zc();
	//圆形度
	void yxd();
	//矩形度
	void jxd();
	//重心
	void zx();

	//真物体
	void zwt();

	//最大物体面积
	void maxArea();

private:
	Ui::AllUseClassClass ui;
	DIPCD_DengLei* dicp;	//用于调用这里面的方法
	cv::Mat image;	//原图
	cv::Mat gray;	//灰度处理之后的图片
	cv::Mat Res;	//结果图
	std::stack<Mat> bak;	//指向Mat的栈指针，用于完成撤销操作
};
