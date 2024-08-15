#include "WindowChangeClass.h"
#include "GrayWindowChange.h"


WindowChangeClass::WindowChangeClass(cv::Mat image,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//������÷���
	cvtColor(image, gray, COLOR_BGR2GRAY);	//���ɻҶ�ͼ��
	ui.uplineEdit->setText(QString::number(U));
	ui.downlineEdit->setText(QString::number(L));
	dicp->display_MatInQT(ui.label_showProcessImage, gray);
	//���Ӳ�
	connect(ui.enterButton, &QPushButton::clicked, this, &WindowChangeClass::enterButton);
	connect(ui.cancelButton, &QPushButton::clicked, this, &WindowChangeClass::cancelButton);
}

WindowChangeClass::~WindowChangeClass()
{
	delete dicp;
	delete &ui;
}

//���������ޱ仯
void WindowChangeClass::windowChange()
{
	//���û������ֵ����ȡ������
	L = ui.downlineEdit->text().toInt();
	U = ui.uplineEdit->text().toInt();
	Res = grayWindowTransform(gray, L, U);
}

//ȷ�ϰ�ť
void WindowChangeClass::enterButton()
{
	windowChange();
	dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//ȡ����ť
void WindowChangeClass::cancelButton()
{
	this->close();
}