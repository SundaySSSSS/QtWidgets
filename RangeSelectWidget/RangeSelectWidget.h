#ifndef RANGESELECTWIDGET_H
#define RANGESELECTWIDGET_H

#include <QWidget>

class RangeSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RangeSelectWidget(QWidget *parent = 0);

    //设置控件颜色
    void setColor(QColor noSelectionColor, QColor selectionColor,
                  QColor handleColor = Qt::red);

    //设置整体范围的最大最小值
    bool setMinMax(double min, double max);
    //获取整体范围的最大最小值
    void getMinMax(double& min, double& max);

    //设置当前选择的范围
    void setSelection(double selectMin, double selectMax);
    //获取当前选择的范围
    void getSelection(double& selectMin, double& selectMax);

private:
    double m_leftRightSpace;    //进度条的左右留白
    double m_handleWidth;   //操作柄宽度
    double m_handleHeight;  //操作柄高度
    double m_minVal;   //范围最小值
    double m_maxVal;   //范围最大值
    double m_selectMinVal; //当前选择范围的最小值
    double m_selectMaxVal; //当前选择范围的最大值

    QColor m_barNoSelectColor;  //没有选择的颜色
    QColor m_barSelectColor;    //被选择的颜色
    QColor m_handleColor;   //操作柄颜色

    QRectF m_barRect;         //整体显示条
    QRectF m_upHandleRangeRect;       //上操作柄显示范围
    QRectF m_downHandleRangeRect;     //下操作柄显示范围

    QRectF m_upHandleRect;      //上操作柄位置
    QRectF m_downHandleRect;    //下操作柄位置

    bool m_isPressUpHandle; //是否按下了上边的操作柄
    bool m_isPressDownHandle;   //是否按下了下边的操作柄

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void drawBackground(QPainter& p, const QRectF& barRect);    //描画整体背景
    void drawSelectPart(QPainter& p, const QRectF& barRect);    //描画选择的范围
    void drawUpHandle(QPainter& p, QRectF& upHandleRect);    //描绘操作柄
    void drawDownHandle(QPainter& p, QRectF& downHandleRect);

    void calcUIRect();
signals:
    void sendSelectMinMaxChanged(double min, double max);

public slots:
};

#endif // RANGESELECTWIDGET_H
