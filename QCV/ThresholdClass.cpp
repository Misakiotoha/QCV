#include "ThresholdClass.h"
#include "threshold.h"
#include <opencv2/opencv.hpp>
using namespace cv;

ThresholdClass::ThresholdClass(Mat image , QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	//首先进行灰度处理然后显示
	cvtColor(image, gray, COLOR_BGR2GRAY);
	dicp = new DIPCD_DengLei;
	dicp->display_MatInQT(ui.label_showProcessImage, gray);
	ui.thresvaluehorizontalSlider->setRange(0, 255);	//设置滑动范围
	ui.thresvaluehorizontalSlider->setValue(128);		//设置初始滑动值
	ui.valuelineEdit->setText(QString::number(ui.thresvaluehorizontalSlider->value()));	//显示初始值


	//后续都基于灰度图像
	

	//连接槽
	
	//取消按钮
	connect(ui.cancelButton, &QPushButton::clicked, this, &ThresholdClass::cancel_Button);
	
	//迭代法
	connect(ui.loopradioButton, &QRadioButton::clicked, this, &ThresholdClass::loopThers);
	
	//大津法OTSU
	connect(ui.OTSUradioButton, &QRadioButton::clicked, this, &ThresholdClass::OTSUThers);

	//自适应算法
	connect(ui.selfradioButton, &QRadioButton::clicked, this, &ThresholdClass::selfThers);

	//最大熵法(自定义算法)
	connect(ui.triangleradioButton, &QRadioButton::clicked, this, &ThresholdClass::triangle);

	//确定按钮
	connect(ui.enterButton, &QPushButton::clicked, this, &ThresholdClass::enter_Buton);

	//滑动值改变
	connect(ui.thresvaluehorizontalSlider, &QSlider::valueChanged, this, &ThresholdClass::updatethresValue);
}

ThresholdClass::~ThresholdClass()
{
	delete dicp;
	delete &ui;	//及时释放内存
}

//迭代法阈值变换实现
void ThresholdClass::loopThers(bool checked)
{
	if (checked) {	//如果被选中
		thres = getEditvalue();		//获取当前阈值
		bestThres= (int)iterativeThreshold(gray, Res, thres);	//迭代计算出最佳阈值
		ui.valuelineEdit->clear();
		ui.valuelineEdit->setText(QString::number(bestThres));	//显示出最佳阈值
	}
	else {
		return;
	}
}

//OTSU大津法
void ThresholdClass::OTSUThers(bool checked)
{
	if (checked) {	//如果被选中
		//直接计算出最佳阈值然后进行阈值变换
		bestThres = otsuThreshold(gray);	//计算出最佳阈值
		ui.valuelineEdit->clear();
		ui.valuelineEdit->setText(QString::number(bestThres));	//显示最佳阈值
		Res = applyBestThreshold(gray, bestThres);	//更新结果图片
	}
	else {
		return;
	}
}

//自适应阈值变换
void ThresholdClass::selfThers(bool checked)
{
	if (checked) {
		Res = adaptiveThresholdSegmentation(gray); 	//自适应处理出图片
	}
	else {
		return;
	}
}

//最大熵法
void ThresholdClass::triangle()
{
	double thres = maximumEntropyThresholding(gray);
	ui.valuelineEdit->clear();
	ui.valuelineEdit->setText(QString::number(thres));
	Res = applyBestThreshold(gray, thres);
}

//确定按钮，设置阈值展示当前的结果
void ThresholdClass::enter_Buton()
{
	dicp->display_MatInQT(ui.label_showProcessImage,Res);
}


//取消
void ThresholdClass::cancel_Button()
{	
	//关闭所有资源，退出窗口
	this->close();
}

//滑动改变值
void ThresholdClass::updatethresValue()
{
	ui.valuelineEdit->setText(QString::number(
		ui.thresvaluehorizontalSlider->value()
	)
);
}

//得到用户输入的值
int ThresholdClass::getEditvalue()
{
	return ui.valuelineEdit->text().toInt();
}
