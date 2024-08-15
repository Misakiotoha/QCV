#pragma execution_character_set("utf-8")    //设置编码
#include <QtWidgets>
#include "DIPCD_DengLei.h"
#include <QMessageBox>
#include "ThresholdClass.h"
#include "WindowChangeClass.h"
#include "grayScaleClass.h"
#include "histogramClass.h"
#include "FilterClass.h"
#include "TRSClass.h"
#include "CuteClass.h"
#include "AllUseClass.h"
using namespace std;

DIPCD_DengLei::DIPCD_DengLei(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::DIPCD_DengLeiClass)
{
    ui->setupUi(this);
    ui->action_openFile->setEnabled(true);
    ui->action_savaFile->setEnabled(false);
    ui->action_quitFile->setEnabled(false);
    ui->action_grayscale->setEnabled(false);
    ui->action_binarization->setEnabled(false);
    ui->action_3x3meanFiltering->setEnabled(false);
    ui->action_3x3medianFiltering->setEnabled(false);
    ui->action_sharpeningOfLaplace4->setEnabled(false);
    ui->action_edgaDetection->setEnabled(false);
    ui->action_histogramCalculationAndDisplay->setEnabled(false);
    ui->action_undoProcessing->setEnabled(false);
    ui->hdyzbh_action->setEnabled(false);
    ui->hddckbh_action->setEnabled(false);
    ui->grayScaleaction->setEnabled(false);
    ui->histogramaction->setEnabled(false);
    ui->Filteraction->setEnabled(false);
    ui->TSRaction->setEnabled(false);
    ui->FGHaction->setEnabled(false);
    ui->yyaction->setEnabled(false);
    // 设置窗口标题
    setWindowTitle("图像处理");

    // 给显示的窗口设置图标
    setWindowIcon(QIcon(".\\Resource Files\\图像处理.ico"));
    /*setWindowIcon(QIcon(".\\Resource Files\\大户爱.ico"));*/

//连接槽
    //灰度阈值变换窗口
    connect(ui->hdyzbh_action,&QAction::triggered,this,&DIPCD_DengLei::threshold_open);

    //灰度的窗口变换
    connect(ui->hddckbh_action, &QAction::triggered, this, &DIPCD_DengLei::windowchange_open);

    //灰度拉伸
    connect(ui->grayScaleaction, &QAction::triggered, this, &DIPCD_DengLei::grayScale_open);

    //直方图均衡化
    connect(ui->histogramaction, &QAction::triggered, this, &DIPCD_DengLei::histogram_open);

    //滤镜
    connect(ui->Filteraction, &QAction::triggered, this, &DIPCD_DengLei::Filter_open);

    //图像几何变换
    connect(ui->TSRaction, &QAction::triggered, this, &DIPCD_DengLei::TSR_open);

    //图像风格化
    connect(ui->FGHaction, &QAction::triggered, this, &DIPCD_DengLei::FGH_open);

    //应用
    connect(ui->yyaction, &QAction::triggered, this, &DIPCD_DengLei::YY_open);

    // 退出
    connect(ui->action_quit, &QAction::triggered, this, &DIPCD_DengLei::close);

}

DIPCD_DengLei::~DIPCD_DengLei()
{
    delete ui;
}

// MAT类型 转为 QImage类型
QImage DIPCD_DengLei::MatToQImage(const cv::Mat& mat)
{
    // 8 位无符号，信道数 = 1
    if (mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);

        // 设置颜色表（用于将颜色索引转换为 q Rgb值）
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }

        // 复制输入 Mat
        uchar* pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++)
        {
            uchar* pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }

    // 8 位无符号，信道数 = 3
    else if (mat.type() == CV_8UC3)
    {
        // 复制输入 Mat
        const uchar* pSrc = (const uchar*)mat.data;

        // 创建与输入 Mat 尺寸相同的 QImage
        QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if (mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        // 复制输入 Mat
        const uchar* pSrc = (const uchar*)mat.data;

        // 创建与输入 Mat 尺寸相同的 QImage
        QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        //qDebug() << "错误：Mat 无法转换为 QImage.";
        return QImage();
    }
}

// MAT 对象用 QT显示
void DIPCD_DengLei::display_MatInQT(QLabel* label, Mat mat)
{
    label->setPixmap(QPixmap::fromImage(MatToQImage(mat)).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// 打开文件
void DIPCD_DengLei::on_action_openFile_triggered()
{    // 调用窗口打开文件
    ui->label_showOriginalImage->clear();
    ui->label_showProcessImage->clear();
    QString filename =
        QFileDialog::getOpenFileName(this, tr("打开图像"),
            ".",
            tr("Image file(*.png *.jpg *.bmp)"));

    image = imread(filename.toLocal8Bit().data());
    if (image.data)
    {
        //如果加载了图像就让对应的按钮可以使用
        ui->action_savaFile->setEnabled(true);
        ui->action_quitFile->setEnabled(true);
        ui->action_grayscale->setEnabled(true);
        ui->action_binarization->setEnabled(true);
        ui->action_3x3meanFiltering->setEnabled(true);
        ui->action_3x3medianFiltering->setEnabled(true);
        ui->action_sharpeningOfLaplace4->setEnabled(true);
        ui->action_edgaDetection->setEnabled(true);
        ui->action_histogramCalculationAndDisplay->setEnabled(true);
        ui->action_undoProcessing->setEnabled(true);
        ui->hdyzbh_action->setEnabled(true);
        ui->hddckbh_action->setEnabled(true);
        ui->grayScaleaction->setEnabled(true);
        ui->histogramaction->setEnabled(true);
        ui->Filteraction->setEnabled(true);
        ui->TSRaction->setEnabled(true);
        ui->FGHaction->setEnabled(true);
        ui->yyaction->setEnabled(true);
        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
    }
}

// 保存文件
void DIPCD_DengLei::on_action_savaFile_triggered()
{
    if (image.data)
    {
        QString savePath;
        savePath = QFileDialog::getSaveFileName(0, "请选择图片保存路径", ".\\Image Files", "jpg(*.jpg);;png(*.png);;bmp(*.bmp);;所有文件(*.*)");

        if ((!savePath.isNull()) || (!savePath.isEmpty()))
        {
            const QPixmap& saveImgage = *ui->label_showProcessImage->pixmap();
            saveImgage.save(savePath);

            QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
            QMessageBox message(QMessageBox::Information, tr("提示"), tr("保存图片成功！"));
            message.setWindowIcon(*icon);
            QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
            message.exec();
        }
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("保存图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 关闭文件
void DIPCD_DengLei::on_action_quitFile_triggered()
{
    if (image.data)
    {
        ui->action_savaFile->setEnabled(false);
        ui->action_grayscale->setEnabled(false);
        ui->action_binarization->setEnabled(false);
        ui->action_3x3meanFiltering->setEnabled(false);
        ui->action_3x3medianFiltering->setEnabled(false);
        ui->action_sharpeningOfLaplace4->setEnabled(false);
        ui->action_edgaDetection->setEnabled(false);
        ui->action_histogramCalculationAndDisplay->setEnabled(false);
        ui->action_undoProcessing->setEnabled(false);

        ui->label_showOriginalImage->clear();
        ui->label_showProcessImage->clear();

        image.release();
        gray.release();
        binary.release();
        meanFiltering3x3.release();
        medianFiltering3x3.release();
        sharpeningOfLaplace4.release();
        edgeDetection.release();
    }
}

// 灰度化
void DIPCD_DengLei::on_action_grayscale_triggered()
{
    ui->label_showProcessImage->clear();

    if (image.data)
    {
        // 灰度化
        cvtColor(image, gray, COLOR_BGR2GRAY);
        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, gray);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 二值化
void DIPCD_DengLei::on_action_binarization_triggered()
{
    ui->label_showProcessImage->clear();

    if (image.data)
    {
        // 获取 int 类型 阈值数据
        int thresholdValue = 0;

        QInputDialog* inputDialog = new QInputDialog(this);
        inputDialog->setOkButtonText(tr("确定"));
        inputDialog->setCancelButtonText(tr("取消"));

        thresholdValue = inputDialog->getInt(this, "提示", "请输入图片二值化的阈值：（范围为 0 ~ 255 之间）", 155, 0, 255, 1);

        // 二值化
        threshold(image, binary, thresholdValue, 255, THRESH_BINARY_INV);

        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, binary);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 3×3 均值滤波
void DIPCD_DengLei::on_action_3x3meanFiltering_triggered()
{
    ui->label_showProcessImage->clear();

    if (image.data)
    {
        // 3×3 均值滤波
        blur(image, meanFiltering3x3, Size(3, 3));
        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, meanFiltering3x3);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 3×3 中值滤波
void DIPCD_DengLei::on_action_3x3medianFiltering_triggered()
{
    ui->label_showProcessImage->clear();

    if (image.data)
    {
        // 3×3 中值滤波
        medianBlur(image, medianFiltering3x3, 3);
        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, medianFiltering3x3);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 拉普拉斯 4 领域锐化
void DIPCD_DengLei::on_action_sharpeningOfLaplace4_triggered()
{
    ui->label_showProcessImage->clear();

    if (image.data)
    {
        // 拉普拉斯 4 领域锐化
        Laplacian(image, sharpeningOfLaplace4, CV_16S, 1, 1, 0, BORDER_DEFAULT);
        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, sharpeningOfLaplace4);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 边缘检测
void DIPCD_DengLei::on_action_edgaDetection_triggered()
{
    ui->label_showProcessImage->clear();

    if (image.data)
    {
        // 边缘检测
        Canny(image, edgeDetection, 150, 100, 3);
        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, edgeDetection);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 直方图计算与显示
void DIPCD_DengLei::on_action_histogramCalculationAndDisplay_triggered()
{
    Mat src, dst;
    src = image;

    if (image.data)
    {
        // 将多通道图像分为单通道图像
        // 单通道图像 vector
        std::vector<Mat> bgr_planes;
        split(src, bgr_planes);

        // 直方图参数
        int histSize = 256;
        float range[] = {0, 256};
        const float* histRanges = {range};
        Mat b_hist, g_hist, r_hist;

        // 求出直方图的数据
        calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize,
            &histRanges, true, false);
        calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize,
            &histRanges, true, false);
        calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize,
            &histRanges, true, false);

        // 画出直方图
        int hist_h = 400;
        int hist_w = 512;
        int bin_w = hist_w / histSize;    // 直方图的步数

        Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

        // 将数据归一化到直方图的图像尺寸中来
        normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
        normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
        normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

        // 0-255 的像素值，画出每个像素值的连线
        //注意：图像中的坐标是以左上角为原点向右下方延伸
        for (int i = 1; i < histSize; ++i)
        {
            line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
                Point(i * bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
            line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
                Point(i * bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);
            line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
                Point(i * bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);
        }

        // 通过 label 方式显示图片
        display_MatInQT(ui->label_showOriginalImage, image);
        display_MatInQT(ui->label_showProcessImage, histImage);
    }
    else
    {
        QIcon* icon = new QIcon(".\\Resource Files\\大户爱.ico");
        QMessageBox message(QMessageBox::Information, tr("提示"), tr("处理图片失败！"));
        message.setWindowIcon(*icon);
        QPushButton* okbutton = (message.addButton(tr("确定"), QMessageBox::AcceptRole));
        message.exec();
    }
}

// 撤销处理
void DIPCD_DengLei::on_action_undoProcessing_triggered()
{
    if (image.data)
    {
        ui->label_showProcessImage->clear();
    }
}

//灰度阈值变换
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::threshold_open()
{
    //新建一个窗口，并传入当前的image对象
    ThresholdClass* thc = new ThresholdClass(this->image);
    thc->show();
}

//灰度的窗口变换
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::windowchange_open()
{
    //新建一个窗口，并传入当前的image对象
    WindowChangeClass* wcc = new WindowChangeClass(this->image);
    wcc->show();
}



//灰度拉伸
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::grayScale_open()
{
    grayScaleClass* gsc = new grayScaleClass(this->image);
    gsc->show();
}

//直方图均衡化
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::histogram_open()
{
    histogramClass* hgc = new histogramClass(this->image);
    hgc->show();
}

//滤镜
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::Filter_open()
{
    FilterClass* fc = new FilterClass(this->image);
    fc->show();
}

//图像集合变换
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::TSR_open()
{
    TRSClass* trs = new TRSClass(this->image);
    trs->show();
}

//图像风格化
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::FGH_open()
{
    CuteClass* cc = new CuteClass(this->image);
    cc->show();
}

//应用
/*
逻辑:
调用对应的构造函数传入需要的图片信息，之后就都由新窗口处理
*/
void DIPCD_DengLei::YY_open()
{
    AllUseClass* auc = new AllUseClass(this->image);
    auc->show();
}

//交换Mat
void DIPCD_DengLei::MatSwap(cv::Mat a,cv::Mat b)
{
    cv::Mat t = a;
    a = b;
    b = t;
}