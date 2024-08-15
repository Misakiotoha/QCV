#include "histogramClass.h"
using namespace cv;

histogramClass::histogramClass(cv::Mat image , QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//������÷���
	cvtColor(image, gray, COLOR_BGR2GRAY);	//���ɻҶ�ͼ��
    dicp->display_MatInQT(ui.label_showOriginalImage, gray);    //��ʾ�Ҷ�ͼ��

    //���Ӳ�
    connect(ui.exitpushButton, &QPushButton::clicked, this, &histogramClass::exitButton);
    connect(ui.histpushButton, &QPushButton::clicked, this, &histogramClass::histogramButton);
}

histogramClass::~histogramClass()
{
	delete dicp;
	delete& ui;
}

/**
 * ������ĻҶ�ͼ�����ֱ��ͼ���⻯����
 *
 * @param src ����ĻҶ�ͼ�񣬱����ǵ�ͨ��ͼ��
 * @return dst ����ֱ��ͼ���⻯���ͼ��������ͼ�������ͬ�Ĵ�С�����͡�
 */
cv::Mat histogramClass::histogramEqualization(const cv::Mat& src)
{
    /*if (src.channels() != 1) {
        throw std::runtime_error("Source image must be a grayscale image.");
    }*/
    // ����һ����Դͼ����ͬ��С�����͵���ͼ�����ڴ�Ž��
    cv::Mat dst;
    // ʹ��OpenCV��equalizeHist��������ֱ��ͼ���⻯
    cv::equalizeHist(src, dst);
    return dst;
}


//ֱ��ͼ���⻯
void histogramClass::histogramButton()
{
    Res = histogramEqualization(gray);
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}


//�˳���ť
void histogramClass::exitButton()
{
    this->close();
}