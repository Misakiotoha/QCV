//�Ҷ�����

#include "grayScaleClass.h"
#include "grayScaleStretching.h"

grayScaleClass::grayScaleClass(cv::Mat image, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//������÷���
	cvtColor(image, gray, COLOR_BGR2GRAY);	//���ɻҶ�ͼ��
	dicp->display_MatInQT(ui.label_showProcessImage, gray);	//��ʾ�Ҷ�ԭͼ

	//���Ӳ�
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

//ȷ����ť����ʾ���
void grayScaleClass::genterButton()
{
	grayScaleCore();
	dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//ȡ����ť
void grayScaleClass::gcancelButton()
{
	this->close();
}