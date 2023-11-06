#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QDebug>

#include <QTcpServer>
#include <QTcpSocket>

#include <QDir>
#include <QFile>
#include <QFileInfo>

enum MsgType {
    FileInfo = 0,  // 文件信息
    FileData = 1,  // 文件数据
    FileOver = 2,
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:

private:
    Ui::Widget* ui;

    QTcpServer* m_tcpserver = Q_NULLPTR;

    void appendMsg(QTcpSocket* client,QString msg);

    QString m_downpath;
    QFile m_downfile;
    qint64  m_filesize = 0;

};

#endif // WIDGET_H
