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

	// �ͻ�Ч��
	cv::Mat oilPaintingEffect(const cv::Mat& src);

	// Ǧ�ʻ�Ч��
	cv::Mat pencilSketch(const cv::Mat& src);

	// ��ͨЧ��
	cv::Mat cartoonEffect(const cv::Mat& src);


//�ۺ���
private slots:
	// �ͻ�Ч��ѡ��
	void YH();

	// Ǧ�ʻ�Ч��ѡ��
	void QB();

	// ��ͨЧ��ѡ��
	void KT();

	//ȷ����ť
	void enterButton();

	//ȡ����ť
	void cancelButton();


private:
	Ui::CuteClassClass ui;
	DIPCD_DengLei* dicp;	//���ڵ���������ķ���
	cv::Mat image;	//ԭͼ
	cv::Mat gray;	//�Ҷȴ���֮���ͼƬ
	cv::Mat Res;	//���ͼ

};
