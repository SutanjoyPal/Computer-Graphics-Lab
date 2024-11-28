/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *workArea;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *radiuslabel;
    QDoubleSpinBox *Radius;
    QPushButton *GenMidPtCircle;
    QPushButton *GenCirclePolar;
    QPushButton *GenBresenhamCircle;
    QPushButton *GenCartCircle;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *minor;
    QLabel *label_5;
    QDoubleSpinBox *major;
    QLabel *label_6;
    QPushButton *PolarEllipse;
    QPushButton *GenEllipseBre;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *showAxis;
    QLabel *label_4;
    QSpinBox *axisWidth;
    QLabel *label_3;
    QSpinBox *gridOffset;
    QPushButton *gridlines;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *x_coordinate;
    QLabel *label_2;
    QLabel *y_coordinate;
    QPushButton *store;
    QPushButton *reset;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BresenhamLineDraw;
    QLabel *DDA_TIME;
    QPushButton *DDADraw;
    QLabel *Bresenham_Time;
    QPushButton *DrawPolygon;
    QSpinBox *polygonSideCount;
    QPushButton *Scanline;
    QPushButton *FloodFill4;
    QRadioButton *FourNeighbour;
    QRadioButton *EightNeighbour;
    QPushButton *boundaryFill;
    QPushButton *zoomOut;
    QPushButton *zoomIn;
    QLCDNumber *timetaken;
    QLabel *TimeMessage;
    QLabel *label_7;
    QCheckBox *ThickEdges;
    QPushButton *ReflectX;
    QPushButton *ReflectY;
    QPushButton *ReflectO;
    QSpinBox *translateX;
    QSpinBox *translateY;
    QPushButton *translate;
    QDoubleSpinBox *rotateAngle;
    QPushButton *rotateOrigin;
    QPushButton *shear;
    QPushButton *Scale;
    QDoubleSpinBox *shearX;
    QDoubleSpinBox *shearY;
    QPushButton *Rotate;
    QPushButton *scale;
    QPushButton *Reflect;
    QPushButton *SutherCohen;
    QPushButton *Window;
    QPushButton *LiangBarsky;
    QLabel *ClipMsg;
    QPushButton *SutherLandhodgeMan;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1499, 1076);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        workArea = new QLabel(centralwidget);
        workArea->setObjectName("workArea");
        workArea->setGeometry(QRect(20, 20, 731, 631));
        workArea->setFrameShape(QFrame::Shape::Box);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(770, 160, 251, 291));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 29, 231, 251));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radiuslabel = new QLabel(layoutWidget);
        radiuslabel->setObjectName("radiuslabel");
        QFont font;
        font.setPointSize(12);
        radiuslabel->setFont(font);

        verticalLayout->addWidget(radiuslabel);

        Radius = new QDoubleSpinBox(layoutWidget);
        Radius->setObjectName("Radius");

        verticalLayout->addWidget(Radius);

        GenMidPtCircle = new QPushButton(layoutWidget);
        GenMidPtCircle->setObjectName("GenMidPtCircle");

        verticalLayout->addWidget(GenMidPtCircle);

        GenCirclePolar = new QPushButton(layoutWidget);
        GenCirclePolar->setObjectName("GenCirclePolar");

        verticalLayout->addWidget(GenCirclePolar);

        GenBresenhamCircle = new QPushButton(layoutWidget);
        GenBresenhamCircle->setObjectName("GenBresenhamCircle");

        verticalLayout->addWidget(GenBresenhamCircle);

        GenCartCircle = new QPushButton(layoutWidget);
        GenCartCircle->setObjectName("GenCartCircle");

        verticalLayout->addWidget(GenCartCircle);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(1030, 160, 281, 281));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(30, 40, 195, 187));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        minor = new QDoubleSpinBox(layoutWidget1);
        minor->setObjectName("minor");

        verticalLayout_2->addWidget(minor);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        label_5->setFont(font1);

        verticalLayout_2->addWidget(label_5);

        major = new QDoubleSpinBox(layoutWidget1);
        major->setObjectName("major");

        verticalLayout_2->addWidget(major);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName("label_6");
        QFont font2;
        font2.setBold(true);
        label_6->setFont(font2);

        verticalLayout_2->addWidget(label_6);

        PolarEllipse = new QPushButton(layoutWidget1);
        PolarEllipse->setObjectName("PolarEllipse");

        verticalLayout_2->addWidget(PolarEllipse);

        GenEllipseBre = new QPushButton(layoutWidget1);
        GenEllipseBre->setObjectName("GenEllipseBre");

        verticalLayout_2->addWidget(GenEllipseBre);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(760, 60, 460, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        showAxis = new QPushButton(layoutWidget2);
        showAxis->setObjectName("showAxis");

        horizontalLayout->addWidget(showAxis);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        horizontalLayout->addWidget(label_4);

        axisWidth = new QSpinBox(layoutWidget2);
        axisWidth->setObjectName("axisWidth");
        axisWidth->setMinimum(1);

        horizontalLayout->addWidget(axisWidth);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        gridOffset = new QSpinBox(layoutWidget2);
        gridOffset->setObjectName("gridOffset");
        gridOffset->setMinimum(0);
        gridOffset->setSingleStep(10);

        horizontalLayout->addWidget(gridOffset);

        gridlines = new QPushButton(layoutWidget2);
        gridlines->setObjectName("gridlines");

        horizontalLayout->addWidget(gridlines);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(770, 20, 498, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget3);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        x_coordinate = new QLabel(layoutWidget3);
        x_coordinate->setObjectName("x_coordinate");
        x_coordinate->setMinimumSize(QSize(50, 0));
        x_coordinate->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_2->addWidget(x_coordinate);

        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        y_coordinate = new QLabel(layoutWidget3);
        y_coordinate->setObjectName("y_coordinate");
        y_coordinate->setMinimumSize(QSize(50, 0));
        y_coordinate->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_2->addWidget(y_coordinate);

        store = new QPushButton(layoutWidget3);
        store->setObjectName("store");

        horizontalLayout_2->addWidget(store);

        reset = new QPushButton(layoutWidget3);
        reset->setObjectName("reset");

        horizontalLayout_2->addWidget(reset);

        layoutWidget4 = new QWidget(centralwidget);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(760, 100, 536, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        BresenhamLineDraw = new QPushButton(layoutWidget4);
        BresenhamLineDraw->setObjectName("BresenhamLineDraw");

        horizontalLayout_3->addWidget(BresenhamLineDraw);

        DDA_TIME = new QLabel(layoutWidget4);
        DDA_TIME->setObjectName("DDA_TIME");
        DDA_TIME->setMinimumSize(QSize(100, 0));
        DDA_TIME->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(DDA_TIME);

        DDADraw = new QPushButton(layoutWidget4);
        DDADraw->setObjectName("DDADraw");

        horizontalLayout_3->addWidget(DDADraw);

        Bresenham_Time = new QLabel(layoutWidget4);
        Bresenham_Time->setObjectName("Bresenham_Time");
        Bresenham_Time->setMinimumSize(QSize(100, 0));
        Bresenham_Time->setFrameShape(QFrame::Shape::Box);

        horizontalLayout_3->addWidget(Bresenham_Time);

        DrawPolygon = new QPushButton(centralwidget);
        DrawPolygon->setObjectName("DrawPolygon");
        DrawPolygon->setGeometry(QRect(770, 450, 131, 29));
        polygonSideCount = new QSpinBox(centralwidget);
        polygonSideCount->setObjectName("polygonSideCount");
        polygonSideCount->setGeometry(QRect(930, 450, 42, 26));
        Scanline = new QPushButton(centralwidget);
        Scanline->setObjectName("Scanline");
        Scanline->setGeometry(QRect(770, 490, 131, 29));
        FloodFill4 = new QPushButton(centralwidget);
        FloodFill4->setObjectName("FloodFill4");
        FloodFill4->setGeometry(QRect(770, 530, 131, 29));
        FourNeighbour = new QRadioButton(centralwidget);
        FourNeighbour->setObjectName("FourNeighbour");
        FourNeighbour->setGeometry(QRect(910, 530, 110, 24));
        EightNeighbour = new QRadioButton(centralwidget);
        EightNeighbour->setObjectName("EightNeighbour");
        EightNeighbour->setGeometry(QRect(910, 570, 110, 24));
        boundaryFill = new QPushButton(centralwidget);
        boundaryFill->setObjectName("boundaryFill");
        boundaryFill->setGeometry(QRect(770, 570, 131, 29));
        zoomOut = new QPushButton(centralwidget);
        zoomOut->setObjectName("zoomOut");
        zoomOut->setGeometry(QRect(1030, 450, 93, 29));
        zoomIn = new QPushButton(centralwidget);
        zoomIn->setObjectName("zoomIn");
        zoomIn->setGeometry(QRect(1030, 490, 93, 29));
        timetaken = new QLCDNumber(centralwidget);
        timetaken->setObjectName("timetaken");
        timetaken->setGeometry(QRect(970, 610, 191, 41));
        TimeMessage = new QLabel(centralwidget);
        TimeMessage->setObjectName("TimeMessage");
        TimeMessage->setGeometry(QRect(770, 660, 591, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font3.setPointSize(9);
        font3.setBold(true);
        TimeMessage->setFont(font3);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(770, 610, 191, 41));
        ThickEdges = new QCheckBox(centralwidget);
        ThickEdges->setObjectName("ThickEdges");
        ThickEdges->setGeometry(QRect(910, 490, 111, 24));
        ReflectX = new QPushButton(centralwidget);
        ReflectX->setObjectName("ReflectX");
        ReflectX->setGeometry(QRect(1130, 450, 141, 29));
        ReflectY = new QPushButton(centralwidget);
        ReflectY->setObjectName("ReflectY");
        ReflectY->setGeometry(QRect(1140, 490, 131, 29));
        ReflectO = new QPushButton(centralwidget);
        ReflectO->setObjectName("ReflectO");
        ReflectO->setGeometry(QRect(1270, 450, 141, 29));
        translateX = new QSpinBox(centralwidget);
        translateX->setObjectName("translateX");
        translateX->setGeometry(QRect(1030, 530, 31, 26));
        translateX->setMinimum(-1000000);
        translateX->setMaximum(1000000);
        translateY = new QSpinBox(centralwidget);
        translateY->setObjectName("translateY");
        translateY->setGeometry(QRect(1110, 530, 31, 26));
        translateY->setMinimum(-1000000);
        translateY->setMaximum(1000000);
        translate = new QPushButton(centralwidget);
        translate->setObjectName("translate");
        translate->setGeometry(QRect(1192, 530, 81, 29));
        rotateAngle = new QDoubleSpinBox(centralwidget);
        rotateAngle->setObjectName("rotateAngle");
        rotateAngle->setGeometry(QRect(1030, 570, 62, 26));
        rotateAngle->setMinimum(-1000000.000000000000000);
        rotateAngle->setMaximum(1000000.000000000000000);
        rotateOrigin = new QPushButton(centralwidget);
        rotateOrigin->setObjectName("rotateOrigin");
        rotateOrigin->setGeometry(QRect(1130, 570, 141, 29));
        shear = new QPushButton(centralwidget);
        shear->setObjectName("shear");
        shear->setGeometry(QRect(1280, 530, 93, 29));
        Scale = new QPushButton(centralwidget);
        Scale->setObjectName("Scale");
        Scale->setGeometry(QRect(1300, 570, 151, 29));
        shearX = new QDoubleSpinBox(centralwidget);
        shearX->setObjectName("shearX");
        shearX->setGeometry(QRect(1280, 500, 62, 26));
        shearX->setMinimum(-1000000.000000000000000);
        shearX->setMaximum(1000000.000000000000000);
        shearY = new QDoubleSpinBox(centralwidget);
        shearY->setObjectName("shearY");
        shearY->setGeometry(QRect(1390, 500, 62, 26));
        shearY->setMinimum(-1000000.000000000000000);
        shearY->setMaximum(1000000.000000000000000);
        Rotate = new QPushButton(centralwidget);
        Rotate->setObjectName("Rotate");
        Rotate->setGeometry(QRect(1180, 610, 93, 29));
        scale = new QPushButton(centralwidget);
        scale->setObjectName("scale");
        scale->setGeometry(QRect(1300, 610, 93, 29));
        Reflect = new QPushButton(centralwidget);
        Reflect->setObjectName("Reflect");
        Reflect->setGeometry(QRect(1180, 660, 93, 29));
        SutherCohen = new QPushButton(centralwidget);
        SutherCohen->setObjectName("SutherCohen");
        SutherCohen->setGeometry(QRect(880, 730, 93, 29));
        Window = new QPushButton(centralwidget);
        Window->setObjectName("Window");
        Window->setGeometry(QRect(770, 730, 93, 29));
        LiangBarsky = new QPushButton(centralwidget);
        LiangBarsky->setObjectName("LiangBarsky");
        LiangBarsky->setGeometry(QRect(1000, 730, 93, 29));
        ClipMsg = new QLabel(centralwidget);
        ClipMsg->setObjectName("ClipMsg");
        ClipMsg->setGeometry(QRect(20, 670, 401, 41));
        SutherLandhodgeMan = new QPushButton(centralwidget);
        SutherLandhodgeMan->setObjectName("SutherLandhodgeMan");
        SutherLandhodgeMan->setGeometry(QRect(600, 730, 121, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1499, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        workArea->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "CIRCLE", nullptr));
        radiuslabel->setText(QCoreApplication::translate("MainWindow", "Radius", nullptr));
        GenMidPtCircle->setText(QCoreApplication::translate("MainWindow", "Generate Circle MidPoint", nullptr));
        GenCirclePolar->setText(QCoreApplication::translate("MainWindow", "Generate Circle Polar", nullptr));
        GenBresenhamCircle->setText(QCoreApplication::translate("MainWindow", "Generate Circle Bresenham", nullptr));
        GenCartCircle->setText(QCoreApplication::translate("MainWindow", "Generate Cartesian Circle", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Semi Minor Axis", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Semi Major Axis", nullptr));
        PolarEllipse->setText(QCoreApplication::translate("MainWindow", "Generate Ellipse Polar", nullptr));
        GenEllipseBre->setText(QCoreApplication::translate("MainWindow", "Generate Ellipse Bresenham", nullptr));
        showAxis->setText(QCoreApplication::translate("MainWindow", "Show Axes", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Axis Width", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "GridOffset", nullptr));
        gridlines->setText(QCoreApplication::translate("MainWindow", "Show Gridlines", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X Coordinate", nullptr));
        x_coordinate->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Y Coordinate", nullptr));
        y_coordinate->setText(QString());
        store->setText(QCoreApplication::translate("MainWindow", "Store Canvas", nullptr));
        reset->setText(QCoreApplication::translate("MainWindow", "Erase Canvas", nullptr));
        BresenhamLineDraw->setText(QCoreApplication::translate("MainWindow", "Generate Bresenham Line", nullptr));
        DDA_TIME->setText(QString());
        DDADraw->setText(QCoreApplication::translate("MainWindow", "Generate DDA Line", nullptr));
        Bresenham_Time->setText(QString());
        DrawPolygon->setText(QCoreApplication::translate("MainWindow", "Draw Polygon", nullptr));
        Scanline->setText(QCoreApplication::translate("MainWindow", "Scanline Fill", nullptr));
        FloodFill4->setText(QCoreApplication::translate("MainWindow", "Flood Fill", nullptr));
        FourNeighbour->setText(QCoreApplication::translate("MainWindow", "4 Neighbour", nullptr));
        EightNeighbour->setText(QCoreApplication::translate("MainWindow", "8 Neighbour", nullptr));
        boundaryFill->setText(QCoreApplication::translate("MainWindow", "Boundary Fill", nullptr));
        zoomOut->setText(QCoreApplication::translate("MainWindow", "Zoom Out", nullptr));
        zoomIn->setText(QCoreApplication::translate("MainWindow", "Zoom In", nullptr));
        TimeMessage->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Time taken in nanoseconds:", nullptr));
        ThickEdges->setText(QCoreApplication::translate("MainWindow", "Thick Edges", nullptr));
        ReflectX->setText(QCoreApplication::translate("MainWindow", "Reflect w.r.t. x-axis", nullptr));
        ReflectY->setText(QCoreApplication::translate("MainWindow", "Reflect w.r.t y-axis", nullptr));
        ReflectO->setText(QCoreApplication::translate("MainWindow", "Reflect w.r.t origin", nullptr));
        translate->setText(QCoreApplication::translate("MainWindow", "Translate", nullptr));
        rotateOrigin->setText(QCoreApplication::translate("MainWindow", "Rotate w.r.t origin", nullptr));
        shear->setText(QCoreApplication::translate("MainWindow", "Shear", nullptr));
        Scale->setText(QCoreApplication::translate("MainWindow", "Scale w.r.t. origin", nullptr));
        Rotate->setText(QCoreApplication::translate("MainWindow", "Rotate ", nullptr));
        scale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        Reflect->setText(QCoreApplication::translate("MainWindow", "Reflect", nullptr));
        SutherCohen->setText(QCoreApplication::translate("MainWindow", "SC Line Clip", nullptr));
        Window->setText(QCoreApplication::translate("MainWindow", "Window", nullptr));
        LiangBarsky->setText(QCoreApplication::translate("MainWindow", "LB Line Clip", nullptr));
        ClipMsg->setText(QString());
        SutherLandhodgeMan->setText(QCoreApplication::translate("MainWindow", "SH Polgon Clip", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
