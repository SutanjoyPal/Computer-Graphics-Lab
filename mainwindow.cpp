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
        canvas = QPixmap(ui->workArea->size());
        canvas.fill(Qt::white);
        ui->workArea->setPixmap(canvas);
    }
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
}

void MainWindow::on_showAxis_clicked() {
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;
    int axisWidth=ui->axisWidth->value();
    //qDebug()<<width<<height<<centerX<<centerY<<axisWidth;
    // Draw horizontal axis
    for (int x = 0; x < width; ++x) {
        colorPoint(x, centerY, 255, 0, 0, axisWidth); // Black color
    }

    // Draw vertical axis
    for (int y = 0; y < height; ++y) {
        colorPoint(centerX, y, 255, 0, 0, axisWidth); // Black color
    }
}

void MainWindow::on_gridlines_clicked() {
    int gridOffset = ui->gridOffset->value();
        int width = ui->workArea->width();
        int height = ui->workArea->height();
        if (gridOffset <= 0) return; // Prevent invalid grid offset

        int centerX=width/2;
        int centerY=height/2;
        QPixmap canvas=ui->workArea->pixmap();
        QPainter painter(&canvas);
        for(int i =  gridOffset; (centerX+i<width && centerX-i>0) || (centerY+i<height && centerY-i>0); i+= gridOffset)
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



bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->workArea && event->type() == QEvent::MouseMove) {
        QMouseEvent *cursor = static_cast<QMouseEvent*>(event);
        int x = cursor->pos().x();
        int y = cursor->pos().y();
        int gridOffset = (ui->gridOffset->value()==0)?1:ui->gridOffset->value();
        int width = ui->workArea->width();
        int height = ui->workArea->height();
        int centerX=width/2;
        int centerY=height/2;
        ui->x_coordinate->setText(QString::number(floor((x-centerX)*1.0/gridOffset)));
        ui->y_coordinate->setText(QString::number(floor((centerY-y)*1.0/gridOffset)));
        return true; // Event handled
    }
    if(watched == ui->workArea && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *cursor = static_cast<QMouseEvent*>(event);
        int x = cursor->pos().x();
        int y = cursor->pos().y();
        int gridOffset = (ui->gridOffset->value()==0)?1:ui->gridOffset->value();
        int width = ui->workArea->width();
        int height = ui->workArea->height();
        int centerX=width/2;
        int centerY=height/2;
        clickedPoint.setX(x);
        clickedPoint.setY(y);
        int X = floor((x-centerX)*1.0/gridOffset);
        int Y = floor((centerY-y)*1.0/gridOffset);
        points.push_back({X, Y});
        int calcX = centerX+ X*gridOffset + gridOffset/2;
        int calcY = centerY -  Y*gridOffset - gridOffset/2;
        // points.push_back({calcX, calcY});
        colorPoint(calcX, calcY, 255,255,0, gridOffset);

    }
    return QMainWindow::eventFilter(watched, event);
}
































void MainWindow::on_reset_clicked()
{
    ui->workArea->setPixmap(temp);
    points.clear();
}


void MainWindow::on_store_clicked()
{
    temp = ui->workArea->pixmap(Qt::ReturnByValue);
}


void MainWindow::draw_dda_line(float x1, float y1, float x2, float y2)
{
    float dx, dy, xinc, yinc, steps;

    dx = x2 - x1;
    dy = y2 - y1;
    steps = std::max(abs(dx), abs(dy));  // Determine the number of steps based on the larger difference

    xinc = dx / steps;  // Increment in x
    yinc = dy / steps;  // Increment in y

    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    float x_float = centerX + x1 * gridOffset + gridOffset / 2.0;
    float y_float = centerY - y1 * gridOffset - gridOffset / 2.0;

    int xn = static_cast<int>(x_float);  // Initial x position in the grid
    int yn = static_cast<int>(y_float);  // Initial y position in the grid

    qDebug() << xn << yn;  // Print the x, y values for debugging
    //colorPoint(xn, yn, 255, 0, 255, gridOffset);  // Color the initial point
    //--------------------------------------------------------------------------------

    QVector<QPoint> pts;
    pts.push_back(QPoint(xn,yn));

    QElapsedTimer timer;
    timer.start();
    int cnt=0;
    for (int i = 0; i < steps; i++)  // Loop to complete the straight line
    {
        x_float += xinc * gridOffset;
        y_float -= yinc * gridOffset;

        int x_new = static_cast<int>(x_float);  // New x position in the grid
        int y_new = static_cast<int>(y_float);  // New y position in the grid

        if (x_new != xn || y_new != yn)  // If there is a change in the grid position
        {
            xn = x_new;
            yn = y_new;
            int X = floor((xn-centerX)*1.0/gridOffset);
            int Y = floor((centerY-yn)*1.0/gridOffset);
            int calcX = centerX+ X*gridOffset + gridOffset/2;
            int calcY = centerY -  Y*gridOffset - gridOffset/2;
            pts.push_back(QPoint(calcX, calcY));
            // colorPoint(calcX, calcY, 0, 255, 0, gridOffset);  // Color the new point
        }
        cnt++;
        /*qDebug() << x_new << y_new;*/  // Print the updated x, y values for debugging
    }
    qDebug() << cnt;
    qint64 elapsedTime = timer.nsecsElapsed();
    ui->DDA_TIME->setText(QString("Time Taken: ") +QString::number(elapsedTime) + QString(" ns"));

    for(auto x: pts)
    {
        colorPoint(x.x(), x.y(), 255, 153, 51, gridOffset);
    }
}


void MainWindow::on_DDADraw_clicked()
{
    if(points.size()< 2 ) return;
    qint64 n  = points.size();
    auto coords1 = points[n-1];
    auto coords2 = points[n-2];
    draw_dda_line(coords1.x(), coords1.y(), coords2.x(), coords2.y());
}

void MainWindow::draw_bresenham_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    QVector<QPoint> pts;
    QElapsedTimer timer;
    timer.start();

    int cnt=0;
    while (true) {
        int calcX = centerX + x1 * gridOffset + gridOffset / 2;
        int calcY = centerY - y1 * gridOffset - gridOffset / 2;
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
        colorPoint(pt.x(), pt.y(), 153, 255, 153, gridOffset);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(points.size()< 2 ) return;
    qint64 n  = points.size();
    auto coords1 = points[n-1];
    auto coords2 = points[n-2];
    draw_bresenham_line(coords1.x(), coords1.y(), coords2.x(), coords2.y());
}



void MainWindow::draw_polar_circle(int xc,int yc){


    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    float x_float = centerX + xc * gridOffset + gridOffset / 2.0;
    float y_float = centerY - yc * gridOffset - gridOffset / 2.0;


    float r = (ui->Radius->value())*gridOffset;

    QVector<QPoint> pts;
    QElapsedTimer timer;
    timer.start();
    for (int angle = 0; angle < 360; ++angle) {
        double radian = angle * M_PI / 180.0;  // Convert degree to radian
        int x = static_cast<int>(x_float+(r * cos(radian)));
        int y = static_cast<int>(y_float+(r * sin(radian)));

        int X = floor((x-centerX)*1.0/gridOffset);
        int Y = floor((centerY-y)*1.0/gridOffset);
        int calcX = centerX+ X*gridOffset + gridOffset/2;
        int calcY = centerY -  Y*gridOffset - gridOffset/2;
        pts.push_back(QPoint(calcX, calcY));


        //pts.push_back(QPoint(x, y));


    }
    qint64 elapsedTime = timer.nsecsElapsed();
    ui->PolarTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    for(auto &pt:pts){
        qDebug()<<pt.x()<<" "<<pt.y();
        colorPoint(pt.x(), pt.y(), 102, 0, 204, gridOffset);
        delay(1);
    }
}

void MainWindow::EightPtSym(QVector<QPoint> &pts,float x_float,float y_float,int x,int y){
    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;



    int dx[] = {x,-x,x,-x,y,-y,y,-y};
    int dy[] = {y,y,-y,-y,x,x,-x,-x};

    for(int i=0;i<8;++i){
        int xn = static_cast<int>(x_float+dx[i]);
        int yn = static_cast<int>(y_float+dy[i]);
        int X = floor((xn-centerX)*1.0/gridOffset);
        int Y = floor((centerY-yn)*1.0/gridOffset);
        int calcX = centerX+ X*gridOffset + gridOffset/2;
        int calcY = centerY -  Y*gridOffset - gridOffset/2;
        pts.push_back(QPoint(calcX, calcY));
    }
}


void MainWindow::draw_circle_bresenham(int xc,int yc){
    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    float x_float = centerX + xc * gridOffset + gridOffset / 2.0;
    float y_float = centerY - yc * gridOffset - gridOffset / 2.0;

    float r = (ui->Radius->value())*gridOffset;
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
        colorPoint(pt.x(), pt.y(), 255, 51, 51, gridOffset);
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


    int offset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
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
        drawCirclePoints(x, y, px, py, 255, 0, 255, offset);
    }

    // qint64 timeMs = t.elapsed();
    // ui->CartTime->setText(QString::number(timeMs) + " ms");
    qint64 elapsedTime = t.nsecsElapsed();
    ui->CartTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

}

void MainWindow::drawCirclePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int gridOffset) {
    colorPoint(pixelCenterX + x * gridOffset, pixelCenterY - y * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX - x * gridOffset, pixelCenterY - y * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX + x * gridOffset, pixelCenterY + y * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX - x * gridOffset, pixelCenterY + y * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX + y * gridOffset, pixelCenterY - x * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX - y * gridOffset, pixelCenterY - x * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX + y * gridOffset, pixelCenterY + x * gridOffset, r, g, b, gridOffset);
    Delay;
    colorPoint(pixelCenterX - y * gridOffset, pixelCenterY + x * gridOffset, r, g, b, gridOffset);
    Delay;
}


void MainWindow::draw_polar_ellipse(QPoint f1, QPoint f2) {
    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    // Convert focus points to pixel coordinates
    float x1 = centerX + f1.x() * gridOffset + gridOffset / 2.0;
    float y1 = centerY - f1.y() * gridOffset - gridOffset / 2.0;
    float x2 = centerX + f2.x() * gridOffset + gridOffset / 2.0;
    float y2 = centerY - f2.y() * gridOffset - gridOffset / 2.0;

    // Calculate the center of the ellipse as the midpoint of the two foci
    float xc = (x1 + x2) / 2.0;
    float yc = (y1 + y2) / 2.0;

    // Fixed semi-major and semi-minor axes
    float a = ui->major->value()*gridOffset;
    float b = ui->minor->value()*gridOffset;

    QVector<QPoint> pts;
    QElapsedTimer timer;
    timer.start();

    // Draw the ellipse using polar coordinates
    for (int angle = 0; angle < 360; ++angle) {
        double radian = angle * M_PI / 180.0; // Convert degrees to radians
        int x = static_cast<int>(xc + a * cos(radian));
        int y = static_cast<int>(yc + b * sin(radian));

        int gridX = floor((x - centerX) * 1.0 / gridOffset);
        int gridY = floor((centerY - y) * 1.0 / gridOffset);
        int calcX = centerX + gridX * gridOffset + gridOffset / 2;
        int calcY = centerY - gridY * gridOffset - gridOffset / 2;
        pts.push_back(QPoint(calcX, calcY));
    }

    qint64 elapsedTime = timer.nsecsElapsed();
    //ui->PolarTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    // Draw each calculated point
    for (auto &pt : pts) {
        qDebug() << pt.x() << " " << pt.y();
        colorPoint(pt.x(), pt.y(), 102, 0, 204, gridOffset);
        delay(1); // Optional delay for visualization
    }
}




void MainWindow::on_PolarEllipse_clicked()
{
    qint64 n  = points.size();
    draw_polar_ellipse(points[n-1],points[n-2]);
}

void MainWindow::drawEllipsePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int gridOffset) {
    // Draw points using 4-point symmetry
    colorPoint(pixelCenterX + x * gridOffset, pixelCenterY - y * gridOffset, r, g, b, gridOffset); // Quadrant 1
    Delay;
    colorPoint(pixelCenterX - x * gridOffset, pixelCenterY - y * gridOffset, r, g, b, gridOffset); // Quadrant 2
    Delay;
    colorPoint(pixelCenterX + x * gridOffset, pixelCenterY + y * gridOffset, r, g, b, gridOffset); // Quadrant 3
    Delay;
    colorPoint(pixelCenterX - x * gridOffset, pixelCenterY + y * gridOffset, r, g, b, gridOffset); // Quadrant 4
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

    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    // Convert grid center to actual pixel coordinates
    int pixelCenterX = centerX + gridCenterX * gridOffset + gridOffset / 2;
    int pixelCenterY = centerY - gridCenterY * gridOffset - gridOffset / 2;

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
        drawEllipsePoints(p.first, p.second, pixelCenterX, pixelCenterY, 170, 170, 170, gridOffset);
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
    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    QSet<QPoint> newPts;
    for(QPoint vertex : polygon){
        QVector<QPoint> neighbours = eight_neighbour(vertex);
        for(QPoint neighbour:neighbours){
            QPoint pt = point_transform(neighbour.x(),neighbour.y());
            colorPoint(pt.x(),pt.y(), 153, 255, 153, gridOffset);
            newPts.insert(neighbour);
        }
    }
    for(QPoint pt:newPts){
        polygon.insert(pt);
    }
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

QPoint MainWindow:: point_transform(int x,int y){
    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX = width / 2;
    int centerY = height / 2;

    float x_float = centerX + x * gridOffset + gridOffset / 2.0;
    float y_float = centerY - y * gridOffset - gridOffset / 2.0;
    int xn = static_cast<int>(x_float);
    int yn = static_cast<int>(y_float);
    return QPoint(xn,yn);
}

double MainWindow::calc_slope(QPoint a,QPoint b){
    double m;
    m = (b.y()-a.y())/(b.x()-a.x());
    return m;
}

void MainWindow::scanline_fill(){
    int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
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
                        float x_float2 = centerX + i * gridOffset + gridOffset / 2.0;
                        int xn2 = static_cast<int>(x_float2);
                        colorPoint(xn2,yn, 0,0, 250, gridOffset);
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

    if(polygon.find(pt)!=polygon.end()) return;
    //qDebug()<<"Not in edge";
    if(visited.find(pt)!=visited.end()) return;
    visited.insert(pt);

    QVector<QPoint> neighbours;
    if(ui->FourNeighbour->isChecked()){
        neighbours = four_neighbour(seed);
    }
    else neighbours = eight_neighbour(seed);

    //qDebug()<<pt.x()<<" "<<pt.y();
    for(QPoint child:neighbours){
        int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
        colorPoint(pt.x(),pt.y(),250,0,0,gridOffset);
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
        int gridOffset = (ui->gridOffset->value() == 0) ? 1 : ui->gridOffset->value();
        colorPoint(pt.x(),pt.y(),250,0,0,gridOffset);
        Delay;
        boundary_fill_rec(child);
    }
}

void MainWindow::on_boundaryFill_clicked()
{
    qint64 n = points.size();
    boundary_fill_rec(points[n-1]);
}

