#include "widget.h"
#include "ui_widget.h"
#include "RangeSelectWidget/RangeSelectTestWidget.h"
#include "IPAddressWidget/IPAddressTest.h"
#include "ToastWidget/Toast.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_ShowRangeSelectWidget_clicked()
{
    static RangeSelectTestWidget widget;
    widget.show();
}

void Widget::on_pushButton_showIPAddressWidget_clicked()
{
    static IPAddressTest widget;
    widget.show();
}

void Widget::on_pushButton_ShowToast_clicked()
{
    static Toast toast("提示：这是一个会自动消失，且没有焦点的窗口", this);
    toast.start();
}
