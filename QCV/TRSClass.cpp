#include "TRSClass.h"

TRSClass::TRSClass(cv::Mat image, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->image = image;
	dicp = new DIPCD_DengLei;	//������÷���
	cvtColor(image, gray, COLOR_BGR2GRAY);	//���ɻҶ�ͼ��
	dicp->display_MatInQT(ui.label_showProcessImage, gray);	//��ʾ�Ҷ�ԭͼ

    //���Ӳ�

    //ƽ��
    connect(ui.PYradioButton, &QRadioButton::clicked, this, &TRSClass::PY);
    //��ת
    connect(ui.XZradioButton, &QRadioButton::clicked, this, &TRSClass::XZ);
    //����
    connect(ui.SFradioButton, &QRadioButton::clicked, this, &TRSClass::SF);

    connect(ui.enterpushButton, &QPushButton::clicked, this, &TRSClass::enterButton);
    connect(ui.cancelpushButton, &QPushButton::clicked, this, &TRSClass::cancelButton);

}

TRSClass::~TRSClass()
{
    delete dicp;
	delete& ui;
}

//ƽ��
void TRSClass::PY()
{
    Res = translateImage(gray,
        ui.XlineEdit->text().toInt(),
        ui.YlineEdit->text().toInt()
    );
}

//��ת
void TRSClass::XZ()
{
    Res = rotateImage(gray, ui.VlineEdit->text().toDouble());
}

//����
void TRSClass::SF()
{
    Res = scaleImage(gray, ui.DlineEdit->text().toDouble());
}


//ȷ����ť
void TRSClass::enterButton()
{
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//ȡ����ť
void TRSClass::cancelButton()
{
    this->close();
}

/*
����Ϊ�ײ㺯��
*/




//ƽ�Ʋ�����ͼ���С����
cv::Mat TRSClass::translateImage(const cv::Mat& srcImage, int xOffset, int yOffset) 
{
    cv::Mat resultImage;
    cv::Mat translationMatrix = cv::Mat::eye(2, 3, CV_64F); // ����2x3�ĵ�λ������Ϊ����任����

    // ����ƽ�ƾ���
    translationMatrix.at<double>(0, 2) = xOffset; // x����ƽ��
    translationMatrix.at<double>(1, 2) = yOffset; // y����ƽ��

    // Ӧ�÷���任
    cv::warpAffine(srcImage, resultImage, translationMatrix, srcImage.size());
    return resultImage;
}
// ��ת�任
cv::Mat TRSClass::rotateImage(const cv::Mat& src, double angle, double scale)
{
    cv::Mat dst;
    // ��ȡͼ��ߴ�
    cv::Size sz = src.size();
    // ������ת����
    cv::Point2f center(sz.width / 2.0, sz.height / 2.0);

    // ��ȡ��ת����
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, scale);

    // Ӧ�÷���任����ת��
    cv::warpAffine(src, dst, rotationMatrix, sz);
    return dst;
}

// ���ű任
cv::Mat TRSClass::scaleImage(const cv::Mat& src, double scale)
{
    cv::Mat dst;
    cv::Size newSize(cvRound(src.cols * scale), cvRound(src.rows * scale));

    // ʹ�� INTER_AREA ������С����
    int interpolationMethod = (scale < 1) ? cv::INTER_AREA : cv::INTER_CUBIC;
    cv::resize(src, dst, newSize, 0, 0, interpolationMethod);
    return dst;
}