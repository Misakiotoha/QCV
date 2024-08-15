//灰度拉伸

#include "grayScaleClass.h"
#include "grayScaleStretching.h"

grayScaleClass::grayScaleClass(cv::Mat image, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//方便调用方法
	cvtColor(image, gray, COLOR_BGR2GRAY);	//生成灰度图像
	dicp->display_MatInQT(ui.label_showProcessImage, gray);	//显示灰度原图

	//连接槽
	connect(ui.cancelpushButton, &QPushButton::clicked, this, &grayScaleClass::gcancelButton);
	connect(ui.enterpushButton, &QPushButton::clicked, this, &grayScaleClass::genterButton);


}

grayScaleClass::~grayScaleClass()
{
	delete dicp;
	delete& ui;
}

void grayScaleClass::grayScaleCore()
{
	x1 = ui.oneXlineEdit->text().toInt();
	x2 = ui.twoXlineEdit->text().toInt();
	y1 = ui.oneYlineEdit->text().toInt();
	y2 = ui.twoYlineEdit->text().toInt();
	Res = grayScaleStretching(gray, x1, y1, x2, y2);
}

//确定按钮，显示结果
void grayScaleClass::genterButton()
{
	grayScaleCore();
	dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//取消按钮
void grayScaleClass::gcancelButton()
{
	this->close();
}