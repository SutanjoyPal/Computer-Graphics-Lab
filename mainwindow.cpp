#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QTimer>
#include <QMouseEvent>
#include<set>
#include <QSet>
#include<QPair>
#include <QImage>
#include <QColor>
#include <QPoint>

#define Delay delay(1)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->workArea->setMouseTracking(true);
    ui->workArea->installEventFilter(this);

    QPixmap canvas = ui->workArea->pixmap(Qt::ReturnByValue);
    if (canvas.isNull()) {
        clear_screen();
    }
    width = ui->workArea->width();
    height = ui->workArea->height();
    centerX = width / 2;
    centerY = height / 2;

    initializeColorPalette();
}

void MainWindow::initializeColorPalette()
{
    colorPalette["red"] = QColor(255, 0, 0);
    colorPalette["yellow"] = QColor(255, 255, 0);
    colorPalette["green"] = QColor(0, 255, 0);
    colorPalette["blue"] = QColor(0, 0, 255);
    colorPalette["cyan"] = QColor(0, 255, 255);
    colorPalette["magenta"] = QColor(255, 0, 255);
    colorPalette["black"] = QColor(0, 0, 0);
    colorPalette["white"] = QColor(255, 255, 255);
    colorPalette["gray"] = QColor(128, 128, 128);
    colorPalette["darkGray"] = QColor(64, 64, 64);
    colorPalette["lightGray"] = QColor(192, 192, 192);
    colorPalette["orange"] = QColor(255, 165, 0);
    colorPalette["purple"] = QColor(128, 0, 128);
    colorPalette["brown"] = QColor(165, 42, 42);
    colorPalette["pink"] = QColor(255, 192, 203);
    colorPalette["lime"] = QColor(0, 255, 0);
    colorPalette["navy"] = QColor(0, 0, 128);
    colorPalette["maroon"] = QColor(128, 0, 0);
    colorPalette["olive"] = QColor(128, 128, 0);
    colorPalette["teal"] = QColor(0, 128, 128);
    colorPalette["gold"] = QColor(255, 215, 0);
    colorPalette["silver"] = QColor(192, 192, 192);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::delay(int ms){
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::colorPoint(int x, int y, int r, int g, int b, int penwidth=1) {
    QPixmap canvas=ui->workArea->pixmap();
    QPainter painter(&canvas);
    QPen pen=QPen(QColor(r,g,b),penwidth);
    painter.setPen(pen);
    painter.drawPoint(x, y);
    ui->workArea->setPixmap(canvas);
    QPoint pt = reverse_point_transform(x,y);
    //qDebug()<<"Point Coloured: "<<pt.x()<<"  "<<pt.y();
    colorMap[{pt.x(),pt.y()}] = QColor(r,g,b);
}

void MainWindow::colorPoint(QPoint curPt, QColor color, int penwidth=1) {
    penwidth=unitDistance;
    QPixmap canvas=ui->workArea->pixmap();
    QPainter painter(&canvas);
    QPen pen=QPen(color,penwidth);
    painter.setPen(pen);
    QPoint pt = point_transform(curPt);
    painter.drawPoint(pt.x(), pt.y());
    ui->workArea->setPixmap(canvas);
    qDebug()<<"Point Coloured: "<<curPt.x()<<"  "<<curPt.y();
    colorMap[{curPt.x(),curPt.y()}] = color;
}

void MainWindow::on_showAxis_clicked() {
    int axisWidth=ui->axisWidth->value();
    // Draw horizontal axis
    for (int x = 0; x < width; ++x) {
        colorPoint(x, centerY, 255, 0, 0, axisWidth);
    }

    // Draw vertical axis
    for (int y = 0; y < height; ++y) {
        colorPoint(centerX, y, 255, 0, 0, axisWidth);
    }
}

void MainWindow::draw_gridlines(int unitDistance){
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    if (unitDistance <= 0) return; // Prevent invalid grid offset

    int centerX=width/2;
    int centerY=height/2;
    QPixmap canvas=ui->workArea->pixmap();
    QPainter painter(&canvas);
    for(int i =  unitDistance; (centerX+i<width && centerX-i>0) || (centerY+i<height && centerY-i>0); i+= unitDistance)
    {
        QPoint qp1 = QPoint(centerX + i, 0);
        QPoint qp2 = QPoint(centerX + i, height);
        QPoint qp3 = QPoint(centerX - i, 0);
        QPoint qp4 = QPoint(centerX - i, height);

        QPoint qp5 = QPoint(0, centerY + i);
        QPoint qp6 = QPoint(width, centerY + i);
        QPoint qp7 = QPoint(0, centerY-i);
        QPoint qp8 = QPoint(width, centerY - i);
        painter.drawLine(qp1, qp2);
        painter.drawLine(qp3, qp4);
        painter.drawLine(qp5, qp6);
        painter.drawLine(qp7, qp8);
    }

    ui->workArea->setPixmap(canvas);
}

void MainWindow::on_gridlines_clicked() {
    int gridOffset = ui->gridOffset->value();
    unitDistance = gridOffset;
    draw_gridlines(unitDistance);
}



bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->workArea && event->type() == QEvent::MouseMove) {
        QMouseEvent *cursor = static_cast<QMouseEvent*>(event);
        int x = cursor->pos().x();
        int y = cursor->pos().y();
        //int gridOffset = (ui->gridOffset->value()==0)?1:ui->gridOffset->value();
        ui->x_coordinate->setText(QString::number(floor((x-centerX)*1.0/unitDistance)));
        ui->y_coordinate->setText(QString::number(floor((centerY-y)*1.0/unitDistance)));
        return true; // Event handled
    }
    if(watched == ui->workArea && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *cursor = static_cast<QMouseEvent*>(event);
        int x = cursor->pos().x();
        int y = cursor->pos().y();
        clickedPoint.setX(x);
        clickedPoint.setY(y);
        int X = floor((x-centerX)*1.0/unitDistance);
        int Y = floor((centerY-y)*1.0/unitDistance);
        qDebug()<<"Point Clicked: "<<X<<" "<<Y;
        QPoint curPt = QPoint(X,Y);
        points.push_back(curPt);
        //QPoint pt = point_transform(X,Y);
        colorPoint(curPt,colorPalette["yellow"]);

    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::clear_screen(){
    QPixmap canvas = ui->workArea->pixmap(Qt::ReturnByValue);
    canvas = QPixmap(ui->workArea->size());
    canvas.fill(Qt::white);
    ui->workArea->setPixmap(canvas);
}

QPoint MainWindow:: point_transform(int x,int y){
    float x_float = centerX + x * unitDistance + unitDistance / 2.0;
    float y_float = centerY - y * unitDistance - unitDistance / 2.0;
    int xn = static_cast<int>(x_float);
    int yn = static_cast<int>(y_float);
    return QPoint(xn,yn);
}

QPoint MainWindow:: point_transform(QPoint pt){
    float x_float = centerX + pt.x() * unitDistance + unitDistance / 2.0;
    float y_float = centerY - pt.y() * unitDistance - unitDistance / 2.0;
    int xn = static_cast<int>(x_float);
    int yn = static_cast<int>(y_float);
    return QPoint(xn,yn);
}




























void MainWindow::on_reset_clicked()
{
    clear_screen();
    points.clear();
}

void MainWindow::on_store_clicked()
{
    temp = ui->workArea->pixmap(Qt::ReturnByValue);
}


float MainWindow::calc_slope(QPoint a,QPoint b){
    float slope;
    if(b.x() == a.x()) return std::numeric_limits<float>::max();
    slope = (b.y()-a.y())/(b.x()-a.x());
    return slope;
}

class MainWindow::myTimer {
    QString algoName;
    QElapsedTimer timer;
    MainWindow* mainWindow; // Add a reference to MainWindow

public:
    myTimer(QString algoName, MainWindow* mainWindow) {
        this->algoName = algoName;
        this->mainWindow = mainWindow;
    }

    void startTimer(){
        timer.start();
    }

    void measureTime() {
        qint64 elapsedTime = timer.nsecsElapsed();
        mainWindow->ui->TimeMessage->setText(QString("Time taken by ")+algoName+QString(" algorithm in nanoseconds"));
        mainWindow->ui->timetaken->display(QString::number(elapsedTime));
    }
};

void MainWindow::draw_line_pts(QVector<QPoint> &linePts,QColor color){
    for(QPoint currentPt : linePts){
        colorPoint(currentPt,color);
    }
}

void MainWindow::generate_dda_linePts(QPoint startPt,QPoint endPt){
    int startX = startPt.x(),startY = startPt.y();
    int endX = endPt.x(),endY = endPt.y();

    int dx = endX-startX,dy = endY-startY;
    int steps = std::max(abs(dx),abs(dy));

    float xinc = (dx*1.0)/steps,yinc = (dy*1.0/steps);
    float curX = startX,curY = startY;

    myTimer t("DDA Line Drawing",this);
    t.startTimer();
    QVector<QPoint> linePts;
    linePts.push_back(startPt);
    while((startX != endX)||(startY!=endY)){
        curX = curX+xinc;
        curY = curY+yinc;
        startX = std::round(curX);
        startY = std::round(curY);
        linePts.push_back(QPoint(startX,startY));
    }
    t.measureTime();
    draw_line_pts(linePts,colorPalette["pink"]);

}

void MainWindow::on_DDADraw_clicked()
{
    if(points.size()< 2 ) return;
    qint64 n  = points.size();
    generate_dda_linePts(points[n-2],points[n-1]);
}


// void MainWindow::generate_bresenham_linePts(QPoint startPt,QPoint endPt){
//     if(startPt.x()>endPt.x()) std::swap(startPt,endPt);

//     int startX = startPt.x(),startY = startPt.y();
//     int endX = endPt.x(),endY = endPt.y();
//     int dx = endX-startX,dy = endY-startY;


//     QVector<QPoint> linePts;
//     // Handle the case where the line is nearly horizontal
//     if (std::abs(dy) < std::abs(dx)) {
//         // Determine the direction of y increment
//         int yStep = (dy > 0) ? 1 : -1;
//         int p = 2 * dy - dx;

//         while (startX <= endX) {
//             linePts.push_back(QPoint(startX, startY));
//             startX++;

//             // Update the decision parameter
//             if (p < 0) {
//                 p += 2 * dy;
//             } else {
//                 startY += yStep;
//                 p += (2 * dy - 2 * dx);
//             }
//         }
//     } else { // Handle the case where the line is nearly vertical
//         // Determine the direction of x increment
//         int xStep = (dx > 0) ? 1 : -1;
//         int p = 2 * dx - dy;

//         while (startY != endY) {
//             linePts.push_back(QPoint(startX, startY));
//             startY += (dy > 0) ? 1 : -1;

//             // Update the decision parameter
//             if (p < 0) {
//                 p += 2 * dx;
//             } else {
//                 startX += xStep;
//                 p += (2 * dx - 2 * dy);
//             }
//         }
//     }
//     draw_line_pts(linePts,colorPalette["maroon"]);
// }

void MainWindow::generate_bresenham_linePts(QPoint startPt, QPoint endPt) {
    // Ensure startPt is to the left of endPt
    if (startPt.x() > endPt.x()) std::swap(startPt, endPt);

    int startX = startPt.x(), startY = startPt.y();
    int endX = endPt.x(), endY = endPt.y();
    int dx = endX - startX;
    int dy = endY - startY;

    QVector<QPoint> linePts;

    // Determine the direction of increments
    int xStep = 1; // Always moving from left to right
    int yStep = (dy > 0) ? 1 : -1; // Determine if y should increment or decrement

    // Handle cases based on slope
    if (std::abs(dy) < std::abs(dx)) { // Gentle slope
        int p = 2 * dy - dx; // Initial decision parameter

        while (startX != endX) {
            linePts.push_back(QPoint(startX, startY));
            startX += xStep; // Move to the next x position

            // Update decision parameter
            if (p < 0) {
                p += 2 * dy; // Stay on the same row
            } else {
                startY += yStep; // Move to the next row (up or down based on slope)
                p += (2 * dy - 2 * dx); // Update for next iteration
            }
        }
    } else { // Steep slope
        int p = 2 * dx - dy; // Initial decision parameter

        while (startY != endY) {
            linePts.push_back(QPoint(startX, startY));
            startY += yStep; // Move to the next y position

            // Update decision parameter
            if (p < 0) {
                p += 2 * dx; // Stay on the same column
            } else {
                startX += xStep; // Move to the next column
                p += (2 * dx - 2 * dy); // Update for next iteration
            }
        }
    }

    // Draw the line points
    draw_line_pts(linePts, colorPalette["maroon"]);
}





void MainWindow::draw_bresenham_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    QVector<QPoint> pts;
    QElapsedTimer timer;
    timer.start();

    int cnt=0;
    while (true) {
        int calcX = centerX + x1 * unitDistance + unitDistance / 2;
        int calcY = centerY - y1 * unitDistance - unitDistance / 2;
        pts.push_back(QPoint(calcX, calcY));
        polygon.insert(QPoint(calcX,calcY));

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
        cnt++;
    }
    qDebug() << cnt;
    qint64 elapsedTime = timer.nsecsElapsed();
    ui->Bresenham_Time->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    for (auto &pt : pts) {
        colorPoint(pt.x(), pt.y(), 153, 255, 153, unitDistance);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(points.size()< 2 ) return;
    qint64 n  = points.size();
    auto coords1 = points[n-1];
    auto coords2 = points[n-2];
    generate_bresenham_linePts(points[n-2],points[n-1]);
}



void MainWindow::draw_polar_circle(int xc,int yc){


    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    float x_float = centerX + xc * unitDistance + unitDistance / 2.0;
    float y_float = centerY - yc * unitDistance - unitDistance / 2.0;


    float r = (ui->Radius->value())*unitDistance;

    QVector<QPoint> pts;
    QElapsedTimer timer;
    timer.start();
    for (int angle = 0; angle < 360; ++angle) {
        double radian = angle * M_PI / 180.0;  // Convert degree to radian
        int x = static_cast<int>(x_float+(r * cos(radian)));
        int y = static_cast<int>(y_float+(r * sin(radian)));

        int X = floor((x-centerX)*1.0/unitDistance);
        int Y = floor((centerY-y)*1.0/unitDistance);
        int calcX = centerX+ X*unitDistance + unitDistance/2;
        int calcY = centerY -  Y*unitDistance - unitDistance/2;
        pts.push_back(QPoint(calcX, calcY));


        //pts.push_back(QPoint(x, y));


    }
    qint64 elapsedTime = timer.nsecsElapsed();
    ui->PolarTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    for(auto &pt:pts){
        qDebug()<<pt.x()<<" "<<pt.y();
        colorPoint(pt.x(), pt.y(), 102, 0, 204, unitDistance);
        delay(1);
    }
}

void MainWindow::EightPtSym(QVector<QPoint> &pts,float x_float,float y_float,int x,int y){
    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;



    int dx[] = {x,-x,x,-x,y,-y,y,-y};
    int dy[] = {y,y,-y,-y,x,x,-x,-x};

    for(int i=0;i<8;++i){
        int xn = static_cast<int>(x_float+dx[i]);
        int yn = static_cast<int>(y_float+dy[i]);
        int X = floor((xn-centerX)*1.0/unitDistance);
        int Y = floor((centerY-yn)*1.0/unitDistance);
        int calcX = centerX+ X*unitDistance + unitDistance/2;
        int calcY = centerY -  Y*unitDistance - unitDistance/2;
        pts.push_back(QPoint(calcX, calcY));
    }
}


void MainWindow::draw_circle_bresenham(int xc,int yc){
    ///int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    float x_float = centerX + xc * unitDistance + unitDistance / 2.0;
    float y_float = centerY - yc * unitDistance - unitDistance / 2.0;

    float r = (ui->Radius->value())*unitDistance;
    QVector<QPoint> pts;

    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    EightPtSym(pts,x_float,y_float,x,y);
    QElapsedTimer timer;
    timer.start();
    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }

        EightPtSym(pts,x_float,y_float,x,y);
    }
    qint64 elapsedTime = timer.nsecsElapsed();
    ui->BresenhamCircleTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    for(auto &pt:pts){
        qDebug()<<pt.x()<<" "<<pt.y();
        colorPoint(pt.x(), pt.y(), 255, 51, 51, unitDistance);
        delay(1);
    }
}

void MainWindow::on_GenCircle_clicked()
{
    qint64 n  = points.size();
    int xc = points[n-1].x();
    int yc = points[n-1].y();
    //draw_polar_circle(xc,yc);
    draw_circle_bresenham(xc,yc);
}




void MainWindow::on_GenCirclePolar_clicked()
{
    qint64 n  = points.size();
    int xc = points[n-1].x();
    int yc = points[n-1].y();
    draw_polar_circle(xc,yc);
}


void MainWindow::on_GenCartCircle_clicked()
{

    qint64 n  = points.size();
    int gx = points[n-1].x();
    int gy = points[n-1].y();


    int offset = unitDistance;
    int w = ui->workArea->width();
    int h = ui->workArea->height();
    int cx = w / 2;
    int cy = h / 2;
    double r = static_cast<int>((ui->Radius->value()));
    int px = cx + gx * offset + offset / 2;
    int py = cy - gy * offset - offset / 2;

    QElapsedTimer t;
    t.start();
    for (double x = 0; x <= r; x++) {
        int y = static_cast<int>(sqrt(r * r - x * x));
        qDebug()<<x<<" "<<y;
        drawCirclePoints(x, y, px, py, 255, 0, 255, unitDistance);
    }

    // qint64 timeMs = t.elapsed();
    // ui->CartTime->setText(QString::number(timeMs) + " ms");
    qint64 elapsedTime = t.nsecsElapsed();
    ui->CartTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

}

void MainWindow::drawCirclePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int unitDistance) {
    colorPoint(pixelCenterX + x * unitDistance, pixelCenterY - y * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX - x * unitDistance, pixelCenterY - y * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX + x * unitDistance, pixelCenterY + y * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX - x * unitDistance, pixelCenterY + y * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX + y * unitDistance, pixelCenterY - x * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX - y * unitDistance, pixelCenterY - x * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX + y * unitDistance, pixelCenterY + x * unitDistance, r, g, b, unitDistance);
    Delay;
    colorPoint(pixelCenterX - y * unitDistance, pixelCenterY + x * unitDistance, r, g, b, unitDistance);
    Delay;
}


void MainWindow::draw_polar_ellipse(QPoint f1, QPoint f2) {
    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    // Convert focus points to pixel coordinates
    float x1 = centerX + f1.x() * unitDistance + unitDistance / 2.0;
    float y1 = centerY - f1.y() * unitDistance - unitDistance / 2.0;
    float x2 = centerX + f2.x() * unitDistance + unitDistance / 2.0;
    float y2 = centerY - f2.y() * unitDistance - unitDistance / 2.0;

    // Calculate the center of the ellipse as the midpoint of the two foci
    float xc = (x1 + x2) / 2.0;
    float yc = (y1 + y2) / 2.0;

    // Fixed semi-major and semi-minor axes
    float a = ui->major->value()*unitDistance;
    float b = ui->minor->value()*unitDistance;

    QVector<QPoint> pts;
    QElapsedTimer timer;
    timer.start();

    // Draw the ellipse using polar coordinates
    for (int angle = 0; angle < 360; ++angle) {
        double radian = angle * M_PI / 180.0; // Convert degrees to radians
        int x = static_cast<int>(xc + a * cos(radian));
        int y = static_cast<int>(yc + b * sin(radian));

        int gridX = floor((x - centerX) * 1.0 / unitDistance);
        int gridY = floor((centerY - y) * 1.0 / unitDistance);
        int calcX = centerX + gridX * unitDistance + unitDistance / 2;
        int calcY = centerY - gridY * unitDistance - unitDistance / 2;
        pts.push_back(QPoint(calcX, calcY));
    }

    qint64 elapsedTime = timer.nsecsElapsed();
    //ui->PolarTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    // Draw each calculated point
    for (auto &pt : pts) {
        qDebug() << pt.x() << " " << pt.y();
        colorPoint(pt.x(), pt.y(), 102, 0, 204, unitDistance);
        delay(1); // Optional delay for visualization
    }
}




void MainWindow::on_PolarEllipse_clicked()
{
    qint64 n  = points.size();
    draw_polar_ellipse(points[n-1],points[n-2]);
}

void MainWindow::drawEllipsePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int unitDistance) {
    // Draw points using 4-point symmetry
    colorPoint(pixelCenterX + x * unitDistance, pixelCenterY - y * unitDistance, r, g, b, unitDistance); // Quadrant 1
    Delay;
    colorPoint(pixelCenterX - x * unitDistance, pixelCenterY - y * unitDistance, r, g, b, unitDistance); // Quadrant 2
    Delay;
    colorPoint(pixelCenterX + x * unitDistance, pixelCenterY + y * unitDistance, r, g, b, unitDistance); // Quadrant 3
    Delay;
    colorPoint(pixelCenterX - x * unitDistance, pixelCenterY + y * unitDistance, r, g, b, unitDistance); // Quadrant 4
    Delay;
}




void MainWindow::on_GenEllipseBre_clicked()
{
    // qint64 n  = points.size();
    // draw_bresenham_ellipse(points[n-1],points[n-2]);
    // Start the timer
    QElapsedTimer timer;
    timer.start();

    // Get the ellipse axes from the QSpinBoxes
    int a = ui->major->value(); // Axis parallel to x-axis
    int b = ui->minor->value(); // Axis parallel to y-axis

    // Get the center of the ellipse from the last clicked point
    if (points.empty()) return;
    int gridCenterX = points.back().x();
    int gridCenterY = points.back().y();

    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    // Convert grid center to actual pixel coordinates
    int pixelCenterX = centerX + gridCenterX * unitDistance + unitDistance / 2;
    int pixelCenterY = centerY - gridCenterY * unitDistance - unitDistance / 2;

    // Store the points in a set to avoid drawing duplicates
    std::set<std::pair<int, int>> ellipsePoints;

    // Bresenham's Midpoint Ellipse Algorithm
    int x = 0, y = b;
    long long a2 = a * a;
    long long b2 = b * b;
    long long d1 = b2 - (a2 * b) + (0.25 * a2);
    long long dx = 2 * b2 * x;
    long long dy = 2 * a2 * y;

    // Region 1
    while (dx < dy) {
        ellipsePoints.insert({x, y});
        if (d1 < 0) {
            x++;
            dx = dx + 2 * b2;
            d1 = d1 + dx + b2;
        } else {
            x++;
            y--;
            dx = dx + 2 * b2;
            dy = dy - 2 * a2;
            d1 = d1 + dx - dy + b2;
        }
    }

    // Region 2
    long long d2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y >= 0) {
        ellipsePoints.insert({x, y});
        if (d2 > 0) {
            y--;
            dy = dy - 2 * a2;
            d2 = d2 + a2 - dy;
        } else {
            y--;
            x++;
            dx = dx + 2 * b2;
            dy = dy - 2 * a2;
            d2 = d2 + dx - dy + a2;
        }
    }

    // Draw the ellipse points using 4-point symmetry
    for (const std::pair<int, int>& p : ellipsePoints) {
        drawEllipsePoints(p.first, p.second, pixelCenterX, pixelCenterY, 170, 170, 170, unitDistance);
    }

}


QVector<QPoint> MainWindow::get_Vertices(){
    int vertexCount = ui->polygonSideCount->value();
    //if(vertexCount < 3) throw "Polygon Not possible";
    //if(vertexCount < points.size()) throw "Insufficient Points";
    qint64 lastIndex = points.size()-1;
    qint64 currentIndex = lastIndex;
    QVector<QPoint> polygonVertices;
    while(vertexCount--){
        polygonVertices.push_back(points[currentIndex]);
        currentIndex--;
    }
    return polygonVertices;
}

void MainWindow::draw_Polgon_Sides(QVector<QPoint> &polygonVertices){
    int vertexCount = polygonVertices.size();
    for(int i=0;i<polygonVertices.size();++i){
        QPoint curVertex = polygonVertices[i];
        QPoint nextVertex = polygonVertices[(i+1)%vertexCount];
        draw_bresenham_line(curVertex.x(),curVertex.y(),nextVertex.x(),nextVertex.y());
    }
}

void MainWindow::make_edges_thicker(){
    // int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    // QSet<QPoint> newPts;
    // for(QPoint vertex : polygon){
    //     QPoint formattedVertex = reverse_point_transform(vertex.x(),vertex.y());
    //     qDebug()<< vertex.x() << "  " << vertex.y();
    //     qDebug()<< formattedVertex.x() << "  " << formattedVertex.y();
    //     QVector<QPoint> neighbours = eight_neighbour(formattedVertex);
    //     for(QPoint neighbour:neighbours){
    //         //QPoint pt = point_transform(neighbour.x(),neighbour.y());
    //         //qDebug() << neighbour.x() << "  " << neighbour.y();
    //         colorPoint(neighbour.x(),neighbour.y(), 153, 255, 153, unitDistance);
    //         newPts.insert(neighbour);
    //     }
    // }
    // for(QPoint pt:newPts){
    //     polygon.insert(pt);
    // }
}

void MainWindow::draw_Polygon(){
    polygon.clear();
    QVector<QPoint> polygonVertices = get_Vertices();
    draw_Polgon_Sides(polygonVertices);
    //make_edges_thicker();
}

void MainWindow::on_DrawPolygon_clicked()
{
    draw_Polygon();
}



QPoint MainWindow::reverse_point_transform(int xn, int yn) {
    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    // Reverse the transformation
    float x_float = (xn - centerX) - unitDistance / 2.0;
    float y_float = (centerY - yn) - unitDistance / 2.0;

    int x = static_cast<int>(x_float / unitDistance);
    int y = static_cast<int>(y_float / unitDistance);

    return QPoint(x, y);
}

void MainWindow::scanline_fill(){
    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    int width = ui->workArea->width();
    int centerX = width / 2;

    for(qint64 row = 30;row >= -31; row--){
        bool fillColor = false;
        int prevCol = -1000;
        QSet<QPoint>::Iterator prevPt=polygon.end();

        for(qint64 col = -36; col <= 35;col++){
            QPoint q = point_transform(col,row);
            int xn = q.x();
            int yn = q.y();
            qDebug()<<col<<" "<<row;
            if(polygon.find(QPoint(xn,yn))!=polygon.end()){
                if((prevCol+1) == col) {prevCol=col;continue;}
                fillColor = !fillColor;
                if((fillColor==false) && (prevCol!=-1000)){
                    for(int i=prevCol+1;i<col;++i){
                        //qDebug()<<i<<" "<<yn;
                        float x_float2 = centerX + i * unitDistance + unitDistance / 2.0;
                        int xn2 = static_cast<int>(x_float2);
                        colorPoint(xn2,yn, 0,0, 250, unitDistance);
                        Delay;
                    }
                }
                prevCol = col;
                prevPt = polygon.find(QPoint(xn,yn));
            }

        }
    }
}

void MainWindow::on_Scanline_clicked()
{
    scanline_fill();
}


QVector<QPoint> MainWindow::four_neighbour(QPoint pt){
    int x = pt.x(),y = pt.y();
    QVector<QPoint> neighbours;

    int drow[] = {+1,0,-1,0};
    int dcol[] = {0,+1,0,-1};

    for(int i=0;i<4;++i){
        neighbours.push_back(QPoint(x+drow[i],y+dcol[i]));
    }

    return neighbours;
}

QVector<QPoint> MainWindow::eight_neighbour(QPoint pt){
    int x = pt.x(),y = pt.y();
    QVector<QPoint> neighbours;

    int drow[] = {+1,0,-1,0,+1,-1,+1,-1};
    int dcol[] = {0,+1,0,-1,+1,-1,-1,+1};

    for(int i=0;i<8;++i){
        neighbours.push_back(QPoint(x+drow[i],y+dcol[i]));
    }

    return neighbours;
}


void MainWindow::flood_fill_rec(QPoint seed,QSet<QPoint> &visited){
    QPoint pt = point_transform(seed.x(),seed.y());

    // if(polygon.find(pt)!=polygon.end()) return;
    // //qDebug()<<"Not in edge";
    // if(visited.find(pt)!=visited.end()) return;
    // visited.insert(pt);
    QColor current_clr = get_Color(pt);

    if(!((current_clr.red()==255) && (current_clr.green()==255) && (current_clr.blue()==0)))
    if((current_clr.red()!=255) || (current_clr.green()!=255) || (current_clr.blue()!=255)) return;

    QVector<QPoint> neighbours;
    if(ui->FourNeighbour->isChecked()){
        neighbours = four_neighbour(seed);
    }
    else neighbours = eight_neighbour(seed);

    //qDebug()<<pt.x()<<" "<<pt.y();
    for(QPoint child:neighbours){
        //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
        colorPoint(pt.x(),pt.y(),250,0,0,unitDistance);
        Delay;
        flood_fill_rec(child,visited);
    }
}




void MainWindow::on_FloodFill4_clicked()
{
    qint64 n = points.size();
    QSet<QPoint> visited;
    flood_fill_rec(points[n-1],visited);
}

QColor MainWindow::get_Color(QPoint pt){
    QImage canvas=ui->workArea->pixmap(Qt::ReturnByValue).toImage();
    QColor clr=canvas.pixelColor(pt.x(),pt.y());
    qDebug()<<pt.x()<<" "<<pt.y();
    qDebug()<<clr.red()<<" "<<clr.green()<<" "<<clr.blue();
    return clr;
}


void MainWindow::boundary_fill_rec(QPoint seed){
    QPoint pt = point_transform(seed.x(),seed.y());

    QColor current_clr = get_Color(pt);
    if((current_clr.red()==153) && (current_clr.green()==255) && (current_clr.blue()==153)) return; //check if boundary color

    if((current_clr.red()==250) && (current_clr.green()==0) && (current_clr.blue()==0)) return; //check if already colored

    QVector<QPoint> neighbours;
    if(ui->FourNeighbour->isChecked()){
        neighbours = four_neighbour(seed);
    }
    else neighbours = eight_neighbour(seed);

    for(QPoint child:neighbours){
        //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
        colorPoint(pt.x(),pt.y(),250,0,0,unitDistance);
        Delay;
        boundary_fill_rec(child);
    }
}

void MainWindow::on_boundaryFill_clicked()
{
    qint64 n = points.size();
    boundary_fill_rec(points[n-1]);
}



void MainWindow::recolor_screen(){
    for(auto i:colorMap.keys()){
        QColor p = colorMap[i];
        QPoint coord = QPoint(i.first,i.second);
        QPoint pt = point_transform(coord.x(),coord.y());
        colorPoint(pt.x(),pt.y(),p.red(),p.green(),p.blue(),unitDistance);
    }
}


void MainWindow::on_zoomOut_clicked()
{
    clear_screen();
    unitDistance += 10;
    draw_gridlines(unitDistance);
    recolor_screen();
}


void MainWindow::on_zoomIn_clicked()
{
    clear_screen();
    if(unitDistance > 10) unitDistance -= 10;
    draw_gridlines(unitDistance);
    recolor_screen();
}

