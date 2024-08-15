#include "CuteClass.h"

CuteClass::CuteClass(cv::Mat image,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    this->image = image;
    dicp = new DIPCD_DengLei();
    dicp->display_MatInQT(ui.label_showProcessImage, this->image);
    //连接槽
    //取消
    connect(ui.cancelpushButton, &QPushButton::clicked, this, &CuteClass::cancelButton);
    //确定
    connect(ui.enterpushButton, &QPushButton::clicked, this, &CuteClass::enterButton);

    connect(ui.YHradioButton, &QRadioButton::clicked, this, &CuteClass::YH);

    connect(ui.QBradioButton, &QRadioButton::clicked, this, &CuteClass::QB);
    
    connect(ui.KTradioButton, &QRadioButton::clicked, this, &CuteClass::KT);

}

CuteClass::~CuteClass()
{
    delete dicp;
	delete& ui;
}

// 油画效果选项
void CuteClass::YH()
{
    Res = oilPaintingEffect(image);
}

// 铅笔画效果选项
void CuteClass::QB()
{
    Res = pencilSketch(image);
}

// 卡通效果选项
void CuteClass::KT()
{
    Res = cartoonEffect(image);
}

//确定按钮
void CuteClass::enterButton()
{
    dicp->display_MatInQT(ui.label_showProcessImage,Res);
}

//取消按钮
void CuteClass::cancelButton()
{
    this->close();
}



// 油画效果
cv::Mat CuteClass::oilPaintingEffect(const cv::Mat& src)
{
    cv::Mat edge, color, dst;
    // 使用Canny算子检测边缘
    cv::Canny(src, edge, 100, 200);
    // 高斯模糊，模拟油画的笔触
    cv::GaussianBlur(src, color, cv::Size(5, 5), 0);
    // 将边缘与模糊的图像合并
    cv::bitwise_and(color, color, dst, edge);
    return dst;
}

// 铅笔画效果
cv::Mat CuteClass::pencilSketch(const cv::Mat& src)
{
    cv::Mat gray, edge, sketch;
    // 转换为灰度图像
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // 使用Sobel算子计算梯度
    cv::Sobel(gray, edge, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    // 将梯度转换为负值，模拟铅笔画的效果
    cv::bitwise_not(edge, sketch);
    // 调整对比度
    cv::multiply(sketch, cv::Scalar::all(1.5), sketch);
    return sketch;
}

// 卡通效果
cv::Mat CuteClass::cartoonEffect(const cv::Mat& src)
{
    // 检查输入图像是否为有效的彩色图像
    if (src.empty() || src.channels() != 3) {
        throw std::runtime_error("Input image is empty or not a 3-channel image.");
    }

    cv::Mat lab, filteredL, channels[3], dst;

    // 将BGR图像转换到LAB颜色空间
    cv::cvtColor(src, lab, cv::COLOR_BGR2Lab);

    // 分离LAB颜色空间的各个通道
    std::vector<cv::Mat> lab_planes;
    cv::split(lab, lab_planes);

    // 对亮度(L)通道使用双边滤波器
    cv::bilateralFilter(lab_planes[0], filteredL, 9, 75, 75);

    // 合并滤波后的亮度通道和原始的a、b通道
    channels[0] = filteredL;
    channels[1] = lab_planes[1];
    channels[2] = lab_planes[2];

    // 使用merge函数合并通道
    cv::merge(channels, 3, dst);

    // 将LAB颜色空间的图像转换回BGR颜色空间
    cv::cvtColor(dst, dst, cv::COLOR_Lab2BGR);

    return dst;
}