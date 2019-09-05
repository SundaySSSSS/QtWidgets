#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_ShowRangeSelectWidget_clicked();
    void on_pushButton_showIPAddressWidget_clicked();

    void on_pushButton_ShowToast_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
