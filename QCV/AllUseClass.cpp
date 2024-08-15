#pragma execution_character_set("utf-8")    //设置编码
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
    dicp = new DIPCD_DengLei;	//方便调用方法
    cvtColor(image, gray, COLOR_BGR2GRAY);	//生成灰度图像
    bak.push(gray.clone());
    dicp->display_MatInQT(ui.label_showProcessImage, gray);	//显示灰度原图
    dicp->display_MatInQT(ui.label_showOriginalImage, image);
    Res = gray;
    //连接槽

    //撤销
    connect(ui.zpushButton, &QPushButton::clicked, this, &AllUseClass::ctrlZ);

    //取消
    connect(ui.cancelButton, &QPushButton::clicked, this, &AllUseClass::cancelButton);

    //预处理
    //平滑去噪
    connect(ui.phqzaction, &QAction::triggered, this, &AllUseClass::phqz);  //已实现
    //灰度拉伸
    connect(ui.hdlsaction, &QAction::triggered, this, &AllUseClass::hdls);  //已实现
    //分割图像
    //OTSU
    connect(ui.OTSUaction, &QAction::triggered, this, &AllUseClass::otsu);  //已实现

    //形态学处理
    //膨胀
    connect(ui.pzaction, &QAction::triggered, this, &AllUseClass::pz);  //已实现
    //腐蚀
    connect(ui.fsaction, &QAction::triggered, this, &AllUseClass::fs);  //已实现
    //闭关
    connect(ui.bgaction, &QAction::triggered, this, &AllUseClass::bg);  //已实现
    //开启
    connect(ui.kqaction, &QAction::triggered, this, &AllUseClass::kq);  //已实现
    //顶帽
    connect(ui.dmaction, &QAction::triggered, this, &AllUseClass::dm);  //已实现
    //黑帽
    connect(ui.hmaction, &QAction::triggered, this, &AllUseClass::hm);  //已实现
    //杂项
    //物体
    connect(ui.wtaction, &QAction::triggered, this, &AllUseClass::wt);  //已实现
    //周长
    connect(ui.zcaction, &QAction::triggered, this, &AllUseClass::zc);  //已实现
    //圆形度
    connect(ui.yxdaction, &QAction::triggered, this, &AllUseClass::yxd);    //已实现
    //矩形度
    connect(ui.jxdaction, &QAction::triggered, this, &AllUseClass::jxd);    //已实现
    //重心
    connect(ui.zxaction, &QAction::triggered, this, &AllUseClass::zx);  //已实现
    //物体
    connect(ui.monoaction, &QAction::triggered, this, &AllUseClass::zwt);   //已实现
    //最大物体面积
    connect(ui.maxAreaaction, &QAction::triggered, this, &AllUseClass::maxArea);    //已实现
}

AllUseClass::~AllUseClass()
{

    while (!bak.empty()) {
        bak.pop();
    }
    delete dicp;
	delete& ui;
}

//撤销
void AllUseClass::ctrlZ()
{
    if (!bak.empty()) {
        bak.pop(); // 安全地弹出栈顶元素
        if (bak.empty()) {}
        else {
            Res = bak.top(); // 创建一个独立的副本
            dicp->display_MatInQT(ui.label_showProcessImage, Res); // 展示上一次的显示
        }
    }
    else {
        // 如果栈为空，显示警告消息
        QMessageBox::warning(this, "提示", "已经撤销到最后一个啦!");
    }
}


void AllUseClass::cancelButton()
{
    this->close();
}

//预处理
//平滑去噪
void AllUseClass::phqz()
{
    Res = FilterClass::meanBlur(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//灰度拉伸
void AllUseClass::hdls()
{
    Res = histogramClass::histogramEqualization(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//分割图像
//OTSU
void AllUseClass::otsu()
{
    Res = applyBestThreshold(Res, otsuThreshold(Res));
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//形态学处理
//膨胀
void AllUseClass::pz()
{
    Res = dilateImage(Res, 3);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//腐蚀
void AllUseClass::fs()
{
    Res = erodeImage(Res, 3);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//闭关
void AllUseClass::bg()
{
    Res = closeImage(Res, 3);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//开启
void AllUseClass::kq()
{
    Res = openImage(Res, 3);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//顶帽
void AllUseClass::dm()
{
    Res = tophatImage(Res, 3);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//黑帽
void AllUseClass::hm()
{
    Res = blackHatImage(Res, 2);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//杂项
//物体,检测圆形
void AllUseClass::wt()
{
    Res = HoughCircle(Res, 3,200);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//最大物体周长
void AllUseClass::zc()
{
    Res = findLargestPerimeter(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//圆形度
void AllUseClass::yxd()
{
    Res = drawLargestObjectContour(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//矩形度
void AllUseClass::jxd()
{
    Res = calculateAndDrawMaxRectangularity(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}
//重心
void AllUseClass::zx()
{
    Res = calculateAndDrawCenterOfMass(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//真物体
void AllUseClass::zwt()
{
    Res = countObjectsInImage(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}

//最大物体面积
void AllUseClass::maxArea()
{
    Res = findLargestObject(Res);
    bak.push(Res.clone());     //拷贝入栈
    dicp->display_MatInQT(ui.label_showProcessImage, Res);
}


// 膨胀操作
cv::Mat AllUseClass::dilateImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(src, dst, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// 腐蚀操作
cv::Mat AllUseClass::erodeImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::erode(src, dst, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// 闭关操作
cv::Mat AllUseClass::closeImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// 开启操作
cv::Mat AllUseClass::openImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// 顶帽操作
cv::Mat AllUseClass::tophatImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// 黑帽操作
cv::Mat AllUseClass::blackHatImage(const cv::Mat& src, int iterations)
{
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(src, dst, cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    return dst;
}

// 阈值分割函数
cv::Mat AllUseClass::thresholdImage(const cv::Mat& src, double threshold, double maxVal, int thresholdType )
{
    cv::Mat dst;
    cv::threshold(src, dst, threshold, maxVal, thresholdType);
    return dst;
}

// 计算连通区域的轮廓特征
void AllUseClass::analyzeConnectedComponents(const cv::Mat& binaryImage, int& objectCount, cv::Rect& boundingBox, double& area, double& perimeter, cv::Point& centroid)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat hierarchy;

    // 寻找轮廓
    cv::findContours(binaryImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    objectCount = static_cast<int>(hierarchy.total());

    // 初始化最大物体的特征
    boundingBox = cv::Rect();
    area = 0;
    perimeter = 0;

    for (size_t i = 0; i < contours.size(); ++i) {
        // 计算当前轮廓的面积和周长
        double currentArea = cv::contourArea(contours[i]);
        double currentPerimeter = cv::arcLength(contours[i], true);

        // 更新最大物体的特征
        if (currentArea > area) {
            area = currentArea;
            perimeter = currentPerimeter;
            boundingBox = cv::boundingRect(contours[i]);
            centroid = cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
        }
    }
}


// 计算矩形度
cv::Mat AllUseClass::calculateAndDrawMaxRectangularity(const cv::Mat& inputImage)
{
    // 将图像转换为二值图像
    cv::Mat binaryImage;
    cv::threshold(inputImage, binaryImage, 127, 255, cv::THRESH_BINARY);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 找到最大轮廓的索引和最大矩形度
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
    //最大矩形度
    QMessageBox::about(this, "最大矩形度", "最大矩形度为" + QString::number(maxRectangularity));

    // 绘制最大轮廓
    cv::Mat resultImage = inputImage.clone();
    cv::drawContours(resultImage, contours, -1, cv::Scalar(0, 255, 0), 2); // 绘制所有轮廓

    // 绘制最大轮廓的边界矩形
    cv::rectangle(resultImage, boundingRect, cv::Scalar(0, 0, 255), 2);

    // 计算并显示最大矩形度
    std::string text = "Max Rectangularity: " + std::to_string(maxRectangularity);
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
    cv::putText(resultImage, text, cv::Point(10, 30 + textSize.height), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

    return resultImage;
}

//检测圆
cv::Mat AllUseClass::HoughCircle(const cv::Mat& src, int minRadius, int maxRadius)
{
    // 检查输入图像是否为有效的图像
    if (src.empty()) {
        throw std::runtime_error("Input image is empty.");
    }

    cv::Mat gray;
    // 确保输入图像是单通道的灰度图像
    if (src.channels() != 1) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone();
    }

    // 使用中值滤波去除噪声
    cv::medianBlur(gray, gray, 5);

    std::vector<cv::Vec3f> circles;
    // 应用霍夫圆变换检测圆
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 16, 100, 30, minRadius, maxRadius);

    cv::Mat dstImg;
    if (src.channels() == 3) {
        dstImg = src.clone(); // 保持原图的通道数
    }
    else {
        dstImg.create(src.size(), src.type()); // 创建与原图相同大小和类型的图像
    }

    // 如果没有检测到圆，dstImg 将与原图相同
    if (!circles.empty()) {
        for (size_t i = 0; i < circles.size(); i++) {
            cv::Vec3i c = cv::Vec3i(circles[i]); // 转换为整型
            cv::Point center = cv::Point(c[0], c[1]);
            int radius = c[2];

            // 绘制检测到的圆心
            cv::circle(dstImg, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
            // 绘制圆轮廓
            cv::circle(dstImg, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
        }
    }

    return dstImg;
}

//几个物体
cv::Mat AllUseClass::countObjectsInImage(const cv::Mat& inputImage)
{
    // 1. 确保输入图像是灰度的
    cv::Mat grayImage;
    if (inputImage.channels() > 1) {
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    }
    else {
        grayImage = inputImage.clone();
    }

    // 2. 应用阈值操作，得到二值图像
    cv::Mat binaryImage;
    double thresholdValue = 128; // 可以根据需要调整阈值
    cv::threshold(grayImage, binaryImage, thresholdValue, 255, cv::THRESH_BINARY);

    // 3. 找到二值图像中的所有连通域
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 4. 统计连通域的数量
    int objectCount = contours.size();

    QMessageBox::about(this, "物体数量", "识别出"+QString::number(objectCount)+"个物体");

    // 在原图上绘制物体轮廓，用于可视化
    cv::Mat resultImage = inputImage.clone();
    cv::drawContours(resultImage, contours, -1, cv::Scalar(0, 255, 0), 2);

    return resultImage;
}

//周长
cv::Mat AllUseClass::findLargestPerimeter(const cv::Mat& src)
{
    if (src.empty()) {
        throw std::runtime_error("Input image is empty.");
    }

    // 将图像转换为灰度图
    cv::Mat gray;
    if (src.channels() > 1) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone();
    }

    // 应用阈值操作将图像二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY );

    // 找到连通组件
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 计算每个连通组件的周长
    double maxPerimeter = 0.0;
    int maxPerimeterContourIndex = -1;
    for (size_t i = 0; i < contours.size(); ++i) {
        double perimeter = cv::arcLength(contours[i], true);
        if (perimeter > maxPerimeter) {
            maxPerimeter = perimeter;
            maxPerimeterContourIndex = i;
        }
    }

    // 如果没有找到任何连通组件，返回原图
    if (maxPerimeterContourIndex == -1) {
        return src.clone();
    }

    //最大周长
    QMessageBox::about(this, "最大周长", "最大物体周长为" + QString::number(maxPerimeter));
    // 创建一个与源图像相同大小和类型的图像，用于绘制轮廓
    cv::Mat dst(src.size(), src.type(), cv::Scalar(0, 0, 0)); // 初始化为全透明黑色

    // 绘制最大连通组件的轮廓
    cv::drawContours(dst, contours, maxPerimeterContourIndex, cv::Scalar(0, 255, 0), 2);

    return dst;
}
//圆形度
cv::Mat AllUseClass::drawLargestObjectContour(const cv::Mat& inputImage)
{
    // 将图像转换为灰度图像
    cv::Mat grayImage;
    if (inputImage.channels() > 1) {
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    }
    else {
        grayImage = inputImage.clone();
    }

    // 使用高斯模糊减少图像噪声
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);

    // 使用Canny边缘检测器检测边缘
    cv::Mat edges;
    cv::Canny(grayImage, edges, 75, 200);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 找到最大轮廓的索引
    int maxContourIndex = 0;
    double maxArea = 0.0;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxContourIndex = i;
        }
    }

    // 绘制最大轮廓
    cv::Mat resultImage = inputImage.clone(); // 复制原图像以绘制轮廓
    cv::drawContours(resultImage, contours, maxContourIndex, cv::Scalar(0, 255, 0), 2);

    // 计算最大轮廓的圆形度
    double perimeter = cv::arcLength(contours[maxContourIndex], true);
    std::vector<cv::Point> approxCurve;
    cv::approxPolyDP(contours[maxContourIndex], approxCurve, 0.02 * perimeter, true);
    cv::Moments moments = cv::moments(contours[maxContourIndex]);
    double area = moments.m00;

    double circularity = 0.0;
    if (perimeter > 0 && area > 0) {
        circularity = 4 * CV_PI * area / (perimeter * perimeter);
    }

    //最大圆形度
    QMessageBox::about(this, "最大圆形度", "最大圆形度为" + QString::number(circularity));
    
    // 在图像上显示圆形度
    int baseline = 0;
    std::string text = format("Circularity: %.2f", circularity);
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
    cv::Point textOrigin(10, 25 + textSize.height);
    cv::putText(resultImage, text, textOrigin, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

    return resultImage;
}

//重心坐标
cv::Mat AllUseClass::calculateAndDrawCenterOfMass(const cv::Mat& inputImage)
{
    // 确保输入图像是二值的
    cv::Mat binaryImage;
    if (inputImage.type() != CV_8U) {
        cv::cvtColor(inputImage, binaryImage, cv::COLOR_BGR2GRAY);
        cv::threshold(binaryImage, binaryImage, 128, 255, cv::THRESH_BINARY_INV);
    }
    else {
        binaryImage = inputImage.clone();
    }

    // 计算图像的矩
    cv::Moments moments = cv::moments(binaryImage, true);

    // 检查图像矩是否有效（即图像不是空的）
    if (moments.m00 != 0.0) {
        // 计算重心的 x 和 y 坐标
        double x = moments.m10 / moments.m00;
        double y = moments.m01 / moments.m00;

        QMessageBox::about(this, "重心坐标", "计算出重心坐标为(" + QString::number(x) + "," + QString::number(y)+")");

        // 在原始图像上绘制重心位置
        cv::circle(inputImage, cv::Point(static_cast<int>(x), static_cast<int>(y)), 5, cv::Scalar(0, 255, 0), -1);
    }

    return inputImage;
}

//最大物体面积
cv::Mat AllUseClass::findLargestObject(const cv::Mat& src)
{
    // 检查输入图像是否为有效的Mat对象
    if (src.empty()) {
        throw std::runtime_error("Input image is empty.");
    }

    // 将图像转换为灰度图
    cv::Mat gray;
    if (src.channels() > 1) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone(); // 如果已经是灰度图，直接克隆
    }

    // 应用阈值操作将图像二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);

    // 找到连通组件
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 计算每个连通组件的面积
    double maxArea = 0.0;
    int maxAreaContourIndex = -1;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaContourIndex = i;
        }
    }

    // 如果没有找到任何连通组件，返回原图
    if (maxAreaContourIndex == -1) {
        return src.clone();
    }
    //最大面积
    QMessageBox::about(this, "最大面积", "最大图形面积为" + QString::number(maxArea));
    
    // 绘制最大连通组件的轮廓
    cv::Mat dst = src.clone(); // 克隆原图以绘制轮廓
    cv::drawContours(dst, contours, maxAreaContourIndex, cv::Scalar(0, 255, 0), 2);

    return dst;
}
