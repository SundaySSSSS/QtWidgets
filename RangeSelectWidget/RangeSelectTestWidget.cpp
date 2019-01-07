#include "widget.h"
#include "ui_RangeSelectTestWidget.h"
#include "RangeSelectTestWidget.h"
#include <QDebug>
#include <QMessageBox>

RangeSelectTestWidget::RangeSelectTestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RangeSelectTestWidget)
{
    ui->setupUi(this);
    m_pSelectRangeWidget = new RangeSelectWidget(this);
    QVBoxLayout* pVLayout = new QVBoxLayout();
    pVLayout->addWidget(m_pSelectRangeWidget);
    ui->frame->setLayout(pVLayout);
    m_pSelectRangeWidget->setMinMax(0, 1000);
    m_pSelectRangeWidget->setSelection(100.0, 900.0);
    ui->lineEdit_Start->setText(QString::number(100.0));
    ui->lineEdit_Len->setText(QString::number(800.0));

    connect(m_pSelectRangeWidget, SIGNAL(sendSelectMinMaxChanged(double,double)),
            this, SLOT(recvSelectMaxMinChangedSlot(double,double)));
    connect(ui->lineEdit_Start, SIGNAL(editingFinished()),
            this, SLOT(recvLineEditFinishSlot()));
    connect(ui->lineEdit_Len, SIGNAL(editingFinished()),
            this, SLOT(recvLineEditFinishSlot()));
}

RangeSelectTestWidget::~RangeSelectTestWidget()
{
    delete ui;
}

bool RangeSelectTestWidget::checkStartLenValid(double start, double len)
{
    if (len < 0)
    {
        return false;
    }

    double max = 0;
    double min = 0;
    double selectMin = 0;
    double selectMax = 0;
    m_pSelectRangeWidget->getMinMax(min, max);
    m_pSelectRangeWidget->getSelection(selectMin, selectMax);

    //校验结果是否合理
    if (start + len > max || start < min)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void RangeSelectTestWidget::recvSelectMaxMinChangedSlot(double min, double max)
{
    ui->lineEdit_Start->setText(QString::number(min));
    ui->lineEdit_Len->setText(QString::number(max - min));
}

void RangeSelectTestWidget::recvLineEditFinishSlot()
{
    qDebug() << "line Edit Finished";
    double startPos = ui->lineEdit_Start->text().toDouble();
    double len = ui->lineEdit_Len->text().toDouble();
    if (checkStartLenValid(startPos, len))
    {
        m_pSelectRangeWidget->setSelection(startPos, startPos + len);
    }
    else
    {
        QMessageBox::warning(this, "错误", "输入值不合法");
    }
}
