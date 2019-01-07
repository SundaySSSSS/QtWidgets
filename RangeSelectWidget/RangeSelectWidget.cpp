#include "RangeSelectWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

RangeSelectWidget::RangeSelectWidget(QWidget *parent) : QWidget(parent)
{
    m_leftRightSpace = 5;
    m_handleWidth = 10;
    m_handleHeight = 10;
    m_minVal = 0;
    m_maxVal = 100;
    m_selectMinVal = 20;
    m_selectMaxVal = 80;
    m_barNoSelectColor = QColor(200, 200, 200);  //没有选择的颜色
    m_barSelectColor = QColor(100, 100, 100);  //被选择的颜色
    m_handleColor = Qt::red;

    m_isPressUpHandle = false;
    m_isPressDownHandle = false;

    //限制控件的最小尺寸, 防止无限制缩小
    this->setMinimumHeight(m_handleHeight * 3);
    this->setMinimumWidth(m_leftRightSpace * 10);

    calcUIRect();
}

void RangeSelectWidget::setColor(QColor noSelectionColor, QColor selectionColor, QColor handleColor)
{
    m_barNoSelectColor = noSelectionColor;
    m_barSelectColor = selectionColor;
    m_handleColor = handleColor;
    update();
}

bool RangeSelectWidget::setMinMax(double min, double max)
{
    if (min >= max)
    {
        return false;
    }
    m_minVal = min;
    m_maxVal = max;
    return true;
}

void RangeSelectWidget::getMinMax(double &min, double &max)
{
    min = m_minVal;
    max = m_maxVal;
}

void RangeSelectWidget::setSelection(double selectMin, double selectMax)
{
    m_selectMinVal = selectMin;
    if (m_selectMinVal < m_minVal)
    {
        m_selectMinVal = m_minVal;
    }
    m_selectMaxVal = selectMax;
    if (m_selectMaxVal > m_maxVal)
    {
        m_selectMaxVal = m_maxVal;
    }
    update();
}

void RangeSelectWidget::getSelection(double &selectMin, double &selectMax)
{
    selectMin = m_selectMinVal;
    selectMax = m_selectMaxVal;
}

void RangeSelectWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    calcUIRect();
    QPainter painter(this);
    painter.setPen(QColor(255, 0, 0));
    drawBackground(painter, m_barRect);
    drawSelectPart(painter, m_barRect);
    drawUpHandle(painter, m_upHandleRect);
    drawDownHandle(painter, m_downHandleRect);
}

void RangeSelectWidget::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        if (m_upHandleRect.contains(event->pos()))
        {
            m_isPressUpHandle = true;
        }
        else if (m_downHandleRect.contains(event->pos()))
        {
            m_isPressDownHandle = true;
        }
    }
    update();
}

void RangeSelectWidget::mouseMoveEvent(QMouseEvent *event)
{
    int eventPosX = event->pos().x();
    if (event->pos().x() < m_barRect.left())
    {
        eventPosX = m_barRect.left();
    }
    else if (event->pos().x() > m_barRect.right())
    {
        eventPosX = m_barRect.right();
    }

    if (m_isPressUpHandle)
    {
        m_selectMinVal = (m_maxVal - m_minVal) * (eventPosX - m_barRect.left()) / m_barRect.width();
        if (m_selectMinVal > m_selectMaxVal)
        {
            m_selectMinVal = m_selectMaxVal;
        }
        update();
    }
    else if (m_isPressDownHandle)
    {
        m_selectMaxVal = (m_maxVal - m_minVal) * (eventPosX - m_barRect.left()) / m_barRect.width();
        if (m_selectMaxVal < m_selectMinVal)
        {
            m_selectMaxVal = m_selectMinVal;
        }
        update();
    }
    emit sendSelectMinMaxChanged(m_selectMinVal, m_selectMaxVal);
}

void RangeSelectWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_isPressDownHandle = false;
    m_isPressUpHandle = false;
    update();
}

void RangeSelectWidget::drawBackground(QPainter &p, const QRectF &barRect)
{
    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(m_barNoSelectColor));
    p.drawRoundedRect(barRect, 5, 5);
    p.restore();
}

void RangeSelectWidget::drawSelectPart(QPainter &p, const QRectF &barRect)
{
    p.save();
    p.setPen(Qt::NoPen);
    double startPos = (m_selectMinVal - m_minVal) / (m_maxVal - m_minVal) * barRect.width() + m_leftRightSpace;
    double stopPos = (m_selectMaxVal - m_minVal) / (m_maxVal - m_minVal) * barRect.width() + m_leftRightSpace;
    p.setBrush(QBrush(m_barSelectColor));
    QRectF selectRect = QRectF(startPos, barRect.top(), stopPos - startPos, barRect.height());
    if (selectRect.width() < 1)
    {   //防止选择区域过小而看不见
        selectRect.setWidth(1);
    }
    p.drawRoundedRect(selectRect, 5, 5);
    p.restore();
}

void RangeSelectWidget::drawUpHandle(QPainter &p, QRectF &upHandleRect)
{
    p.save();
    p.setPen(Qt::NoPen);
    double top = upHandleRect.top();
    double bottom = upHandleRect.bottom();
    double centerPos = upHandleRect.center().x();
    QPointF points[3] =
    {
        QPointF(centerPos - m_handleWidth / 2, top),
        QPointF(centerPos + m_handleWidth / 2, top),
        QPointF(centerPos, bottom),
    };
    p.setBrush(QBrush(m_handleColor));
    p.drawPolygon(points, 3);
    p.restore();
}

void RangeSelectWidget::drawDownHandle(QPainter &p, QRectF &downHandleRect)
{
    p.save();
    p.setPen(Qt::NoPen);
    double top = downHandleRect.top();
    double bottom = downHandleRect.bottom();
    double centerPos = downHandleRect.center().x();
    QPointF points[3] = {
        QPointF(centerPos - m_handleWidth / 2, bottom),
        QPointF(centerPos + m_handleWidth / 2, bottom),
        QPointF(centerPos, top),
    };
    p.setBrush(QBrush(m_handleColor));
    p.drawPolygon(points, 3);
    p.restore();
}

void RangeSelectWidget::calcUIRect()
{
    m_barRect = QRectF(m_leftRightSpace, m_handleHeight, width() - 2 * m_leftRightSpace, height() - 2 * m_handleHeight);
    m_upHandleRangeRect = QRectF(m_leftRightSpace, 0, width() - 2 * m_leftRightSpace, m_handleHeight);
    m_downHandleRangeRect = QRectF(m_leftRightSpace, height() - m_handleHeight, width() - 2 * m_leftRightSpace, m_handleHeight);

    double minCenterPos = (m_selectMinVal - m_minVal) / (m_maxVal - m_minVal) * m_barRect.width() + m_leftRightSpace;
    m_upHandleRect = QRectF(minCenterPos - m_handleWidth / 2, m_upHandleRangeRect.top(),
                            m_handleWidth, m_handleHeight);
    double maxCenterPos = (m_selectMaxVal - m_minVal) / (m_maxVal - m_minVal) * m_barRect.width() + m_leftRightSpace;
    m_downHandleRect = QRectF(maxCenterPos - m_handleWidth / 2, m_downHandleRangeRect.top(),
                              m_handleWidth, m_handleHeight);
}

