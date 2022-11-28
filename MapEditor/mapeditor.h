#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <cmath>
#include <QMainWindow>
#include <fstream>

namespace Ui {
    class MapEditor;
}

class MapEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget* parent = 0);
    int tp = 0;//切换当前状态
    int edgenum = 0, pointnum = 0;//edgenum存储当前路径数（不超过200），pointnum存储点数（不超过50）
    double matrix[51][51] = {0};//邻接矩阵，存储路径长度，为零表示不存在路径
    bool reach[51] = {};//搜索路径时判断点是否已经被访问过
    void DFS(int P1, int P2);//深度优先搜索，查找p1和p2之间的所有路径
    bool isin(QPoint x, QPoint y, int n = 10);//判断点击的位置是否选中了某个点
    double dist(QPoint a, QPoint b);//计算两点之间的像素距离
    void clr();//清除右侧搜索栏中的数据
    ~MapEditor();
    void drawArrow(QPoint x, QPoint y, QPainter& paper);//画一条从x指向y的箭头
    //求最短路径
    void Dijkstra(int begin, int end);
    struct Path {

        double value;//起点到当前点的路径长度
        bool visit;
        Path() {
            value = 0;
            visit = false;
        }
    } curPath[51];//记录起点到每个顶点的最短路径的信息

private slots://十三个点击按钮事件，一个绘图事件和一个鼠标点击事件
    void on_pushButton_clicked();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();

private:
    Ui::MapEditor* ui;
};

#endif // MAPEDITOR_H
