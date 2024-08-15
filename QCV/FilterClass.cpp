#include "FilterClass.h"

FilterClass::FilterClass(cv::Mat image, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->image = image;
	dicp = new DIPCD_DengLei;	//������÷���
	cvtColor(image, gray, COLOR_BGR2GRAY);	//���ɻҶ�ͼ��
	dicp->display_MatInQT(ui.label_showProcessImage, gray);	//��ʾ�Ҷ�ԭͼ

    //���Ӳ�

    //��ɫ�任
    connect(ui.radioButton_1, &QRadioButton::clicked, this, &FilterClass::invert);
    //��ֵ
    connect(ui.radioButton_2, &QRadioButton::clicked, this, &FilterClass::mean);
    //��˹
    connect(ui.radioButton_3, &QRadioButton::clicked, this, &FilterClass::gauss);
    //��
    connect(ui.radioButton_4, &QRadioButton::clicked, this, &FilterClass::sharp);
    //����
    connect(ui.radioButton_5, &QRadioButton::clicked, this, &FilterClass::em);
    //Sobel����
    connect(ui.radioButton_6, &QRadioButton::clicked, this, &FilterClass::edge);
    //�ı�����
    connect(ui.radioButton_7, &QRadioButton::clicked, this, &FilterClass::adjustB);
    //�ı�Աȶ�
    connect(ui.radioButton_8, &QRadioButton::clicked, this, &FilterClass::adjustC);

    //Ԥ��ͼ��
    connect(ui.viewpushButton, &QPushButton::clicked, this, &FilterClass::viewP);
    //�ָ�ͼ��
    connect(ui.recpushButton, &QPushButton::clicked, this, &FilterClass::recP);

    //װ������
    connect(ui.usepushButton, &QPushButton::clicked, this, &FilterClass::withPic);

    //ȷ��
    connect(ui.enterpushButton, &QPushButton::clicked, this, &FilterClass::enterButton);

    //ȡ��
    connect(ui.cancelpushButton, &QPushButton::clicked, this, &FilterClass::cancelButton);
}

FilterClass::~FilterClass()
{
	delete dicp;
	delete& ui;
}


//ȷ����ť
void FilterClass::enterButton()
{
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//ȡ����ť
void FilterClass::cancelButton()
{
	this->close();
}

//Ԥ��ͼ��
void FilterClass::viewP()
{
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//�ָ�ͼ��
void FilterClass::recP()
{
    dicp->display_MatInQT(ui.label_showProcessImage, gray);
}

//��ɫ
void FilterClass::invert()
{
    Res = invertColor(gray);
}

//��ֵģ��
void FilterClass::mean()
{
    Res = meanBlur(gray);
}

//��˹ģ��
void FilterClass::gauss()
{
    Res = gaussianBlur(gray);
}

// �� - ʹ��������˹����
void FilterClass::sharp()
{
    Res = sharpen(gray);
}

// ��Ե��� - ʹ��Sobel����
void FilterClass::edge()
{
    Res = edgeDetection(gray);
}

// ����Ч��
void FilterClass::em()
{
    Res = emboss(gray);
}

// �ı����� - ͨ����ӳ���ֵ
void FilterClass::adjustB()
{
    int value = ui.valuelineEdit->text().toInt();
    Res = adjustBrightness(gray,value);
}

// �ı�Աȶ� - ͨ������ϵ����б�ʣ�
void FilterClass::adjustC()
{
    int k = ui.definelineEdit->text().toInt();
    Res = adjustContrast(gray, k);
}

//ʹ�ø��������ӽ��д���ͼ��
void FilterClass::withPic()
{
    Res = applyCustomFilter(gray, toFilter());
}



/*
�����ǵײ㣬ֻ����ĵ���
*/

// Ӧ��3x3���ӵ�ͼ��ĺ���
cv::Mat FilterClass::applyCustomFilter(const cv::Mat& src, const cv::Mat& filter)
{
    // ȷ������ͼ���ǵ�ͨ���Ҷ�ͼ
    if (src.channels() != 1) {
        throw std::runtime_error("Source image must be a single-channel grayscale image.");
    }

    // ȷ��������3x3��С
    if (filter.rows != 3 || filter.cols != 3) {
        throw std::runtime_error("Filter must be a 3x3 matrix.");
    }

    // �������ͼ��������ͼ�������ͬ�Ĵ�С������
    cv::Mat dst;

    // Ӧ������
    cv::filter2D(src, dst, -1, filter, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    return dst;
}

//�û������ת����3*3Mat����
cv::Mat FilterClass::toFilter()
{
    // ����һ��3x3����
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


// ��ɫ�任
cv::Mat FilterClass::invertColor(const cv::Mat& src)
{
    cv::Mat dst;
    cv::bitwise_not(src, dst);
    return dst;
}

// ƽ��/ģ�� - ��ֵģ��
cv::Mat FilterClass::meanBlur(const cv::Mat& src)
{
    cv::Mat dst;
    cv::blur(src, dst, cv::Size(3, 3)); // 3x3��ֵ�˲���
    return dst;
}

// ��˹ģ��
cv::Mat FilterClass::gaussianBlur(const cv::Mat& src)
{
    cv::Mat dst;
    cv::GaussianBlur(src, dst, cv::Size(5, 5), 0); // 5x5��˹�˲���
    return dst;
}


// �� - ʹ��������˹����
cv::Mat FilterClass::sharpen(const cv::Mat& src)
{
    cv::Mat dst, kernel;
    int kernelSize = 3;
    double ddepth = -1;

    // ������˹����
    kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    cv::filter2D(src, dst, ddepth, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    return dst;
}

// ��Ե��� - ʹ��Sobel����
cv::Mat FilterClass::edgeDetection(const cv::Mat& src)
{
    cv::Mat dst, grad_x, grad_y;
    int sobelSize = 3;
    double scale = 1;
    double delta = 0;
    int ddepth = CV_16S;

    // ����ˮƽ�ʹ�ֱ�ݶ�
    cv::Sobel(src, grad_x, ddepth, 1, 0, sobelSize, scale, delta, cv::BORDER_DEFAULT);
    cv::Sobel(src, grad_y, ddepth, 0, 1, sobelSize, scale, delta, cv::BORDER_DEFAULT);

    // �����ݶȷ���
    cv::Mat abs_grad_x;
    cv::convertScaleAbs(grad_x, abs_grad_x);

    cv::Mat abs_grad_y;
    cv::convertScaleAbs(grad_y, abs_grad_y);

    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

    return dst;
}

// ����Ч��
cv::Mat FilterClass::emboss(const cv::Mat& src)
{
    cv::Mat dst;
    // ���þ����
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);
    // ȷ�����ͼ������������ͼ��һ��
    cv::filter2D(src, dst, src.depth(), kernel, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
    return dst;
}



// �ı����� - ͨ����ӳ���ֵ
cv::Mat FilterClass::adjustBrightness(const cv::Mat& src, int value)
{
    cv::Mat dst;
    cv::add(src, value, dst);
    return dst;
}

// �ı�Աȶ� - ͨ������ϵ����б�ʣ�(0,3)
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