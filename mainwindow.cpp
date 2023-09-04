#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QUrlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QtDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
    ui->plainTextEdit->setReadOnly(true);
    promptBase = "\n\n### Instructions:\n%1\n\n### Response:\n";
    // chatURL = "https://webhook.site/268969b6-7537-4762-89b9-def2d39d14c8";
    // chatURL = "http://localhost:8008/api/chat/%1/question";  // serge
    chatURL = "http://0.0.0.0:8080/v1/completions";     // llama-cpp-python

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->sendChatMessage();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            this->sendChatMessage();
            return true;
        }
    }
    return false;
}

void MainWindow::sendChatMessage()
{
    QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(OnGetResponse(QNetworkReply*)));

    QUrl url(chatURL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObject;
    jsonObject["prompt"] = promptBase.arg(ui->textEdit->toPlainText());
    QJsonArray stopArray;
    stopArray.append("\n");
    stopArray.append("###");
    jsonObject["stop"] = stopArray;
    QJsonDocument jsonDoc(jsonObject);
    QByteArray data = jsonDoc.toJson();

    mgr->post(request, data);
    qDebug() << "sent data";

    ui->plainTextEdit->appendPlainText(ui->textEdit->toPlainText());
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void MainWindow::OnGetResponse(QNetworkReply *rep)
{
    qDebug() << "recieve resp";
    QByteArray bts = rep->readAll();
    qDebug() << bts;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(bts);
    QJsonObject jsonObject = jsonResponse.object();
    QJsonValue choicesValue = jsonObject["choices"];
    QJsonObject choiceObject = choicesValue[0].toObject();
    QString text = choiceObject["text"].toString();
    qDebug() << text;
    ui->plainTextEdit->appendPlainText(text);
    ui->plainTextEdit->appendPlainText("");
}
