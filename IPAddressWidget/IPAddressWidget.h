#ifndef IPADDRESSWIDGET_H
#define IPADDRESSWIDGET_H

#include <QLineEdit>
#include <QEvent>
#include <QRegExpValidator>
#include <QPainter>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QBrush>

class IPAddressWidget : public QLineEdit
{
    Q_OBJECT
public:
    IPAddressWidget(QWidget *parent = 0);
    ~IPAddressWidget();

    void setText(const QString& strIP);
    QString text() const;
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *ev);

    int getIndex(QLineEdit *pEdit);
    bool isTextValid(const QString &strIP);
private:
    QLineEdit *m_lineEidt[4];
};

#endif // IPADDRESSWIDGET_H
