// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H

// #include <QMainWindow>

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();
// protected:
//     bool eventFilter(QObject *watched, QEvent *event) override;
// private slots:
//     void on_showAxis_clicked();

//     void on_gridlines_clicked();

//     void on_pushButton_clicked();

//     void on_store_clicked();

// private:
//     Ui::MainWindow *ui;
//     void colorPoint(int x,int y,int r,int g, int b, int penwidth);
//     void delay(int ms);
//     QPoint clickedPoint;
// };
// #endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>
#include <QSet>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    void on_showAxis_clicked();

    void on_gridlines_clicked();


    //void on_setCoord_clicked();

    void on_DDADraw_clicked();

    void on_store_clicked();

    void on_reset_clicked();

    //void on_pushButton_clicked();


    // void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    // void on_label_5_linkActivated(const QString &link);

    void on_GenCircle_clicked();

    // void on_Radius_textChanged(const QString &arg1);

    void on_GenCirclePolar_clicked();

    void on_GenCartCircle_clicked();


    void on_PolarEllipse_clicked();

    void on_GenEllipseBre_clicked();

    void on_DrawPolygon_clicked();



    void on_Scanline_clicked();

    void on_FloodFill4_clicked();

    void on_boundaryFill_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap temp;
    void colorPoint(int x,int y,int r,int g, int b, int penwidth);
    void delay(int ms);
    void draw_dda_line(float x1,float y1,float x2,float y2);
    void draw_bresenham_line(int x1, int y1, int x2, int y2);
    void draw_polar_circle(int xc,int yc);
    void draw_circle_bresenham(int xc,int yc);
    void EightPtSym(QVector<QPoint> &pts,float x_float,float y_float,int x,int y);
    void drawCirclePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int gridOffset);
    //void draw_bresenham_ellipse(QPoint f1, QPoint f2);
    void draw_polar_ellipse(QPoint f1, QPoint f2);
    void drawEllipsePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int gridOffset);

    void draw_Polygon();
    void draw_Polgon_Sides(QVector<QPoint> &polygonVertices);
    QVector<QPoint> get_Vertices();
    void make_edges_thicker();

    QColor getGridSquareColor(int gridX, int gridY);
    void on_checkColorButton_clicked();

    void scanline_fill();
    QPoint point_transform(int x,int y);
    double calc_slope(QPoint a,QPoint b);

    QVector<QPoint> four_neighbour(QPoint pt);
    QVector<QPoint> eight_neighbour(QPoint pt);
    void flood_fill_rec(QPoint seed,QSet<QPoint> &visited);

    QColor get_Color(QPoint pt);
    void boundary_fill_rec(QPoint seed);

    QPoint clickedPoint;
    QVector<QPoint> points;
    QSet<QPoint> polygon;
    //int gridOffset;
};
#endif // MAINWINDOW_H


