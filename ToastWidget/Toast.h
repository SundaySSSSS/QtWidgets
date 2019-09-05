#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QTimer>

class Toast : public QWidget
{
    Q_OBJECT
public:
    explicit Toast(QString strText, QWidget *parent = 0);
    void start();

    static void showToast(QString strText, int iShowMSec, QSize size)
    {

    }

private:
    QTimer m_timer;

private slots:
    void slot_timeout();
};

#endif // TOAST_H
