#include "TRSClass.h"

TRSClass::TRSClass(cv::Mat image, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//方便调用方法
	cvtColor(image, gray, COLOR_BGR2GRAY);	//生成灰度图像
	dicp->display_MatInQT(ui.label_showProcessImage, gray);	//显示灰度原图

    //连接槽

    //平移
    connect(ui.PYradioButton, &QRadioButton::clicked, this, &TRSClass::PY);
    //旋转
    connect(ui.XZradioButton, &QRadioButton::clicked, this, &TRSClass::XZ);
    //缩放
    connect(ui.SFradioButton, &QRadioButton::clicked, this, &TRSClass::SF);

    connect(ui.enterpushButton, &QPushButton::clicked, this, &TRSClass::enterButton);
    connect(ui.cancelpushButton, &QPushButton::clicked, this, &TRSClass::cancelButton);

}

TRSClass::~TRSClass()
{
    delete dicp;
	delete& ui;
}

//平移
void TRSClass::PY()
{
    Res = translateImage(gray,
        ui.XlineEdit->text().toInt(),
        ui.YlineEdit->text().toInt()
    );
}

//旋转
void TRSClass::XZ()
{
    Res = rotateImage(gray, ui.VlineEdit->text().toDouble());
}

//缩放
void TRSClass::SF()
{
    Res = scaleImage(gray, ui.DlineEdit->text().toDouble());
}


//确定按钮
void TRSClass::enterButton()
{
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//取消按钮
void TRSClass::cancelButton()
{
    this->close();
}

/*
下面为底层函数
*/




//平移操作，图像大小不变
cv::Mat TRSClass::translateImage(const cv::Mat& srcImage, int xOffset, int yOffset) 
{
    cv::Mat resultImage;
    cv::Mat translationMatrix = cv::Mat::eye(2, 3, CV_64F); // 创建2x3的单位矩阵作为仿射变换矩阵

    // 设置平移矩阵
    translationMatrix.at<double>(0, 2) = xOffset; // x方向平移
    translationMatrix.at<double>(1, 2) = yOffset; // y方向平移

    // 应用仿射变换
    cv::warpAffine(srcImage, resultImage, translationMatrix, srcImage.size());
    return resultImage;
}
// 旋转变换
cv::Mat TRSClass::rotateImage(const cv::Mat& src, double angle, double scale)
{
    cv::Mat dst;
    // 获取图像尺寸
    cv::Size sz = src.size();
    // 计算旋转中心
    cv::Point2f center(sz.width / 2.0, sz.height / 2.0);

    // 获取旋转矩阵
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, scale);

    // 应用仿射变换（旋转）
    cv::warpAffine(src, dst, rotationMatrix, sz);
    return dst;
}

// 缩放变换
cv::Mat TRSClass::scaleImage(const cv::Mat& src, double scale)
{
    cv::Mat dst;
    cv::Size newSize(cvRound(src.cols * scale), cvRound(src.rows * scale));

    // 使用 INTER_AREA 进行缩小操作
    int interpolationMethod = (scale < 1) ? cv::INTER_AREA : cv::INTER_CUBIC;
    cv::resize(src, dst, newSize, 0, 0, interpolationMethod);
    return dst;
}