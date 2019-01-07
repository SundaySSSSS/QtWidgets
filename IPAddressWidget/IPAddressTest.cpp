#include "IPAddressTest.h"
#include "IPAddressWidget.h"
#include <QVBoxLayout>

IPAddressTest::IPAddressTest(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    this->setLayout(pVLayout);
    IPAddressWidget* pIPAddressWidget = new IPAddressWidget(this);
    pVLayout->addWidget(pIPAddressWidget);
}

