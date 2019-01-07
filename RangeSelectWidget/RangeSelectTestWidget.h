#ifndef RANGESELECTTESTWIDGET_H
#define RANGESELECTTESTWIDGET_H

#include <QWidget>
#include "RangeSelectWidget.h"

namespace Ui {
class RangeSelectTestWidget;
}

class RangeSelectTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RangeSelectTestWidget(QWidget *parent = 0);
    ~RangeSelectTestWidget();

private:
    Ui::RangeSelectTestWidget *ui;
    RangeSelectWidget* m_pSelectRangeWidget;

    //判断界面上的起始和长度是否合理
    bool checkStartLenValid(double start, double len);

private slots:
    void recvSelectMaxMinChangedSlot(double min, double max);
    void recvLineEditFinishSlot();
};

#endif // RANGESELECTTESTWIDGET_H
