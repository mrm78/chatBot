#include "qmlwidget.h"
#include <QVBoxLayout>

QmlWidget::QmlWidget(QWidget *parent) : QWidget(parent) {
    qmlWidget = new QQuickWidget(this);
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    qmlWidget->setSource(QUrl("app.qml"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(qmlWidget);
    setLayout(layout);
}
