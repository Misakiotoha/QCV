#include "CuteClass.h"

CuteClass::CuteClass(cv::Mat image,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    this->image = image;
    dicp = new DIPCD_DengLei();
    dicp->display_MatInQT(ui.label_showProcessImage, this->image);
    //���Ӳ�
    //ȡ��
    connect(ui.cancelpushButton, &QPushButton::clicked, this, &CuteClass::cancelButton);
    //ȷ��
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

// �ͻ�Ч��ѡ��
void CuteClass::YH()
{
    Res = oilPaintingEffect(image);
}

// Ǧ�ʻ�Ч��ѡ��
void CuteClass::QB()
{
    Res = pencilSketch(image);
}

// ��ͨЧ��ѡ��
void CuteClass::KT()
{
    Res = cartoonEffect(image);
}

//ȷ����ť
void CuteClass::enterButton()
{
    dicp->display_MatInQT(ui.label_showProcessImage,Res);
}

//ȡ����ť
void CuteClass::cancelButton()
{
    this->close();
}



// �ͻ�Ч��
cv::Mat CuteClass::oilPaintingEffect(const cv::Mat& src)
{
    cv::Mat edge, color, dst;
    // ʹ��Canny���Ӽ���Ե
    cv::Canny(src, edge, 100, 200);
    // ��˹ģ����ģ���ͻ��ıʴ�
    cv::GaussianBlur(src, color, cv::Size(5, 5), 0);
    // ����Ե��ģ����ͼ��ϲ�
    cv::bitwise_and(color, color, dst, edge);
    return dst;
}

// Ǧ�ʻ�Ч��
cv::Mat CuteClass::pencilSketch(const cv::Mat& src)
{
    cv::Mat gray, edge, sketch;
    // ת��Ϊ�Ҷ�ͼ��
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // ʹ��Sobel���Ӽ����ݶ�
    cv::Sobel(gray, edge, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    // ���ݶ�ת��Ϊ��ֵ��ģ��Ǧ�ʻ���Ч��
    cv::bitwise_not(edge, sketch);
    // �����Աȶ�
    cv::multiply(sketch, cv::Scalar::all(1.5), sketch);
    return sketch;
}

// ��ͨЧ��
cv::Mat CuteClass::cartoonEffect(const cv::Mat& src)
{
    // �������ͼ���Ƿ�Ϊ��Ч�Ĳ�ɫͼ��
    if (src.empty() || src.channels() != 3) {
        throw std::runtime_error("Input image is empty or not a 3-channel image.");
    }

    cv::Mat lab, filteredL, channels[3], dst;

    // ��BGRͼ��ת����LAB��ɫ�ռ�
    cv::cvtColor(src, lab, cv::COLOR_BGR2Lab);

    // ����LAB��ɫ�ռ�ĸ���ͨ��
    std::vector<cv::Mat> lab_planes;
    cv::split(lab, lab_planes);

    // ������(L)ͨ��ʹ��˫���˲���
    cv::bilateralFilter(lab_planes[0], filteredL, 9, 75, 75);

    // �ϲ��˲��������ͨ����ԭʼ��a��bͨ��
    channels[0] = filteredL;
    channels[1] = lab_planes[1];
    channels[2] = lab_planes[2];

    // ʹ��merge�����ϲ�ͨ��
    cv::merge(channels, 3, dst);

    // ��LAB��ɫ�ռ��ͼ��ת����BGR��ɫ�ռ�
    cv::cvtColor(dst, dst, cv::COLOR_Lab2BGR);

    return dst;
}