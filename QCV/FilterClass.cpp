#include "FilterClass.h"

FilterClass::FilterClass(cv::Mat image, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->image = image;
	dicp = new DIPCD_DengLei;	//方便调用方法
	cvtColor(image, gray, COLOR_BGR2GRAY);	//生成灰度图像
	dicp->display_MatInQT(ui.label_showProcessImage, gray);	//显示灰度原图

    //连接槽

    //反色变换
    connect(ui.radioButton_1, &QRadioButton::clicked, this, &FilterClass::invert);
    //均值
    connect(ui.radioButton_2, &QRadioButton::clicked, this, &FilterClass::mean);
    //高斯
    connect(ui.radioButton_3, &QRadioButton::clicked, this, &FilterClass::gauss);
    //锐化
    connect(ui.radioButton_4, &QRadioButton::clicked, this, &FilterClass::sharp);
    //浮雕
    connect(ui.radioButton_5, &QRadioButton::clicked, this, &FilterClass::em);
    //Sobel算子
    connect(ui.radioButton_6, &QRadioButton::clicked, this, &FilterClass::edge);
    //改变亮度
    connect(ui.radioButton_7, &QRadioButton::clicked, this, &FilterClass::adjustB);
    //改变对比度
    connect(ui.radioButton_8, &QRadioButton::clicked, this, &FilterClass::adjustC);

    //预览图像
    connect(ui.viewpushButton, &QPushButton::clicked, this, &FilterClass::viewP);
    //恢复图像
    connect(ui.recpushButton, &QPushButton::clicked, this, &FilterClass::recP);

    //装载算子
    connect(ui.usepushButton, &QPushButton::clicked, this, &FilterClass::withPic);

    //确定
    connect(ui.enterpushButton, &QPushButton::clicked, this, &FilterClass::enterButton);

    //取消
    connect(ui.cancelpushButton, &QPushButton::clicked, this, &FilterClass::cancelButton);
}

FilterClass::~FilterClass()
{
	delete dicp;
	delete& ui;
}


//确定按钮
void FilterClass::enterButton()
{
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//取消按钮
void FilterClass::cancelButton()
{
	this->close();
}

//预览图像
void FilterClass::viewP()
{
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//恢复图像
void FilterClass::recP()
{
    dicp->display_MatInQT(ui.label_showProcessImage, gray);
}

//反色
void FilterClass::invert()
{
    Res = invertColor(gray);
}

//均值模糊
void FilterClass::mean()
{
    Res = meanBlur(gray);
}

//高斯模糊
void FilterClass::gauss()
{
    Res = gaussianBlur(gray);
}

// 锐化 - 使用拉普拉斯算子
void FilterClass::sharp()
{
    Res = sharpen(gray);
}

// 边缘检测 - 使用Sobel算子
void FilterClass::edge()
{
    Res = edgeDetection(gray);
}

// 浮雕效果
void FilterClass::em()
{
    Res = emboss(gray);
}

// 改变亮度 - 通过添加常数值
void FilterClass::adjustB()
{
    int value = ui.valuelineEdit->text().toInt();
    Res = adjustBrightness(gray,value);
}

// 改变对比度 - 通过调整系数（斜率）
void FilterClass::adjustC()
{
    int k = ui.definelineEdit->text().toInt();
    Res = adjustContrast(gray, k);
}

//使用给出的算子进行处理图像
void FilterClass::withPic()
{
    Res = applyCustomFilter(gray, toFilter());
}



/*
以下是底层，只被别的调用
*/

// 应用3x3算子到图像的函数
cv::Mat FilterClass::applyCustomFilter(const cv::Mat& src, const cv::Mat& filter)
{
    // 确保输入图像是单通道灰度图
    if (src.channels() != 1) {
        throw std::runtime_error("Source image must be a single-channel grayscale image.");
    }

    // 确保算子是3x3大小
    if (filter.rows != 3 || filter.cols != 3) {
        throw std::runtime_error("Filter must be a 3x3 matrix.");
    }

    // 创建输出图像，与输入图像具有相同的大小和类型
    cv::Mat dst;

    // 应用算子
    cv::filter2D(src, dst, -1, filter, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    return dst;
}

//用户输入的转化成3*3Mat算子
cv::Mat FilterClass::toFilter()
{
    // 定义一个3x3算子
    cv::Mat filter = (cv::Mat_<double>(3, 3) <<
        ui.lineEdit_1->text().toInt(), 
        ui.lineEdit_2->text().toInt(),
        ui.lineEdit_3->text().toInt(),
        ui.lineEdit_4->text().toInt(),
        ui.lineEdit_5->text().toInt(),
        ui.lineEdit_6->text().toInt(),
        ui.lineEdit_7->text().toInt(),
        ui.lineEdit_8->text().toInt(),
        ui.lineEdit_9->text().toInt()
        );
    return filter;
}


// 反色变换
cv::Mat FilterClass::invertColor(const cv::Mat& src)
{
    cv::Mat dst;
    cv::bitwise_not(src, dst);
    return dst;
}

// 平滑/模糊 - 均值模糊
cv::Mat FilterClass::meanBlur(const cv::Mat& src)
{
    cv::Mat dst;
    cv::blur(src, dst, cv::Size(3, 3)); // 3x3均值滤波器
    return dst;
}

// 高斯模糊
cv::Mat FilterClass::gaussianBlur(const cv::Mat& src)
{
    cv::Mat dst;
    cv::GaussianBlur(src, dst, cv::Size(5, 5), 0); // 5x5高斯滤波器
    return dst;
}


// 锐化 - 使用拉普拉斯算子
cv::Mat FilterClass::sharpen(const cv::Mat& src)
{
    cv::Mat dst, kernel;
    int kernelSize = 3;
    double ddepth = -1;

    // 拉普拉斯算子
    kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    cv::filter2D(src, dst, ddepth, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    return dst;
}

// 边缘检测 - 使用Sobel算子
cv::Mat FilterClass::edgeDetection(const cv::Mat& src)
{
    cv::Mat dst, grad_x, grad_y;
    int sobelSize = 3;
    double scale = 1;
    double delta = 0;
    int ddepth = CV_16S;

    // 计算水平和垂直梯度
    cv::Sobel(src, grad_x, ddepth, 1, 0, sobelSize, scale, delta, cv::BORDER_DEFAULT);
    cv::Sobel(src, grad_y, ddepth, 0, 1, sobelSize, scale, delta, cv::BORDER_DEFAULT);

    // 计算梯度幅度
    cv::Mat abs_grad_x;
    cv::convertScaleAbs(grad_x, abs_grad_x);

    cv::Mat abs_grad_y;
    cv::convertScaleAbs(grad_y, abs_grad_y);

    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

    return dst;
}

// 浮雕效果
cv::Mat FilterClass::emboss(const cv::Mat& src)
{
    cv::Mat dst;
    // 设置卷积核
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);
    // 确保输出图像的深度与输入图像一致
    cv::filter2D(src, dst, src.depth(), kernel, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
    return dst;
}



// 改变亮度 - 通过添加常数值
cv::Mat FilterClass::adjustBrightness(const cv::Mat& src, int value)
{
    cv::Mat dst;
    cv::add(src, value, dst);
    return dst;
}

// 改变对比度 - 通过调整系数（斜率）(0,3)
cv::Mat FilterClass::adjustContrast(const cv::Mat& src, double alpha)
{
    cv::Mat dst;
    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;

    for (int i = 0; i < 256; i++) {
        p[i] = saturate_cast<uchar>(i * alpha);
    }

    cv::LUT(src, lookUpTable, dst);
    return dst;
}