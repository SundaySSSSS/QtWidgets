#include "Toast.h"
#include <QVBoxLayout>
#include <QLabel>

Toast::Toast(QString strText, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(new QLabel(strText));
    this->setLayout(pLayout);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint |
                         Qt::WindowDoesNotAcceptFocus);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
}

void Toast::start()
{
    this->show();
    m_timer.start(2000);
}

void Toast::slot_timeout()
{
    this->hide();
}

