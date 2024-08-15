#pragma execution_character_set("utf-8")    //���ñ���
#include "AllUseClass.h"
#include "FilterClass.h"
#include "grayScaleStretching.h"
#include "histogramClass.h"
#include "threshold.h"
#include <qmessagebox.h>

AllUseClass::AllUseClass(cv::Mat image, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    this->image = image;
    dicp = new DIPCD_DengLei;	//������÷���
    cvtColor(image, gray, COLOR_BGR2GRAY);	//���ɻҶ�ͼ��
    bak.push(gray.clone());
    dicp->display_MatInQT(ui.label_showProcessImage, gray);	//��ʾ�Ҷ�ԭͼ
    dicp->display_MatInQT(ui.label_showOriginalImage, image);
    Res = gray;
    //���Ӳ�

    //����
    connect(ui.zpushButton, &QPushButton::clicked, this, &AllUseClass::ctrlZ);

    //ȡ��
    connect(ui.cancelButton, &QPushButton::clicked, this, &AllUseClass::cancelButton);

    //Ԥ����
    //ƽ��ȥ��
    connect(ui.phqzaction, &QAction::triggered, this, &AllUseClass::phqz);  //��ʵ��
    //�Ҷ�����
    connect(ui.hdlsaction, &QAction::triggered, this, &AllUseClass::hdls);  //��ʵ��
    //�ָ�ͼ��
    //OTSU
    connect(ui.OTSUaction, &QAction::triggered, this, &AllUseClass::otsu);  //��ʵ��

    //��̬ѧ����
    //����
    connect(ui.pzaction, &QAction::triggered, this, &AllUseClass::pz);  //��ʵ��
    //��ʴ
    connect(ui.fsaction, &QAction::triggered, this, &AllUseClass::fs);  //��ʵ��
    //�չ�
    connect(ui.bgaction, &QAction::triggered, this, &AllUseClass::bg);  //��ʵ��
    //����
    connect(ui.kqaction, &QAction::triggered, this, &AllUseClass::kq);  //��ʵ��
    //��ñ
    connect(ui.dmaction, &QAction::triggered, this, &AllUseClass::dm);  //��ʵ��
    //��ñ
    connect(ui.hmaction, &QAction::triggered, this, &AllUseClass::hm);  //��ʵ��
    //����
    //����
    connect(ui.wtaction, &QAction::triggered, this, &AllUseClass::wt);  //��ʵ��
    //�ܳ�
    connect(ui.zcaction, &QAction::triggered, this, &AllUseClass::zc);  //��ʵ��
    //Բ�ζ�
    connect(ui.yxdaction, &QAction::triggered, this, &AllUseClass::yxd);    //��ʵ��
    //���ζ�
    connect(ui.jxdaction, &QAction::triggered, this, &AllUseClass::jxd);    //��ʵ��
    //����
    connect(ui.zxaction, &QAction::triggered, this, &AllUseClass::zx);  //��ʵ��
    //����
    connect(ui.monoaction, &QAction::triggered, this, &AllUseClass::zwt);   //��ʵ��
    //����������
    connect(ui.maxAreaaction, &QAction::triggered, this, &AllUseClass::maxArea);    //��ʵ��
}

AllUseClass::~AllUseClass()
{

    while (!bak.empty()) {
        bak.pop();
    }
    delete dicp;
	delete& ui;
}

//����
void AllUseClass::ctrlZ()
{
    if (!bak.empty()) {
        bak.pop(); // ��ȫ�ص���ջ��Ԫ��
        if (bak.empty()) {}
        else {
            Res = bak.top(); // ����һ�������ĸ���
            dicp->display_MatInQT(ui.label_showProcessImage, Res); // չʾ��һ�ε���ʾ
        }
    }
    else {
        // ���ջΪ�գ���ʾ������Ϣ
        QMessageBox::warning(this, "��ʾ", "�Ѿ����������һ����!");
    }
}


void AllUseClass::cancelButton()
{
    this->close();
}

//Ԥ����
//ƽ��ȥ��
void AllUseClass::phqz()
{
    Res = FilterClass::meanBlur(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//�Ҷ�����
void AllUseClass::hdls()
{
    Res = histogramClass::histogramEqualization(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//�ָ�ͼ��
//OTSU
void AllUseClass::otsu()
{
    Res = applyBestThreshold(Res, otsuThreshold(Res));
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//��̬ѧ����
//����
void AllUseClass::pz()
{
    Res = dilateImage(Res, 3);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//��ʴ
void AllUseClass::fs()
{
    Res = erodeImage(Res, 3);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//�չ�
void AllUseClass::bg()
{
    Res = closeImage(Res, 3);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//����
void AllUseClass::kq()
{
    Res = openImage(Res, 3);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//��ñ
void AllUseClass::dm()
{
    Res = tophatImage(Res, 3);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//��ñ
void AllUseClass::hm()
{
    Res = blackHatImage(Res, 2);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//����
//����,���Բ��
void AllUseClass::wt()
{
    Res = HoughCircle(Res, 3,200);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//��������ܳ�
void AllUseClass::zc()
{
    Res = findLargestPerimeter(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//Բ�ζ�
void AllUseClass::yxd()
{
    Res = drawLargestObjectContour(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//���ζ�
void AllUseClass::jxd()
{
    Res = calculateAndDrawMaxRectangularity(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//����
void AllUseClass::zx()
{
    Res = calculateAndDrawCenterOfMass(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//������
void AllUseClass::zwt()
{
    Res = countObjectsInImage(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//����������
void AllUseClass::maxArea()
{
    Res = findLargestObject(Res);
    bak.push(Res.clone());     //������ջ
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}


// ���Ͳ���
cv::Mat AllUseClass::dilateImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(src, dst, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// ��ʴ����
cv::Mat AllUseClass::erodeImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::erode(src, dst, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// �չز���
cv::Mat AllUseClass::closeImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// ��������
cv::Mat AllUseClass::openImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// ��ñ����
cv::Mat AllUseClass::tophatImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// ��ñ����
cv::Mat AllUseClass::blackHatImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// ��ֵ�ָ��
cv::Mat AllUseClass::thresholdImage(const cv::Mat& src, double threshold, double maxVal, int thresholdType )
{
    cv::Mat dst;
    cv::threshold(src, dst, threshold, maxVal, thresholdType);
    return dst;
}

// ������ͨ�������������
void AllUseClass::analyzeConnectedComponents(const cv::Mat& binaryImage, int& objectCount, cv::Rect& boundingBox, double& area, double& perimeter, cv::Point& centroid)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat hierarchy;

    // Ѱ������
    cv::findContours(binaryImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    objectCount = static_cast<int>(hierarchy.total());

    // ��ʼ��������������
    boundingBox = cv::Rect();
    area = 0;
    perimeter = 0;

    for (size_t i = 0; i < contours.size(); ++i) {
        // ���㵱ǰ������������ܳ�
        double currentArea = cv::contourArea(contours[i]);
        double currentPerimeter = cv::arcLength(contours[i], true);

        // ����������������
        if (currentArea > area) {
            area = currentArea;
            perimeter = currentPerimeter;
            boundingBox = cv::boundingRect(contours[i]);
            centroid = cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
        }
    }
}


// ������ζ�
cv::Mat AllUseClass::calculateAndDrawMaxRectangularity(const cv::Mat& inputImage)
{
    // ��ͼ��ת��Ϊ��ֵͼ��
    cv::Mat binaryImage;
    cv::threshold(inputImage, binaryImage, 127, 255, cv::THRESH_BINARY);

    // ��������
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // �ҵ���������������������ζ�
    double maxRectangularity = 0.0;
    cv::Rect boundingRect;
    for (size_t i = 0; i < contours.size(); ++i) {
        cv::Rect rect = cv::boundingRect(contours[i]);
        double area = rect.width * rect.height;
        double perimeter = cv::arcLength(contours[i], true);
        double rectangularity = (perimeter * perimeter) / (4 * area);

        if (rectangularity > maxRectangularity) {
            maxRectangularity = rectangularity;
            boundingRect = rect;
        }
    }
    //�����ζ�
    QMessageBox::about(this, "�����ζ�", "�����ζ�Ϊ" + QString::number(maxRectangularity));

    // �����������
    cv::Mat resultImage = inputImage.clone();
    cv::drawContours(resultImage, contours, -1, cv::Scalar(0, 255, 0), 2); // ������������

    // ������������ı߽����
    cv::rectangle(resultImage, boundingRect, cv::Scalar(0, 0, 255), 2);

    // ���㲢��ʾ�����ζ�
    std::string text = "Max Rectangularity: " + std::to_string(maxRectangularity);
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
    cv::putText(resultImage, text, cv::Point(10, 30 + textSize.height), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

    return resultImage;
}

//���Բ
cv::Mat AllUseClass::HoughCircle(const cv::Mat& src, int minRadius, int maxRadius)
{
    // �������ͼ���Ƿ�Ϊ��Ч��ͼ��
    if (src.empty()) {
        throw std::runtime_error("Input image is empty.");
    }

    cv::Mat gray;
    // ȷ������ͼ���ǵ�ͨ���ĻҶ�ͼ��
    if (src.channels() != 1) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone();
    }

    // ʹ����ֵ�˲�ȥ������
    cv::medianBlur(gray, gray, 5);

    std::vector<cv::Vec3f> circles;
    // Ӧ�û���Բ�任���Բ
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 16, 100, 30, minRadius, maxRadius);

    cv::Mat dstImg;
    if (src.channels() == 3) {
        dstImg = src.clone(); // ����ԭͼ��ͨ����
    }
    else {
        dstImg.create(src.size(), src.type()); // ������ԭͼ��ͬ��С�����͵�ͼ��
    }

    // ���û�м�⵽Բ��dstImg ����ԭͼ��ͬ
    if (!circles.empty()) {
        for (size_t i = 0; i < circles.size(); i++) {
            cv::Vec3i c = cv::Vec3i(circles[i]); // ת��Ϊ����
            cv::Point center = cv::Point(c[0], c[1]);
            int radius = c[2];

            // ���Ƽ�⵽��Բ��
            cv::circle(dstImg, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
            // ����Բ����
            cv::circle(dstImg, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
        }
    }

    return dstImg;
}

//��������
cv::Mat AllUseClass::countObjectsInImage(const cv::Mat& inputImage)
{
    // 1. ȷ������ͼ���ǻҶȵ�
    cv::Mat grayImage;
    if (inputImage.channels() > 1) {
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    }
    else {
        grayImage = inputImage.clone();
    }

    // 2. Ӧ����ֵ�������õ���ֵͼ��
    cv::Mat binaryImage;
    double thresholdValue = 128; // ���Ը�����Ҫ������ֵ
    cv::threshold(grayImage, binaryImage, thresholdValue, 255, cv::THRESH_BINARY);

    // 3. �ҵ���ֵͼ���е�������ͨ��
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 4. ͳ����ͨ�������
    int objectCount = contours.size();

    QMessageBox::about(this, "��������", "ʶ���"+QString::number(objectCount)+"������");

    // ��ԭͼ�ϻ����������������ڿ��ӻ�
    cv::Mat resultImage = inputImage.clone();
    cv::drawContours(resultImage, contours, -1, cv::Scalar(0, 255, 0), 2);

    return resultImage;
}

//�ܳ�
cv::Mat AllUseClass::findLargestPerimeter(const cv::Mat& src)
{
    if (src.empty()) {
        throw std::runtime_error("Input image is empty.");
    }

    // ��ͼ��ת��Ϊ�Ҷ�ͼ
    cv::Mat gray;
    if (src.channels() > 1) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone();
    }

    // Ӧ����ֵ������ͼ���ֵ��
    cv::Mat binary;
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY );

    // �ҵ���ͨ���
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // ����ÿ����ͨ������ܳ�
    double maxPerimeter = 0.0;
    int maxPerimeterContourIndex = -1;
    for (size_t i = 0; i < contours.size(); ++i) {
        double perimeter = cv::arcLength(contours[i], true);
        if (perimeter > maxPerimeter) {
            maxPerimeter = perimeter;
            maxPerimeterContourIndex = i;
        }
    }

    // ���û���ҵ��κ���ͨ���������ԭͼ
    if (maxPerimeterContourIndex == -1) {
        return src.clone();
    }

    //����ܳ�
    QMessageBox::about(this, "����ܳ�", "��������ܳ�Ϊ" + QString::number(maxPerimeter));
    // ����һ����Դͼ����ͬ��С�����͵�ͼ�����ڻ�������
    cv::Mat dst(src.size(), src.type(), cv::Scalar(0, 0, 0)); // ��ʼ��Ϊȫ͸����ɫ

    // ���������ͨ���������
    cv::drawContours(dst, contours, maxPerimeterContourIndex, cv::Scalar(0, 255, 0), 2);

    return dst;
}
//Բ�ζ�
cv::Mat AllUseClass::drawLargestObjectContour(const cv::Mat& inputImage)
{
    // ��ͼ��ת��Ϊ�Ҷ�ͼ��
    cv::Mat grayImage;
    if (inputImage.channels() > 1) {
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    }
    else {
        grayImage = inputImage.clone();
    }

    // ʹ�ø�˹ģ������ͼ������
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);

    // ʹ��Canny��Ե���������Ե
    cv::Mat edges;
    cv::Canny(grayImage, edges, 75, 200);

    // ��������
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // �ҵ��������������
    int maxContourIndex = 0;
    double maxArea = 0.0;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxContourIndex = i;
        }
    }

    // �����������
    cv::Mat resultImage = inputImage.clone(); // ����ԭͼ���Ի�������
    cv::drawContours(resultImage, contours, maxContourIndex, cv::Scalar(0, 255, 0), 2);

    // �������������Բ�ζ�
    double perimeter = cv::arcLength(contours[maxContourIndex], true);
    std::vector<cv::Point> approxCurve;
    cv::approxPolyDP(contours[maxContourIndex], approxCurve, 0.02 * perimeter, true);
    cv::Moments moments = cv::moments(contours[maxContourIndex]);
    double area = moments.m00;

    double circularity = 0.0;
    if (perimeter > 0 && area > 0) {
        circularity = 4 * CV_PI * area / (perimeter * perimeter);
    }

    //���Բ�ζ�
    QMessageBox::about(this, "���Բ�ζ�", "���Բ�ζ�Ϊ" + QString::number(circularity));
    
    // ��ͼ������ʾԲ�ζ�
    int baseline = 0;
    std::string text = format("Circularity: %.2f", circularity);
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
    cv::Point textOrigin(10, 25 + textSize.height);
    cv::putText(resultImage, text, textOrigin, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

    return resultImage;
}

//��������
cv::Mat AllUseClass::calculateAndDrawCenterOfMass(const cv::Mat& inputImage)
{
    // ȷ������ͼ���Ƕ�ֵ��
    cv::Mat binaryImage;
    if (inputImage.type() != CV_8U) {
        cv::cvtColor(inputImage, binaryImage, cv::COLOR_BGR2GRAY);
        cv::threshold(binaryImage, binaryImage, 128, 255, cv::THRESH_BINARY_INV);
    }
    else {
        binaryImage = inputImage.clone();
    }

    // ����ͼ��ľ�
    cv::Moments moments = cv::moments(binaryImage, true);

    // ���ͼ����Ƿ���Ч����ͼ���ǿյģ�
    if (moments.m00 != 0.0) {
        // �������ĵ� x �� y ����
        double x = moments.m10 / moments.m00;
        double y = moments.m01 / moments.m00;

        QMessageBox::about(this, "��������", "�������������Ϊ(" + QString::number(x) + "," + QString::number(y)+")");

        // ��ԭʼͼ���ϻ�������λ��
        cv::circle(inputImage, cv::Point(static_cast<int>(x), static_cast<int>(y)), 5, cv::Scalar(0, 255, 0), -1);
    }

    return inputImage;
}

//����������
cv::Mat AllUseClass::findLargestObject(const cv::Mat& src)
{
    // �������ͼ���Ƿ�Ϊ��Ч��Mat����
    if (src.empty()) {
        throw std::runtime_error("Input image is empty.");
    }

    // ��ͼ��ת��Ϊ�Ҷ�ͼ
    cv::Mat gray;
    if (src.channels() > 1) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone(); // ����Ѿ��ǻҶ�ͼ��ֱ�ӿ�¡
    }

    // Ӧ����ֵ������ͼ���ֵ��
    cv::Mat binary;
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);

    // �ҵ���ͨ���
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // ����ÿ����ͨ��������
    double maxArea = 0.0;
    int maxAreaContourIndex = -1;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaContourIndex = i;
        }
    }

    // ���û���ҵ��κ���ͨ���������ԭͼ
    if (maxAreaContourIndex == -1) {
        return src.clone();
    }
    //������
    QMessageBox::about(this, "������", "���ͼ�����Ϊ" + QString::number(maxArea));
    
    // ���������ͨ���������
    cv::Mat dst = src.clone(); // ��¡ԭͼ�Ի�������
    cv::drawContours(dst, contours, maxAreaContourIndex, cv::Scalar(0, 255, 0), 2);

    return dst;
}
