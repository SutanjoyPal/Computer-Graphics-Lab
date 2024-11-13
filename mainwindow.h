#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QMap>
#include <QPair>
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

    void on_DDADraw_clicked();

    void on_store_clicked();

    void on_reset_clicked();

    void on_GenCirclePolar_clicked();

    void on_GenCartCircle_clicked();


    void on_PolarEllipse_clicked();

    void on_GenEllipseBre_clicked();

    void on_DrawPolygon_clicked();



    void on_Scanline_clicked();

    void on_FloodFill4_clicked();

    void on_boundaryFill_clicked();

    void on_zoomOut_clicked();

    void on_zoomIn_clicked();

    void on_BresenhamLineDraw_clicked();

    void on_GenBresenhamCircle_clicked();

    void on_GenMidPtCircle_clicked();

    void on_ReflectX_clicked();

    void on_ReflectY_clicked();

    void on_ReflectO_clicked();

    void on_translate_clicked();

    void on_rotateOrigin_clicked();

    void on_shear_clicked();

    void on_Scale_clicked();

    void on_Rotate_clicked();

    void on_scale_clicked();

    void on_Reflect_clicked();

    void on_SutherCohen_clicked();

    void on_Window_clicked();

    void on_LiangBarsky_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap temp;
    void colorPoint(int x,int y,int r,int g, int b, int penwidth);
    void colorPoint(QPoint curPt, QColor color, int penwidth);
    void delay(int ms);
    void draw_gridlines(int gridOffset);
    void clear_screen();
    //void draw_dda_line(int x1,int y1,int x2,int y2);

    void color_pts(QVector<QPoint> &linePts,QColor color);
    void color_pts(QSet<QPoint> &linePts,QColor color);
    QVector<QPoint> generate_dda_linePts(QPoint startPt,QPoint endPt);
    QVector<QPoint> generate_bresenham_linePts(QPoint startPt,QPoint endPt);

    void eight_pt_symmetry(QVector<QPoint> &pts,QPoint curPt,QPoint centre);
    QVector<QPoint> generate_polar_circlePts(QPoint centre);
    QVector<QPoint> generate_bresenham_circlePts(QPoint centre);
    QVector<QPoint> generate_midpoint_circlePts(QPoint centre);
    QVector<QPoint> generate_cartesian_circlePts(QPoint centre);

    void four_pt_symmetry(QVector<QPoint> &pts,QPoint curPt,QPoint centre);
    QVector<QPoint> generate_polar_ellipsePts(QPoint focus1,QPoint focus2);

    //void draw_bresenham_ellipse(QPoint f1, QPoint f2);
    void draw_polar_ellipse(QPoint f1, QPoint f2);
    void drawEllipsePoints(int x, int y, int pixelCenterX, int pixelCenterY, int r, int g, int b, int gridOffset);

    void draw_Polygon();
    void draw_Polgon_Sides(QVector<QPoint> &polygonVertices);
    void get_Vertices();
    void make_edges_thicker();

    QColor getGridSquareColor(int gridX, int gridY);
    void on_checkColorButton_clicked();

    void scanline_fill();
    QPoint point_transform(int x,int y);
    QPoint point_transform(QPoint pt);

    QPoint reverse_point_transform(int xn, int yn);
    float calc_slope(QPoint a,QPoint b);

    QVector<QPoint> four_neighbour(QPoint pt);
    QVector<QPoint> eight_neighbour(QPoint pt);
    //void flood_fill_rec(QPoint seed,QSet<QPoint> &visited);

    QColor get_Color(QPoint pt);
    //void boundary_fill_rec(QPoint seed);
    void boundary_fill_rec(QPoint seed,QColor boundaryColor,QColor fillColor);
    void flood_fill_rec(QPoint seed,QColor oldColor,QColor newColor);

    void recolor_screen();
    void genRectangle(QPoint mn,QPoint mx);
    int genCode(QPoint endPt);


    QMap<QString,QColor> colorPalette;
    QPoint clickedPoint;
    QVector<QPoint> points;
    QSet<QPoint> polygon;
    QPoint start,end;
    QVector<QPoint> line;
    QVector<QPoint> polygonVertices;
    QMap<QPair<int,int>,QColor> colorMap;
    int unitDistance;
    int width;
    int height;
    int centerX;
    int centerY;

    void initializeColorPalette();

    class myTimer;
    QVector<int> matrix_multiplication(QVector<QVector<float>> &transformationMatrix,QVector<int> &coordinates);
    QVector<QPair<int,int>> coordinate_transformation(QVector<QVector<float>> &transformationMatrix);
    void draw_transfromed_polygon(QVector<QPair<int,int>> &transformedVertices);
    void redraw_screen();


};
#endif // MAINWINDOW_H


