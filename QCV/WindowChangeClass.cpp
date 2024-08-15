#include "WindowChangeClass.h"
#include "GrayWindowChange.h"


WindowChangeClass::WindowChangeClass(cv::Mat image,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//方便调用方法
	cvtColor(image, gray, COLOR_BGR2GRAY);	//生成灰度图像
	ui.uplineEdit->setText(QString::number(U));
	ui.downlineEdit->setText(QString::number(L));
	dicp->display_MatInQT(ui.label_showProcessImage, gray);
	//连接槽
	connect(ui.enterButton, &QPushButton::clicked, this, &WindowChangeClass::enterButton);
	connect(ui.cancelButton, &QPushButton::clicked, this, &WindowChangeClass::cancelButton);
}

WindowChangeClass::~WindowChangeClass()
{
	delete dicp;
	delete &ui;
}

//窗口上下限变化
void WindowChangeClass::windowChange()
{
	//从用户输入的值来获取上下限
	L = ui.downlineEdit->text().toInt();
	U = ui.uplineEdit->text().toInt();
	Res = grayWindowTransform(gray, L, U);
}

//确认按钮
void WindowChangeClass::enterButton()
{
	windowChange();
	dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//取消按钮
void WindowChangeClass::cancelButton()
{
	this->close();
}