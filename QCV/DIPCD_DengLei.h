#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DIPCD_DengLei.h"

#include <QLabel>
#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;

// 对应的是 ui 文件中的类
namespace Ui
{
    class DIPCD_DengLeiClass;
}

class DIPCD_DengLei : public QMainWindow
{
    Q_OBJECT

public:
    explicit DIPCD_DengLei(QWidget* parent = nullptr);
    ~DIPCD_DengLei();

private:
    Ui::DIPCD_DengLeiClass* ui;
    Mat image;
    Mat gray;
    Mat binary;
    Mat meanFiltering3x3;
    Mat medianFiltering3x3;
    Mat sharpeningOfLaplace4;
    Mat edgeDetection;
    Mat histImage;

public:
    QImage MatToQImage(const cv::Mat& mat);    // MAT类型 转为 QImage类型
    void display_MatInQT(QLabel* label, cv::Mat mat);    // MAT 对象用 QT显示

//槽函数声明
private slots:
    // 打开文件
    void on_action_openFile_triggered();

    // 保存文件
    void on_action_savaFile_triggered();

    // 关闭文件
    void on_action_quitFile_triggered();

    // 灰度化
    void on_action_grayscale_triggered();

    // 二值化
    void on_action_binarization_triggered();

    // 3×3 均值滤波
    void on_action_3x3meanFiltering_triggered();

    // 3×3 中值滤波
    void on_action_3x3medianFiltering_triggered();

    // 拉普拉斯 4 领域锐化
    void on_action_sharpeningOfLaplace4_triggered();

    // 边缘检测
    void on_action_edgaDetection_triggered();

    // 直方图计算与显示
    void on_action_histogramCalculationAndDisplay_triggered();

    // 撤销处理
    void on_action_undoProcessing_triggered();

    //灰度阈值变换，打开新的窗口
    void threshold_open();

    //灰度窗口变换，打开新的窗口
    void windowchange_open();

    //灰度拉伸，打开新的窗口
    void grayScale_open();

    //直方图均衡化，打开新的窗口
    void histogram_open();

    //滤镜，打开新的窗口
    void Filter_open();

    //图像集合变换，打开新的窗口
    void TSR_open();

    //图像风格化，打开新的窗口
    void FGH_open();

    //应用，打开新的窗口
    void YY_open();

    //交换结果图像
    void MatSwap(cv::Mat a, cv::Mat b);
};