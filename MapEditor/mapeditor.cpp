#include "mapeditor.h"
#include "ui_mapeditor.h"
#include "CoorTrans.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QFileDialog>
#include <QInputDialog>
const double inf = 1e100;//路径最大值
QPoint P1, P2, P3, P4;//四个临时点
QPoint P[51];//点数组p，防越界
QString Pl[51], pic;//pl数组存储每个点的标签，pic为当前背景图片的存储路径
int ways, waysDij;//右侧显示栏路径的数量
double dis, min, mindis;//dis是搜索路径时路径长度当前值，min是路径长度最小值
bool showlen = false;//是否显示当前路径长度
struct lines { int a, b; bool f = false; } currLine, line[201];//线，ab是两点p1，p2的下标，f标记是否是最短路径，如是则标红，否则保持蓝色。currentLine是当前线，line数组存储所有线
//line数组表示线时，下标从1开始，直到200
int path[51];//起点到当前点的最短路径，从下标1开始存

struct location{
    double longitude;
    double latitude;
} locations[51];//记录点的经纬度

class Stack//用于dfs，遍历时，“错误”路径时倒退
{
private:
    int a[51] = {};//存储点的下标，经过的点下标
    int num = 0;//初始化点的个数，经过的点个数
public:
    void push(int n) {
        for(int i = 1; i <= num; ++i)
            if(a[i] == n) return;//点不能重合
        a[++num] = n; }//将下标为n的点压入栈
    void pop() { a[num--] = 0; }//出栈
    void removeAll()//清空栈
    {
        while(num) pop();
    }
    QString getstr()//右侧显示栏中点的标签展示，路径结果
    {
        QString str = "";
        for (int i = 1; i < num; i++)
            str += Pl[a[i]] + "->";
        str += Pl[a[num]];
        return str;
    }
    void showline()//将最短路径标红
    {
        for (int i = 1; i < num; i++)
        {
            for (int j = 1; line[j].a && j <= 200; j++)//在line[j]存在并且line数量在200以内循环
            {
//                if ((line[j].a == a[i] && line[j].b == a[i + 1]) || (line[j].b == a[i] && line[j].a == a[i + 1]))//如果线当中点的下标与最短路径栈中存储的点下标相同
                if (line[j].a == a[i] && line[j].b == a[i + 1])//如果线当中点的下标与最短路径栈中存储的点下标相同
                {
                    line[j].f = true;//标红
                    break;
                }
            }
        }
    }
}stack, shortestStack, shortestDij;//shortestStack存储最短路径对应的栈，stack是搜索时候的当前路径栈
int count = 1;//添加的点的默认下标
double MapEditor::dist(QPoint a, QPoint b)//计算两点间距离的函数
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
bool MapEditor::isin(QPoint x, QPoint y, int n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    if (dist(x, y) <= n) return true;//半径n有默认参数10
    else return false;
}

MapEditor::MapEditor(QWidget* parent) ://构造函数
    QMainWindow(parent),
    ui(new Ui::MapEditor)
{
    ui->setupUi(this);
    ui->pushButton_6->setText("求所有路径\n及最短路径");
}

MapEditor::~MapEditor()//析构函数
{
    delete ui;
}

void MapEditor::Dijkstra(int begin, int end) //使用dij算法求最短路
{
    waysDij = 0;//最短路径清空，暂无最短路
    mindis = inf;
    for(int k = 0; k < 51; ++k) path[k] = -1;
//    int mark = 0;
    //首先初始化我们的curPath数组
    int i;
    for(i = 0; i < 51; i++){
        curPath[i].value = inf;
        curPath[i].visit = false;
    }
    for (i = 1; i <= this->pointnum; i++) {
        if(matrix[begin][i] == 0)//表示从begin到i没有路径
        {
            curPath[i].value = inf;
        }
        else curPath[i].value = matrix[begin][i];//存在路径
    }
    //设置起点的到起点的路径为0
    curPath[begin].value = 0;
    curPath[begin].visit = true;//起点到达

//    int cnt = 1;
    //计算剩余pointnum-1个顶点的最短路径
//    while (cnt != this->pointnum)
    for(int cnt = 1; cnt <= this->pointnum; ++cnt)
    {
        if(cnt == begin) continue;
        int temp = 0;//当前curPath数组中最小距离的下标
        mindis = inf;//记录当前的距离最小值
        for (i = 1; i <= this->pointnum; ++i)
        {
            if (curPath[i].visit == false && curPath[i].value < mindis)
            {
                mindis = curPath[i].value;
                temp = i;
            }
        }
        if (mindis == inf) return;//说明未找到最小值

        //把temp对应的顶点加入到已经找到的最短路径的集合中
        curPath[temp].visit = true;
//        ++cnt;
//        path[++mark] = temp;
        for (i = 1; i <= this->pointnum; i++) {
            //注意这里的条件matrix[temp][i]!=0必须加，不然会出现溢出，从而造成程序异常
            if (matrix[temp][i] != 0 && (curPath[temp].value + matrix[temp][i]) < curPath[i].value) {
                //如果新得到的边可以影响其他未访问的顶点，那就更新它的最短路径和长度
                curPath[i].value = curPath[temp].value + matrix[temp][i];
                path[i] = temp;//最短路径，记录点的下标
//                path[++mark] = temp;
            }
        }
    }
    mindis = curPath[end].value;
//    if(mindis == inf)
//    {
//        waysDij = 0;
//        return ;
//    }
//    for(i = 1; i <= 50; ++i)
//    {
        shortestDij.removeAll();
        int j = end;
        shortestDij.push(begin);
        while(path[j] != -1)
        {
            shortestDij.push(j);
            j = path[j];
        }
        shortestDij.push(j);
        waysDij = 1;
//    }
}

void MapEditor::DFS(int i, int j)//i为起点，j为终点
{
    reach[i] = true;//起点到达
    stack.push(i);//将起点压入栈内
    if (i == j)//判断已经到达终点
    {
        if (ways <= 200000) ui->listWidget->addItem(stack.getstr() + "，长度为：" + QString::number(dis)), ways++;
        if (min == 0 || dis < min)//将最短路径值赋给min以及shortestStack
        {//min == 0时将dis赋值给min是指当前不存在这条路径，所以任意路径都是最短的
            min = dis;
            shortestStack = stack;//shortestStack是当前最短路径栈
        }
    }
    else//未到达终点，遍历所有可行途径
        for (int t = 1; t <= pointnum; t++)
            if (matrix[i][t] && !reach[t])//matrix[i][t]存在，即该路径存在，并且P[t]未达到
            {
                dis += matrix[i][t];//当前路径长度＋目前点到下一个点的距离
                DFS(t, j);//递归，t为新的起点
                dis -= matrix[i][t];//更换新路径，将此前路径长度减去
            }
    stack.pop();//将最新的点弹出
    reach[i] = false;//因为此点弹出，故未达到
}
void MapEditor::clr()//清除右侧显示栏的显示信息
{
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->listWidget->clear();
    for (int i = 1; i <= edgenum; i++)
        if (line[i].f) line[i].f = false;//红线变回蓝线
    update();//调用paintEvent函数
}
void MapEditor::drawArrow(QPoint x, QPoint y, QPainter& paper)
{
    paper.drawLine(x, y);//在x和y之间先画一条直线

    float x1 = x.x();         //起点
    float y1 = x.y();
    float x2 = y.x();         //终点
    float y2 = y.y();
    float l = 15.0;           //箭头的那长度
    float a = 0.5;            //箭头与线段角度
    float x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);
    float y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);
    float x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);
    float y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);
    paper.drawLine(x2,y2,x3,y3);
    paper.drawLine(x2,y2,x4,y4);

}
void MapEditor::paintEvent(QPaintEvent*)//绘图函数
{
    QPainter painter(this);//画笔，this为当前窗口
    painter.drawPixmap(190, 70, 1000, 700, QPixmap(pic));//载入背景图片并显示出来
    QFont font1("Microsoft YaHei", 9);//字体说明
    QFont font2("Microsoft YaHei", 12);
    painter.drawRect(190, 70, 1000, 700);//矩形大小，窗口大小
    painter.setFont(font1);
    painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑
    for (int i = 1; i <= edgenum; i++)//edgenum是当前路径数
    {
        if (!line[i].f) painter.setPen(Qt::blue);//设置画笔颜色为蓝色
        else painter.setPen(Qt::red);
        //从a到b的有向线段，a->b
        drawArrow(P[line[i].a], P[line[i].b], painter);//两点连线
    }
    painter.setPen(Qt::darkMagenta);
    if (showlen)//如果显示路径
        for (int i = 1; i <= pointnum; i++)//pointnum是点的数量
            for (int j = 1; j <= pointnum; j++)
                if (matrix[i][j])//若 i->j 路径存在
                {
                    int x1, y1;//显示路径长度的横纵坐标
//                    x1 = (P[i].x() + P[j].x()) / 2 - 10;//路径中央偏左
//                    y1 = (P[i].y() + P[j].y()) / 2 + 4;//路径中央偏下
                    x1 = P[j].x() - 80;//路径终点偏左
                    y1 = P[j].y() + 20;//路径终点偏下
                    painter.drawText(QPoint(x1, y1), QString::number(matrix[i][j]));//路径长度显示在（x1,y1）位置处，邻接矩阵中存储路径长度
                }
    painter.setPen(Qt::black);
    painter.setBrush(Qt::yellow);
    painter.setFont(font2);
    for (int i = 1; i <= pointnum; i++)
    {
        painter.drawEllipse(P[i], 4, 4);//把点画出来
        painter.drawText(QPoint(P[i].x() + 5, P[i].y() + 6), Pl[i]);//画出点的标签，pl[i]为标签
    }
    ui->label_2->setText("点数：" + QString::number(pointnum));
    ui->label_3->setText("路径数：" + QString::number(edgenum));
}
void MapEditor::mousePressEvent(QMouseEvent* event)//功能实现
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint temp = event->pos();//event->pos为当前点击位置
        switch (tp)//tp标识状态量
        {
        case 1://选择第一个点
            if (edgenum >= 200) QMessageBox::warning(this, "警告", "路径数已达上限");
            else
                for (int i = 1; i <= pointnum; i++)//在现有的点中查找被选中的点
                    if (isin(temp, P[i]))//选中
                    {
                        //更新当前点信息
                        ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                        ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                        ui->textEdit->setText(Pl[i]);

                        P1 = P[i]; line[edgenum + 1].a = i; tp = 2; ui->label->setText("请选择第二个点"); break;//将第一个点信息存入P1，line[num1+1]，并开始case2功能
                    } break;
        case 2://选择第二个点
            for (int i = 1; i <= pointnum; i++)
                if (P[i] != P1 && isin(temp, P[i]))//若选中了与第一个点不同的点
                {
                    //更新当前点信息
                    ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                    ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                    ui->textEdit->setText(Pl[i]);

                    int t = edgenum++;//线数量+1
                    P2 = P[i]; line[edgenum].b = i; tp = 1;//P2信息录入，完善line[num1]信息（num1已+1），tp回归1.
//                    if (line[edgenum].a > line[edgenum].b)//保证线的第一个点下标比第二个小
//                    {
//                        int t1 = line[edgenum].a; line[edgenum].a = line[edgenum].b; line[edgenum].b = t1;
//                    }
                    for (int j = 1; j < edgenum; j++)//判断是否路线已经存在
                    {
                        if (line[edgenum].a == line[j].a && line[edgenum].b == line[j].b)
                        {
                            line[edgenum--] = line[0];//line[0]是空线
                            QMessageBox::warning(this, "警告", "两条路径重合");
                            break;
                        }
                    }
                    //上面如果线已经存在，则t == edgenum，没有成功添加线
                    if (t != edgenum)
                    {
                          //使用两点的经纬度计算两点之间的路径长度
//                          matrix[line[edgenum].a][line[edgenum].b] = matrix[line[edgenum].b][line[edgenum].a]
//                                  = calDist(locations[line[edgenum].a].latitude, locations[line[edgenum].a].longitude, locations[line[edgenum].b].latitude, locations[line[edgenum].b].longitude);
                          //有向图
                          matrix[line[edgenum].a][line[edgenum].b] = calDist(locations[line[edgenum].a].latitude, locations[line[edgenum].a].longitude, locations[line[edgenum].b].latitude, locations[line[edgenum].b].longitude);
                          if(matrix[line[edgenum].a][line[edgenum].b] == 0)//经纬度计算失效，将两点间的像素距离赋值给两点间的路径长度（默认）
                            matrix[line[edgenum].a][line[edgenum].b] = dist(P[line[edgenum].a], P[line[edgenum].b]);
                    }
                    ui->label->setText("请选择第一个点");
                    break;
                }
            update(); break;
        case 3://添加点
            if (pointnum < 50 && temp.x() >= 190 && temp.x() <= 1190 && temp.y()>70 && temp.y() <= 770)//判断所加的点是否在窗口范围内
            {
                int t = pointnum++;
                for (int i = 1; i < pointnum; i++)
                    if (isin(temp, P[i], 20))//判断两点是否太近，选中条件为“半径10的圆邻域”，故两点距离需要大于20
                    {
                        pointnum--; QMessageBox::warning(this, "警告", "两个点靠太近");
                    }
                if (t == pointnum) break;//未成功添加点
                P[pointnum] = event->pos();//当前位置赋给最新的P点

                count = pointnum;//count从pointnum开始编号，防止读取地图之后使用默认count编号和原来的编号名称相同
                QString s0 = QInputDialog::getText(this, "设置点标签", "输入该点的名称");
                if (s0 != "") {
                    Pl[pointnum] = s0.left(13);
                    for(int j = 1; j < pointnum; ++j)
                    {
                        if(Pl[pointnum] == Pl[j])//存在同名标签，新点将使用默认标签
                        {
                            QMessageBox::warning(this, "警告", "标签重名");
                            Pl[pointnum] = QString::number(count++);//创建默认标签
                        }
                    }
                }
                else Pl[pointnum] = QString::number(count++);//创建默认标签

                //将添加点的标签加入右侧下拉框中
                ui->comboBox->addItem(Pl[pointnum]);
                ui->comboBox_2->addItem(Pl[pointnum]);

                //lo存储经度，la存储纬度
                double lo = -1, la = -1;
                lo = QInputDialog::getDouble(this, "设置坐标", "输入该点的经度", 0, -180, 180, 6);
                if(lo == 0)
                {
                    QMessageBox::warning(this, "警告", "经度默认值为0");
                    lo = QInputDialog::getDouble(this, "设置坐标", "请确保设置该点的经度", 0, -180, 180, 6);
                }
                la = QInputDialog::getDouble(this, "设置坐标", "输入该点的纬度", 0, -90, 90, 6);
                if(la == 0)
                {
                    QMessageBox::warning(this, "警告", "纬度默认值为0");
                    la = QInputDialog::getDouble(this, "设置坐标", "请确保设置该点的纬度", 0,-90, 90, 6);
                }
                locations[pointnum].longitude = lo;
                locations[pointnum].latitude = la;

                update();
            }
            else if (pointnum >= 50) QMessageBox::warning(this, "警告", "点数已达上限");
            else QMessageBox::warning(this, "警告", "点超出边界");
            break;
        case 4://删除点
            if (pointnum <= 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= pointnum; i++)
                    if (isin(temp, P[i]))//选中想要删除的点
                    {
                        //更新当前点信息
                        ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                        ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                        ui->textEdit->setText(Pl[i]);

                        QString lbl = ui->textEdit->toPlainText();
                        if(lbl == Pl[i])//清除右侧三个信息
                        {
                            ui->textEdit_3->setText("");
                            ui->textEdit_2->setText("");
                            ui->textEdit->setText("");
                        }

                        for (int j = i; j < pointnum; j++)
                        {
                            P[j] = P[j + 1];//将删除的点后的点前移
                            Pl[j] = Pl[j + 1];//点的标签同理
                            //点的经纬度同理
                            locations[j].latitude = locations[j + 1].latitude;
                            locations[j].longitude = locations[j + 1].longitude;

                            for (int k = 1; k <= pointnum; k++)//此一系列对matrix的操作使该点下标对应的行列删除
                                matrix[j][k] = matrix[j + 1][k];
                        }
                        for (int j = i; j < pointnum; j++)
                            for (int k = 1; k <= pointnum; k++)
                                matrix[k][j] = matrix[k][j + 1];
                        for (int j = 1; j <= pointnum; j++)
                            matrix[j][pointnum] = matrix[pointnum][j] = 0;
                        //最后一个点的经纬度消失，下标为零中存储默认初始值0？？？
                        locations[pointnum].latitude = locations[0].latitude;
                        locations[pointnum].longitude = locations[0].longitude;
                        Pl[pointnum] = Pl[0];//最后一个点标签消失
                        P[pointnum--] = P[0];//最后一个点消失

                        //在右侧下拉框中删除点，先删除所有点，再添加点
                        while(ui->comboBox->count())
                        {
                             ui->comboBox->removeItem(0);
                             ui->comboBox_2->removeItem(0);
                        }
                        for(int i = 1; i <= pointnum; ++i)
                        {
                            ui->comboBox->addItem(Pl[i]);
                            ui->comboBox_2->addItem(Pl[i]);
                        }

                        for (int j = 1; j <= edgenum; j++)
                        {
                            if (i == line[j].a || i == line[j].b)//将line数组一并前移
                            {
                                for (int k = j; k < edgenum; k++)
                                    line[k] = line[k + 1];
                                line[edgenum--] = line[0];//将最后一条线消除，同时线数量减一
                                j--;
                            }
                            else//下标原在被选中的点之后的点所在线的下标前移
                            {
                                if (line[j].a > i) line[j].a--;
                                if (line[j].b > i) line[j].b--;
                            }
                        }
                        update();
                        break;
                    }
            break;
        case 5://选择第一个点删除路径
            if (edgenum <= 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= pointnum; i++)
                    if (isin(temp, P[i]))//判断选中
                    {
                        //更新当前点信息
                        ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                        ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                        ui->textEdit->setText(Pl[i]);

                        P1 = P[i]; currLine.a = i; tp = 6; ui->label->setText("请选择要删除路径的第二个点");
                    } break;
        case 6://选择第二个点删除路径
            for (int i = 1; i <= pointnum; i++)
            {
                if (P[i] != P1 && isin(temp, P[i]))//选中
                {
                    //更新当前点信息
                    ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                    ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                    ui->textEdit->setText(Pl[i]);

                    P2 = P[i]; currLine.b = i; tp = 5;//第二个点信息载入
//                    if (currLine.a > currLine.b)//保证线的第二个点下标大于第一个
//                    {
//                        int t1 = currLine.a; currLine.a = currLine.b; currLine.b = t1;
//                    }
                    int t3 = edgenum;
                    for (int j = 1; j <= edgenum; j++)
                    {
                        if (currLine.a == line[j].a && currLine.b == line[j].b)//两次选中的点之间有边存在
                        {
                            matrix[line[j].a][line[j].b] = 0;//点之间路径长度删除
                            {for (int k = j; k < edgenum; k++)
                                line[k] = line[k + 1];//路径（线）下标前移
                            line[edgenum--] = line[0];
                            break; }
                        }
                    }
                    ui->label->setText("请选择要删除路径的第一个点");
                    if (edgenum == t3) QMessageBox::warning(this, "警告", "找不到这条路径");
                    else break;
                }
            }
            update(); break;
        case 7://编辑点的标签
            if (pointnum <= 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= pointnum; i++)
                    if (isin(temp, P[i]))
                    {
                        //更新当前点信息
                        ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                        ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                        ui->textEdit->setText(Pl[i]);

                        QString s0 = QInputDialog::getText(this, "编辑标签", "输入文本(最多13个字)");
                        if (s0 != "") Pl[i] = s0.left(13);

                        //更新下拉框中的点信息，在右侧下拉框中删除点，先删除所有点，再添加点
                        while(ui->comboBox->count())
                        {
                             ui->comboBox->removeItem(0);
                             ui->comboBox_2->removeItem(0);
                        }
                        for(int i = 1; i <= pointnum; ++i)
                        {
                            ui->comboBox->addItem(Pl[i]);
                            ui->comboBox_2->addItem(Pl[i]);
                        }

                        break;
                    }
            break;
        case 8://选择起点
            for (int i = 1; i <= pointnum; i++)
                if (isin(temp, P[i]))
                {
                    //更新当前点信息
                    ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                    ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                    ui->textEdit->setText(Pl[i]);

                    P1 = P[i]; tp = 9; ui->label->setText("请选择终点");
                    currLine.a = i;//起点下标赋给temp1（当前线）
                    ui->label_4->setText("起点：" + Pl[i]);
                    ui->label_5->setText("终点：");
                    break;
                } break;
        case 9://选择终点
            for (int i = 1; i <= pointnum; i++)
                if (P[i] != P1 && isin(temp, P[i]))//判断不与起点重合
                {
                    //更新当前点信息
                    ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                    ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                    ui->textEdit->setText(Pl[i]);

                    P2 = P[i];
                    currLine.b = i;//终点下标赋给temp1
                    ui->label_5->setText("终点：" + Pl[i]);
                    ui->listWidget->clear();
                    ways = 0;
                    min = 0;
                    DFS(currLine.a, currLine.b);
                    if (ways)//若有路
                    {
                        if (ways > 200000) ui->listWidget->addItem("路径数过多，超过200000条，无法完全显示！最短路径为：" + shortestStack.getstr() + "，长度为：" + QString::number(min));
                        else ui->listWidget->addItem("共" + QString::number(ways) + "条路径，其中最短路径为：" + shortestStack.getstr() + "，长度为：" + QString::number(min));
                        shortestStack.showline();//最短路径展示
                        update();
                    }
                    else ui->listWidget->addItem("找不到路径");
                    tp = 0;
                    ui->label->setText("点击任一点以查看详细信息"); break;
                }
            break;
        case 10://编辑路径长度第一个点
            if (edgenum <= 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= pointnum; i++)
                    if (isin(temp, P[i]))//选中
                    {
                        //更新当前点信息
                        ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                        ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                        ui->textEdit->setText(Pl[i]);

                        P1 = P[i]; tp = 11; ui->label->setText("请选择要编辑路径长度的第二个点");//转入下一个case
                        currLine.a = i;
                        break;
                    } break;
        case 11://编辑路径长度第二个点
            for (int i = 1; i <= pointnum; i++)
                if (P[i] != P1 && isin(temp, P[i]))//不与第一个点重合
                {
                    //更新当前点信息
                    ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                    ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                    ui->textEdit->setText(Pl[i]);

                    P2 = P[i];
                    currLine.b = i;
                    tp = 10;
//                    if (currLine.a > currLine.b)//保证线的第二个点下标大于第一个
//                    {
//                        int t1 = currLine.a; currLine.a = currLine.b; currLine.b = t1;
//                    }
                    bool f0 = false;
                    for (int j = 1; j <= edgenum; j++)
                    {
                        if (currLine.a == line[j].a && currLine.b == line[j].b)
                        {
                            double number = QInputDialog::getDouble(this, "编辑长度", "输入浮点数(0.0001~999999)", matrix[currLine.a][currLine.b], 0.0001, 999999, 4);
                            if (number) matrix[currLine.a][currLine.b] = number;//若输入了数，则点之间长度更改
                            f0 = true;
                            break;
                        }
                    }
                    ui->label->setText("请选择要编辑路径长度的第一个点");
                    if (!f0) QMessageBox::warning(this, "警告", "找不到这条路径");
                    update();
                    break;
                }
            break;
        default://查找有无鼠标点击的点，在右侧显示出标签和经纬度
            for(int i = 1; i <= pointnum; i++)
                if(isin(temp, P[i]))//显示相关信息
                {
                    ui->textEdit_3->setText(QString::number(locations[i].latitude, 'f', 10));
                    ui->textEdit_2->setText(QString::number(locations[i].longitude, 'f', 10));
                    ui->textEdit->setText(Pl[i]);
                }
            break;
        }
    }
}

//右侧下拉框中起点和终点调用dij求最短路
void MapEditor::on_pushButton_21_clicked()
{
    clr();
//    shortestStack.removeAll();//最短路栈清空
    if (edgenum == 0) { QMessageBox::warning(this, "警告", "无任何路径"); return; }//判断整个地图是否存在路径
    QString begin = ui->comboBox->currentText();
    QString end = ui->comboBox_2->currentText();
    //如果不排除起点终点重合的情况会导致最短路径显示为0
    if(begin == end) {QMessageBox::warning(this, "警告", "起点终点无法重合"); return;}
    ui->label_4->setText("起点：" + begin);
    ui->listWidget->clear();
    ui->label_5->setText("终点：" + end);
    ui->listWidget->addItem("搜索结果将会显示在这里");
    for (int i = 1; i <= pointnum; i++)
    {
        if (begin == Pl[i])//查找起点
        {
            P3 = P[i];
            currLine.a = i;//起点下标赋给currLine（当前线）
        }
        else if (end == Pl[i])//查找终点
        {
            P4 = P[i];
            currLine.b = i;//终点下标赋给currLine（当前线）
        }
    }

    Dijkstra(currLine.a, currLine.b);

    if (waysDij)//若有路
    {
        ui->listWidget->addItem("最短路径为：" + shortestDij.getstr() + "，长度为：" + QString::number(mindis));
        shortestDij.showline();//最短路径展示
        update();
    }
    else ui->listWidget->addItem("找不到路径");
}

//右侧下拉框选中起点和终点调用dfs求所有路径和最短路
void MapEditor::on_pushButton_20_clicked()
{
    clr();
//    shortestStack.removeAll();//最短路栈清空
    if (edgenum == 0) { QMessageBox::warning(this, "警告", "无任何路径"); return; }//判断整个地图是否存在路径
    QString begin = ui->comboBox->currentText();
    QString end = ui->comboBox_2->currentText();
    //如果不排除起点终点重合的情况会导致最短路径显示为0
    if(begin == end) {QMessageBox::warning(this, "警告", "起点终点无法重合"); return;}
    ui->label_4->setText("起点：" + begin);
    ui->listWidget->clear();
    ui->label_5->setText("终点：" + end);
    ui->listWidget->addItem("搜索结果将会显示在这里");
    for (int i = 1; i <= pointnum; i++)
    {
        if (begin == Pl[i])//查找起点
        {
            P3 = P[i];
            currLine.a = i;//起点下标赋给currLine（当前线）
        }
        else if (end == Pl[i])//查找终点
        {
            P4 = P[i];
            currLine.b = i;//终点下标赋给currLine（当前线）
        }
    }
    ways = 0;
    min = 0;
    DFS(currLine.a, currLine.b);
    if (ways)//若有路
    {
        if (ways > 200000) ui->listWidget->addItem("路径数过多，超过200000条，无法完全显示！最短路径为：" + shortestStack.getstr() + "，长度为：" + QString::number(min));
        else ui->listWidget->addItem("共" + QString::number(ways) + "条路径，其中最短路径为：" + shortestStack.getstr() + "，长度为：" + QString::number(min));
        shortestStack.showline();//最短路径展示
        update();
    }
    else ui->listWidget->addItem("找不到路径");
}
//右侧修改点的经度
void MapEditor::on_pushButton_14_clicked()
{
    for(int i = 1; i <= pointnum; ++i)
    {
        if(Pl[i] == ui->textEdit->toPlainText())//当前编辑的点下标是i
        {
            QString lo = ui->textEdit_2->toPlainText();
            locations[i].longitude = lo.toDouble();
            QMessageBox::warning(this, "提示", "修改经度成功");
            //修改与该点相连的所有边的长度
            for(int j = 1; j <= pointnum; j++)//查找与该点相连的点
            {
                if(matrix[i][j] != 0)//存在从点i（被修改的点）到点j的路径
                {
                    double temp = calDist(locations[i].latitude, locations[i].longitude, locations[j].latitude, locations[j].longitude);
                    if(temp == 0) QMessageBox::warning(this, "警告", "与现有点经纬度重合，路径不做修改");
                    else {
                        matrix[i][j] = temp;
                        //QMessageBox::warning(this, "提示", "路径长度更新完毕");
                    }
                }
                if(matrix[j][i] != 0)//存在从点j到点i（被修改的点）的路径
                {
                    double temp = calDist(locations[i].latitude, locations[i].longitude, locations[j].latitude, locations[j].longitude);
                    if(temp == 0) QMessageBox::warning(this, "警告", "与现有点经纬度重合，路径不做修改");
                    else {
                        matrix[j][i] = temp;
                        //QMessageBox::warning(this, "提示", "路径长度更新完毕");
                    }
                }
            }
            QMessageBox::warning(this, "提示", "路径长度更新完毕");
            update();
            break;
        }
        else if(i == pointnum && Pl[i] != ui->textEdit->toPlainText())
             QMessageBox::warning(this, "警告", "找不到该点");
    }
}
//右侧修改点的纬度
void MapEditor::on_pushButton_19_clicked()
{
    for(int i = 1; i <= pointnum; ++i)
    {
        if(Pl[i] == ui->textEdit->toPlainText())
        {
            QString la = ui->textEdit_3->toPlainText();
            locations[i].latitude = la.toDouble();
            QMessageBox::warning(this, "提示", "修改纬度成功");
            //修改与该点相连的所有边的长度
            for(int j = 1; j <= pointnum; j++)//查找与该点相连的点
            {
                if(matrix[i][j] != 0)//存在从点i（被修改的点）到点j的路径
                {
                    double temp = calDist(locations[i].latitude, locations[i].longitude, locations[j].latitude, locations[j].longitude);
                    if(temp == 0) QMessageBox::warning(this, "警告", "与现有点经纬度重合，路径不做修改");
                    else {
                        matrix[i][j] = temp;
                        //QMessageBox::warning(this, "提示", "路径长度更新完毕");
                    }
                }
                if(matrix[j][i] != 0)//存在从点j到点i（被修改的点）的路径
                {
                    double temp = calDist(locations[i].latitude, locations[i].longitude, locations[j].latitude, locations[j].longitude);
                    if(temp == 0) QMessageBox::warning(this, "警告", "与现有点经纬度重合，路径不做修改");
                    else {
                        matrix[j][i] = temp;
                        //QMessageBox::warning(this, "提示", "路径长度更新完毕");
                    }
                }
            }
            QMessageBox::warning(this, "提示", "路径长度更新完毕");
            update();
            break;
        }
       else if(i == pointnum && Pl[i] != ui->textEdit->toPlainText())
            QMessageBox::warning(this, "警告", "找不到该点");
   }
}
void MapEditor::on_pushButton_clicked()
{
    clr();
    if (tp != 3) tp = 3, ui->label->setText("请选择一个位置添加点");//转到case 3
    else tp = 0, ui->label->setText("点击任一点以查看详细信息");//跳出
}

void MapEditor::on_pushButton_2_clicked()
{
    clr();
    if (tp != 1) tp = 1, ui->label->setText("请选择第一个点");//转到case 1
    else tp = 0, ui->label->setText("点击任一点以查看详细信息");//跳出
}

void MapEditor::on_pushButton_3_clicked()
{
    clr();
    if (tp != 4) tp = 4, ui->label->setText("请选择一个位置删除点");//转到case 4
    else tp = 0, ui->label->setText("点击任一点以查看详细信息");//跳出
}

void MapEditor::on_pushButton_4_clicked()
{
    clr();
    if (tp != 5) tp = 5, ui->label->setText("请选择要删除路径的第一个点");//转到case 5
    else tp = 0, ui->label->setText("点击任一点以查看详细信息");//跳出
}

void MapEditor::on_pushButton_7_clicked()
{
    clr();
    if (tp != 7) tp = 7, ui->label->setText("请选择要编辑标签的点");//转到case 7
    else tp = 0, ui->label->setText("点击任一点以查看详细信息");//跳出
}

void MapEditor::on_pushButton_6_clicked()
{
    clr();
    if (tp != 8) {
        if (edgenum == 0) { QMessageBox::warning(this, "警告", "无任何路径"); return; }//判断整个地图是否存在路径
        tp = 8; ui->label->setText("请选择起点");//转到case 8
        ui->label_4->setText("起点："); ui->listWidget->clear();
        ui->label_5->setText("");
        ui->listWidget->addItem("搜索结果将会显示在这里");
    }
    else tp = 0, ui->label->setText("");//跳出
}

void MapEditor::on_pushButton_8_clicked()
{
    if (!showlen) showlen = true, ui->pushButton_8->setText("隐藏路径长");
    else showlen = false, ui->pushButton_8->setText("显示路径长");//每点一下切换状态
    update();
}

void MapEditor::on_pushButton_5_clicked()
{
    clr();
    if (tp != 10) tp = 10, ui->label->setText("请选择要编辑路径长度的第一个点");//转到case 10
    else tp = 0, ui->label->setText("点击任一点以查看详细信息");//跳出
}

void MapEditor::on_pushButton_9_clicked()
{
    QString s0 = QInputDialog::getText(this, "编辑标题", "输入文本(最多28个字)", QLineEdit::Normal, ui->label_6->text());
    if (s0 != "") ui->label_6->setText(s0.left(28));//跳出
}

void MapEditor::on_pushButton_10_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "提示", "确认要清除地图吗？", QMessageBox::Yes | QMessageBox::No);
    if (btn == QMessageBox::Yes)//清除地图
    {
        pic = "";
        for (int i = 1; i <= pointnum; i++)
        {
            P[i] = P[0];
            Pl[i] = Pl[0];
            for (int j = 1; j <= pointnum; j++)
                matrix[i][j] = 0;
            //清空经纬度信息
            locations[i].latitude = locations[0].latitude;
            locations[i].longitude = locations[0].longitude;
        }
        for (int i = 1; i <= edgenum; i++)
            line[i] = line[0];
        tp = pointnum = edgenum = count = 0;

        //清除右侧显示点的三个信息
        ui->textEdit_3->setText("");
        ui->textEdit_2->setText("");
        ui->textEdit->setText("");
        //在右侧下拉框中删除所有点
        while(ui->comboBox->count())
        {
             ui->comboBox->removeItem(0);
             ui->comboBox_2->removeItem(0);
        }

        clr();
        ui->label->setText("");
    }
}

void MapEditor::on_pushButton_13_clicked()//改背景
{
    QString temp = QFileDialog::getOpenFileName(this, "选择文件", "D:/", "图像文件(*.jpg *.jpeg *.bmg *.png *.gif)");
    if (temp != "") pic = temp;//传入图片存储路径
    update();
}

void MapEditor::on_pushButton_12_clicked()//保存地图
{
    using namespace std;
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", "", "地图文件(*.map2)");//文件扩展名为.map2
    if (filename != "")//判断地址是否输入成功
    {
        ofstream out(filename.toStdString());//转换为标准字符串进行保存
        if (out.is_open())
        {
            out << ui->label_6->text().toStdString() << endl;//地图标题
            out << edgenum << ' ' << pointnum << endl;
            for (int i = 1; i <= pointnum; i++)
                out << P[i].x() << ' ' << P[i].y() << ' ' << Pl[i].toStdString() << ' ' << locations[i].latitude << ' ' << locations[i].longitude << endl;//空格隔开
            for (int i = 1; i <= pointnum; i++)
            {
                for (int j = 1; j <= pointnum; j++)
                    out << matrix[i][j] << ' ';
                out << endl;
            }
            for (int i = 1; i <= edgenum; i++)
                out << line[i].a << ' ' << line[i].b << endl;
            out << pic.toStdString() << endl;
            QMessageBox::information(this, "提示", "保存成功");
            out.close();//关闭文档
        }
        else QMessageBox::information(this, "提示", "保存失败");
    }
}

void MapEditor::on_pushButton_11_clicked()//载入地图
{
//    using namespace std;
    QString filename = QFileDialog::getOpenFileName(this, "选择文件", "", "地图文件(*.map2)");
    if (filename != "")
    {
        std::ifstream in(filename.toStdString());
        if (in.is_open())
        {
            //先清除现有地图和所有数据
            pic = "";
            for (int i = 1; i <= pointnum; i++)
            {
                P[i] = P[0];
                Pl[i] = Pl[0];
                for (int j = 1; j <= pointnum; j++)
                    matrix[i][j] = 0;
            }
            for (int i = 1; i <= edgenum; i++)
                line[i] = line[0];
            tp = pointnum = edgenum = count = 0;

            //清除右侧显示点的三个信息
            ui->textEdit_3->setText("");
            ui->textEdit_2->setText("");
            ui->textEdit->setText("");
            //在右侧下拉框中删除所有点
            while(ui->comboBox->count())
            {
                 ui->comboBox->removeItem(0);
                 ui->comboBox_2->removeItem(0);
            }

            //读入新地图
            std::string c;
            in >> c;
            ui->label_6->setText(QString::fromStdString(c));//转变为Qstring，读入标题
            in >> edgenum >> pointnum;
            for (int i = 1; i <= pointnum; i++)//初始化点的标签
            {
                int a, b;
                in >> a >> b;
                P[i].setX(a);
                P[i].setY(b);
                in >> c;
                Pl[i] = QString::fromStdString(c);
                double la, lo;
                in >> la >> lo;
                locations[i].latitude = la;
                locations[i].longitude = lo;
            }
            for (int i = 1; i <= pointnum; i++)
                for (int j = 1; j <= pointnum; j++)
                    in >> matrix[i][j];//初始化邻接矩阵
            for (int i = 1; i <= edgenum; i++)
                in >> line[i].a >> line[i].b;//初始化边数组
            in >> c;
            pic = QString::fromStdString(c);//初始化背景图
            //初始化右侧两个下拉框，将所有点加入
            for(int i = 1; i <= pointnum; ++i)
            {
                ui->comboBox->addItem(Pl[i]);
                ui->comboBox_2->addItem(Pl[i]);
            }

            clr();
            QMessageBox::information(this, "提示", "读取成功");
            in.close();//关闭文件
        }
        else QMessageBox::information(this, "提示", "读取失败");
    }
}
