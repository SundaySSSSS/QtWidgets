#include "Toast.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>

Toast::Toast(QString strText, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(new QLabel(strText));
    this->setLayout(pLayout);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint |
                         Qt::WindowDoesNotAcceptFocus |
                         Qt::Popup);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
}

void Toast::start()
{
    this->move((QApplication::desktop()->width() - this->width())/2,
               (QApplication::desktop()->height() - this->height())/2);
    this->show();
    m_timer.start(2000);
}

void Toast::slot_timeout()
{
    this->hide();
}

