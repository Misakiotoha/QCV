#include "ThresholdClass.h"
#include "threshold.h"
#include <opencv2/opencv.hpp>
using namespace cv;

ThresholdClass::ThresholdClass(Mat image , QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	//���Ƚ��лҶȴ���Ȼ����ʾ
	cvtColor(image, gray, COLOR_BGR2GRAY);
	dicp = new DIPCD_DengLei;
	dicp->display_MatInQT(ui.label_showProcessImage, gray);
	ui.thresvaluehorizontalSlider->setRange(0, 255);	//���û�����Χ
	ui.thresvaluehorizontalSlider->setValue(128);		//���ó�ʼ����ֵ
	ui.valuelineEdit->setText(QString::number(ui.thresvaluehorizontalSlider->value()));	//��ʾ��ʼֵ


	//���������ڻҶ�ͼ��
	

	//���Ӳ�
	
	//ȡ����ť
	connect(ui.cancelButton, &QPushButton::clicked, this, &ThresholdClass::cancel_Button);
	
	//������
	connect(ui.loopradioButton, &QRadioButton::clicked, this, &ThresholdClass::loopThers);
	
	//���OTSU
	connect(ui.OTSUradioButton, &QRadioButton::clicked, this, &ThresholdClass::OTSUThers);

	//����Ӧ�㷨
	connect(ui.selfradioButton, &QRadioButton::clicked, this, &ThresholdClass::selfThers);

	//����ط�(�Զ����㷨)
	connect(ui.triangleradioButton, &QRadioButton::clicked, this, &ThresholdClass::triangle);

	//ȷ����ť
	connect(ui.enterButton, &QPushButton::clicked, this, &ThresholdClass::enter_Buton);

	//����ֵ�ı�
	connect(ui.thresvaluehorizontalSlider, &QSlider::valueChanged, this, &ThresholdClass::updatethresValue);
}

ThresholdClass::~ThresholdClass()
{
	delete dicp;
	delete &ui;	//��ʱ�ͷ��ڴ�
}

//��������ֵ�任ʵ��
void ThresholdClass::loopThers(bool checked)
{
	if (checked) {	//�����ѡ��
		thres = getEditvalue();		//��ȡ��ǰ��ֵ
		bestThres= (int)iterativeThreshold(gray, Res, thres);	//��������������ֵ
		ui.valuelineEdit->clear();
		ui.valuelineEdit->setText(QString::number(bestThres));	//��ʾ�������ֵ
	}
	else {
		return;
	}
}

//OTSU���
void ThresholdClass::OTSUThers(bool checked)
{
	if (checked) {	//�����ѡ��
		//ֱ�Ӽ���������ֵȻ�������ֵ�任
		bestThres = otsuThreshold(gray);	//����������ֵ
		ui.valuelineEdit->clear();
		ui.valuelineEdit->setText(QString::number(bestThres));	//��ʾ�����ֵ
		Res = applyBestThreshold(gray, bestThres);	//���½��ͼƬ
	}
	else {
		return;
	}
}

//����Ӧ��ֵ�任
void ThresholdClass::selfThers(bool checked)
{
	if (checked) {
		Res = adaptiveThresholdSegmentation(gray); 	//����Ӧ�����ͼƬ
	}
	else {
		return;
	}
}

//����ط�
void ThresholdClass::triangle()
{
	double thres = maximumEntropyThresholding(gray);
	ui.valuelineEdit->clear();
	ui.valuelineEdit->setText(QString::number(thres));
	Res = applyBestThreshold(gray, thres);
}

//ȷ����ť��������ֵչʾ��ǰ�Ľ��
void ThresholdClass::enter_Buton()
{
	dicp->display_MatInQT(ui.label_showProcessImage,Res);
}


//ȡ��
void ThresholdClass::cancel_Button()
{	
	//�ر�������Դ���˳�����
	this->close();
}

//�����ı�ֵ
void ThresholdClass::updatethresValue()
{
	ui.valuelineEdit->setText(QString::number(
		ui.thresvaluehorizontalSlider->value()
	)
);
}

//�õ��û������ֵ
int ThresholdClass::getEditvalue()
{
	return ui.valuelineEdit->text().toInt();
}
