#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString chatURL;
    QString promptBase;

private slots:
    void on_pushButton_clicked();
    void OnGetResponse(QNetworkReply *rep);
    void sendChatMessage();
    bool eventFilter(QObject *target, QEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif
