#include "histogramClass.h"
using namespace cv;

histogramClass::histogramClass(cv::Mat image , QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//方便调用方法
	cvtColor(image, gray, COLOR_BGR2GRAY);	//生成灰度图像
    dicp->display_MatInQT(ui.label_showOriginalImage, gray);    //显示灰度图像

    //连接槽
    connect(ui.exitpushButton, &QPushButton::clicked, this, &histogramClass::exitButton);
    connect(ui.histpushButton, &QPushButton::clicked, this, &histogramClass::histogramButton);
}

histogramClass::~histogramClass()
{
	delete dicp;
	delete& ui;
}

/**
 * 对输入的灰度图像进行直方图均衡化处理。
 *
 * @param src 输入的灰度图像，必须是单通道图像。
 * @return dst 经过直方图均衡化后的图像，与输入图像具有相同的大小和类型。
 */
cv::Mat histogramClass::histogramEqualization(const cv::Mat& src)
{
    /*if (src.channels() != 1) {
        throw std::runtime_error("Source image must be a grayscale image.");
    }*/
    // 创建一个与源图像相同大小和类型的新图像用于存放结果
    cv::Mat dst;
    // 使用OpenCV的equalizeHist函数进行直方图均衡化
    cv::equalizeHist(src, dst);
    return dst;
}


//直方图均衡化
void histogramClass::histogramButton()
{
    Res = histogramEqualization(gray);
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}


//退出按钮
void histogramClass::exitButton()
{
    this->close();
}