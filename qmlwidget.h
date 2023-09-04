#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QWidget>
#include <QtQuickWidgets/QQuickWidget>

class QmlWidget : public QWidget {
    Q_OBJECT
public:
    QmlWidget(QWidget *parent = nullptr);

private:
    QQuickWidget *qmlWidget;
};

#endif // QMLWIDGET_H
