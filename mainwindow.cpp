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
    //qDebug()<<"Point Coloured: "<<curPt.x()<<"  "<<curPt.y();
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
        timer.start();
    }

    void measureTime() {
        qint64 elapsedTime = timer.nsecsElapsed();
        mainWindow->ui->TimeMessage->setText(QString("By ")+algoName+QString(" drawing algorithm"));
        mainWindow->ui->timetaken->display(QString::number(elapsedTime));
    }
};

void MainWindow::color_pts(QVector<QPoint> &linePts,QColor color){
    for(QPoint currentPt : linePts){
        colorPoint(currentPt,color);
        delay(1);
    }
}
void MainWindow::color_pts(QSet<QPoint> &linePts,QColor color){
    for(QPoint currentPt : linePts){
        colorPoint(currentPt,color);
        delay(1);
    }
}


QVector<QPoint> MainWindow::generate_dda_linePts(QPoint startPt,QPoint endPt){
    int startX = startPt.x(),startY = startPt.y();
    int endX = endPt.x(),endY = endPt.y();

    int dx = endX-startX,dy = endY-startY;
    int steps = std::max(abs(dx),abs(dy));

    float xinc = (dx*1.0)/steps,yinc = (dy*1.0/steps);
    float curX = startX,curY = startY;

    myTimer t("DDA Line",this);
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
    return linePts;
}

void MainWindow::on_DDADraw_clicked()
{
    if(points.size()< 2 ) return;
    qint64 n  = points.size();
    QVector<QPoint> linePts = generate_dda_linePts(points[n-2],points[n-1]);
    color_pts(linePts,colorPalette["pink"]);
}

QVector<QPoint> MainWindow::generate_bresenham_linePts(QPoint startPt,QPoint endPt){

    int startX = startPt.x(),startY = startPt.y();
    int endX = endPt.x(),endY = endPt.y();
    int dx = abs(endX-startX),dy = abs(endY-startY);

    int xStep = (endX > startX ? 1:-1);
    int yStep = (endY > startY ? 1:-1);
    bool flag=1;

    if(dy>dx){
        std::swap(startX,startY);
        std::swap(dx,dy);
        std::swap(xStep,yStep);
        flag=0;
    }

    int p = 2*dy-dx;
    QVector<QPoint> linePts;
    myTimer t("Bresenham Line",this);
    for(int steps=0;steps<=dx;++steps){
        if(flag==0){
            linePts.push_back(QPoint(startY,startX));
        }
        else linePts.push_back(QPoint(startX,startY));
        startX+=xStep;

        if(p<0){
            p+=2*dy;
        }
        else{
            startY+=yStep;
            p+=(2*dy-2*dx);
        }

    }
    t.measureTime();
    return linePts;

}

void MainWindow::on_BresenhamLineDraw_clicked()
{
    if(points.size()< 2 ) return;
    qint64 n  = points.size();
    QVector<QPoint> linePts = generate_bresenham_linePts(points[n-2],points[n-1]);
    color_pts(linePts,colorPalette["maroon"]);
}



void MainWindow::eight_pt_symmetry(QVector<QPoint> &pts,QPoint curPt,QPoint centre){
    int centreX=centre.x(),centreY=centre.y();
    int x = curPt.x(), y =curPt.y();
    int newX[] = {x,-x,x,-x,y,-y,y,-y};
    int newY[] = {y,y,-y,-y,x,x,-x,-x};

    for(int i=0;i<8;++i){
        pts.push_back(QPoint(centreX+newX[i],centreY+newY[i]));
    }
}

QVector<QPoint> MainWindow::generate_polar_circlePts(QPoint centre){
    int centreX=centre.x(),centreY=centre.y();
    float r = ui->Radius->value();

    QVector<QPoint> circlePts;
    myTimer t("Polar Circle",this);
    for(int angle = 0;angle <= 45;++angle){
        float radian = angle * M_PI / 180.0;
        int curX = std::round((r*cos(radian)));
        int curY = std::round((r*sin(radian)));
        QPoint curPt = QPoint(curX,curY);
        eight_pt_symmetry(circlePts,curPt,QPoint(centreX,centreY));
    }
    t.measureTime();
    return circlePts;
}

void MainWindow::on_GenCirclePolar_clicked()
{
    qint64 n  = points.size();
    QVector<QPoint> circlePts = generate_polar_circlePts(points[n-1]);
    color_pts(circlePts,colorPalette["olive"]);
}

QVector<QPoint> MainWindow::generate_bresenham_circlePts(QPoint centre){
    int r = ui->Radius->value();
    int curX=0,curY=r;

    int p = 3-2*r;
    QVector<QPoint> circlePts;
    myTimer t("Bresenham Circle",this);
    while(curX <= curY){
        eight_pt_symmetry(circlePts,QPoint(curX,curY),centre);
        curX++;
        if(p >= 0){
            curY--;
            p+=(4*(curX-curY)+10);
        }
        else{
            p+=(4*curX+6);
        }
    }
    t.measureTime();
    return circlePts;
}

void MainWindow::on_GenBresenhamCircle_clicked()
{
    qint64 n  = points.size();
    QVector<QPoint> circlePts = generate_midpoint_circlePts(points[n-1]);
    color_pts(circlePts,colorPalette["navy"]);
}

QVector<QPoint> MainWindow::generate_midpoint_circlePts(QPoint centre){
    int r = ui->Radius->value();
    int curX=0,curY=r;

    int p = 1-r;
    QVector<QPoint> circlePts;
    myTimer t("MidPoint Circle",this);
    while(curX<=curY){
        eight_pt_symmetry(circlePts,QPoint(curX,curY),centre);
        if(p<0){
            p+=(2*curX+3);
        }
        else{
            p+=(2*curX+2*curY+5);
            curY--;
        }
        curX++;
    }
    t.measureTime();
    return circlePts;
}

void MainWindow::on_GenMidPtCircle_clicked()
{
    qint64 n  = points.size();
    QVector<QPoint> circlePts = generate_bresenham_circlePts(points[n-1]);
    color_pts(circlePts,colorPalette["teal"]);
}

QVector<QPoint> MainWindow::generate_cartesian_circlePts(QPoint centre){
    float r = ui->Radius->value();

    QVector<QPoint> circlePts;
    myTimer t("Cartesian Circle",this);
    for(int curX=0;(curX*1.0)<=(r/std::sqrt(2));++curX){
        int curY=std::round((r*r-curX*curX));
        eight_pt_symmetry(circlePts,QPoint(curX,curY),centre);
    }
    t.measureTime();
    return circlePts;
}

void MainWindow::on_GenCartCircle_clicked()
{
    qint64 n  = points.size();
    QVector<QPoint> circlePts = generate_midpoint_circlePts(points[n-1]);
    color_pts(circlePts,colorPalette["lime"]);
}




void MainWindow::four_pt_symmetry(QVector<QPoint> &pts,QPoint curPt,QPoint centre){
    colorPoint(centre,colorPalette["gold"]);
    int centreX=centre.x(),centreY=centre.y();
    int x = curPt.x(), y =curPt.y();
    int newX[] = {x,-x,x,-x};
    int newY[] = {y,y,-y,-y};

    for(int i=0;i<4;++i){
        pts.push_back(QPoint(centreX+newX[i],centreY+newY[i]));
    }
}

QVector<QPoint> MainWindow::generate_polar_ellipsePts(QPoint focus1,QPoint focus2){
    int focus1X = focus1.x(),focus1Y = focus1.y();
    int focus2X = focus2.x(),focus2Y = focus2.y();

    int centreX = std::round(((focus1X+focus2X*1.0)/2.0));
    int centreY = std::round(((focus1Y+focus2Y*1.0)/2.0));
    QPoint centre = QPoint(centreX,centreY);
    colorPoint(centre,colorPalette["gold"]);
    float semiMajor  = ui->major->value();
    float semiMinor = ui->minor->value();

    QVector<QPoint> ellipsePts;
    myTimer t("Polar Ellipse",this);
    for(int angle=0;angle<=360;++angle){
        float radian = angle * M_PI / 180.0;
        int curX = std::round(semiMajor*cos(radian));
        int curY = std::round(semiMinor*sin(radian));
        ellipsePts.push_back(QPoint(centreX+curX,centreY+curY));
        //four_pt_symmetry(ellipsePts,QPoint(curX,curY),centre);
    }
    t.measureTime();
    for(QPoint pt:ellipsePts){
        qDebug()<<"Ellipse Pt "<<pt.x()<<" "<<pt.y();
    }
    return ellipsePts;
}



void MainWindow::draw_polar_ellipse(QPoint f1, QPoint f2) {
    //int unitDistance = (ui->unitDistance->value() == 0) ? 1 : ui->unitDistance->value();
    QVector<QPoint> ellipsePts = generate_polar_ellipsePts(f1,f2);
    color_pts(ellipsePts,colorPalette["gray"]);
    // int width = ui->workArea->width();
    // int height = ui->workArea->height();
    // int centerX = width / 2;
    // int centerY = height / 2;

    // // Convert focus points to pixel coordinates
    // float x1 = centerX + f1.x() * unitDistance + unitDistance / 2.0;
    // float y1 = centerY - f1.y() * unitDistance - unitDistance / 2.0;
    // float x2 = centerX + f2.x() * unitDistance + unitDistance / 2.0;
    // float y2 = centerY - f2.y() * unitDistance - unitDistance / 2.0;

    // // Calculate the center of the ellipse as the midpoint of the two foci
    // float xc = (x1 + x2) / 2.0;
    // float yc = (y1 + y2) / 2.0;

    // // Fixed semi-major and semi-minor axes
    // float a = ui->major->value()*unitDistance;
    // float b = ui->minor->value()*unitDistance;

    // QVector<QPoint> pts;
    // QElapsedTimer timer;
    // timer.start();

    // // Draw the ellipse using polar coordinates
    // for (int angle = 0; angle < 360; ++angle) {
    //     double radian = angle * M_PI / 180.0; // Convert degrees to radians
    //     int x = static_cast<int>(xc + a * cos(radian));
    //     int y = static_cast<int>(yc + b * sin(radian));

    //     int gridX = floor((x - centerX) * 1.0 / unitDistance);
    //     int gridY = floor((centerY - y) * 1.0 / unitDistance);
    //     int calcX = centerX + gridX * unitDistance + unitDistance / 2;
    //     int calcY = centerY - gridY * unitDistance - unitDistance / 2;
    //     pts.push_back(QPoint(calcX, calcY));
    // }

    // qint64 elapsedTime = timer.nsecsElapsed();
    // //ui->PolarTime->setText(QString("Time Taken: ") + QString::number(elapsedTime) + QString(" ns"));

    // // Draw each calculated point
    // for (auto &pt : pts) {
    //     qDebug() << pt.x() << " " << pt.y();
    //     colorPoint(pt.x(), pt.y(), 102, 0, 204, unitDistance);
    //     delay(1); // Optional delay for visualization
    // }
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
        QVector<QPoint> sidePts = generate_bresenham_linePts(curVertex,nextVertex);
        for(QPoint curPt:sidePts){
            polygon.insert(curPt);
        }
        //draw_bresenham_line(curVertex.x(),curVertex.y(),nextVertex.x(),nextVertex.y());
    }
}

void MainWindow::make_edges_thicker(){
    QVector<QPoint> neighbourPts;
    for(QPoint curPt:polygon){
        QVector<QPoint> neighbours = eight_neighbour(curPt);
        for(QPoint curNeighbour:neighbours){
            neighbourPts.push_back(curNeighbour);
        }
    }
    for(QPoint curPt:neighbourPts){
        polygon.insert(curPt);
    }
}

void MainWindow::draw_Polygon(){
    polygon.clear();
    QVector<QPoint> polygonVertices = get_Vertices();
    draw_Polgon_Sides(polygonVertices);
}

void MainWindow::on_DrawPolygon_clicked()
{
    myTimer t("Polygon",this);
    draw_Polygon();
    if(ui->ThickEdges->isChecked()) make_edges_thicker();
    t.measureTime();
    color_pts(polygon,colorPalette["purple"]);
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

QColor MainWindow::get_Color(QPoint curPt){
    QPoint pt = point_transform(curPt);
    QImage canvas=ui->workArea->pixmap(Qt::ReturnByValue).toImage();
    QColor clr=canvas.pixelColor(pt.x(),pt.y());
    //qDebug()<<pt.x()<<" "<<pt.y();
    //qDebug()<<clr.red()<<" "<<clr.green()<<" "<<clr.blue();
    return clr;
}


void MainWindow::flood_fill_rec(QPoint seed,QColor oldColor,QColor newColor){
    QColor currentColor = get_Color(seed);
    if(currentColor == newColor) return;
    if((currentColor != oldColor)&&(currentColor!=colorPalette["yellow"])) return;

    QVector<QPoint> neighbours;
    if(ui->EightNeighbour->isChecked()){
        neighbours = eight_neighbour(seed);
    }
    else neighbours = four_neighbour(seed);
    for(QPoint child:neighbours){
        colorPoint(seed,newColor);
        delay(1);
        flood_fill_rec(child,oldColor,newColor);
    }
}

void MainWindow::on_FloodFill4_clicked()
{
    qint64 n = points.size();
    myTimer t("Flood Fill",this);
    flood_fill_rec(points[n-1],colorPalette["white"],colorPalette["orange"]);
    t.measureTime();
}


void MainWindow::boundary_fill_rec(QPoint seed,QColor boundaryColor,QColor fillColor){
    QColor current_clr = get_Color(seed);
    if(current_clr == boundaryColor) return;
    if(current_clr == fillColor) return;


    QVector<QPoint> neighbours;
    if(ui->EightNeighbour->isChecked()){
        neighbours = eight_neighbour(seed);
    }
    else neighbours = four_neighbour(seed);


    for(QPoint child:neighbours){
        colorPoint(seed,fillColor);
        delay(1);
        boundary_fill_rec(child,boundaryColor,fillColor);
    }
}

void MainWindow::on_boundaryFill_clicked()
{
    qint64 n = points.size();
    get_Color(points[n-1]);
    myTimer t("Boundary Fill",this);
    boundary_fill_rec(points[n-1],colorPalette["purple"],colorPalette["red"]);
    t.measureTime();
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










