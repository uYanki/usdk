#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QTime>

#include <QDebug>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>

#include <QClipboard>

#include <QDateTime>

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

    QTcpSocket* m_tcpclient;

    void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent* event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;

    bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

    void appendMsg(QString msg);
    bool uploadFile(QString filepath);

};


#endif  // CLIENT_H
