#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget* parent) : QWidget(parent),
                                  ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("TCP Client");

    m_tcpclient = new QTcpSocket(this);

    ui->edit_msg->installEventFilter(this);

    connect(ui->btn_connect, &QPushButton::clicked, [=](bool checked) {
        Q_UNUSED(checked);
        switch (m_tcpclient->state()) {
            // connect tcp server
            case QTcpSocket::UnconnectedState: {
                // split ip address and port
                QStringList sercfg = ui->edit_server->text().split(',');
                // connect to tcpserver
                if (sercfg.count() == 2) {
                    m_tcpclient->connectToHost(/* ip */ sercfg[0], /* port */ sercfg[1].toInt());
                }
                break;
            }
            // disconnect tcp server
            default:
            case QTcpSocket::ConnectedState: {
                m_tcpclient->close();
                break;
            }
        }
        qDebug() << m_tcpclient->state();
    });

    connect(m_tcpclient, &QTcpSocket::connected, [=]() {
        appendMsg("server connected");
        ui->btn_connect->setText("disconnect");
    });
    connect(m_tcpclient, &QTcpSocket::disconnected, [=]() {
        appendMsg("server disconnected");
        ui->btn_connect->setText("connect");
    });
    connect(m_tcpclient, &QTcpSocket::readyRead, []() {});

    setAcceptDrops(true);
}

Widget::~Widget()
{
    delete ui;
}

// 拖放文件到进入窗口
void Widget::dragEnterEvent(QDragEnterEvent* event)
{
    event->mimeData()->hasUrls() ? event->acceptProposedAction() : event->ignore();
}

// 拖放文件在窗口中移动
void Widget::dragMoveEvent(QDragMoveEvent* event)
{
    Q_UNUSED(event);
}

// 拖放文件在窗口释放
void Widget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        Q_FOREACH (auto url, mimeData->urls()) {
            uploadFile(url.toLocalFile());
        }
    }
}

bool Widget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->edit_msg) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            if (keyEvent->matches(QKeySequence::Paste)) {
                QClipboard* clipboard = QApplication::clipboard();

                if (clipboard->mimeData()->hasText()) {
                    qDebug() << clipboard->mimeData()->text();
                }

                if (clipboard->mimeData()->hasUrls()) {
                    Q_FOREACH (auto url, clipboard->mimeData()->urls()) {
                        uploadFile(url.toLocalFile());
                    }
                }

                clipboard->clear();

                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, event);
}

#include <QThread>
bool Widget::uploadFile(QString filepath)
{

    if(m_tcpclient->state() != QTcpSocket::ConnectedState){
        return false;
    }

    QFile file(filepath);

    if (!file.exists(filepath) /* 文件不存在 */ ||
         file.size() == 0 /* 空文件 */) {
        return false;
    }



    QFileInfo fileinfo(filepath);

    // get file info

    {
        float   filesize = fileinfo.size();
        QString filename = fileinfo.fileName();

        uint8_t        idx    = 0;
        static QString unit[] = {"B", "KB", "MB", "GB"};

        while (filesize > 1024) {
            filesize /= 1024;
            ++idx;
        }

        appendMsg(QString("%1(%2%3)").arg(filename).arg(filesize).arg(unit[idx]));
    }



    /////////////////////////////////////////////////////////

    auto cbk_tx = [=](MsgType type, std::function<void(QDataStream& stream)> cb_data = nullptr) -> bool {

        QByteArray DataInfoBlock;
        QDataStream stream(&DataInfoBlock, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_14);

        stream << (qint8)(type);
        if(cb_data != nullptr){
            cb_data(stream);
        }

        m_tcpclient->write(DataInfoBlock); // send data

        QThread::usleep(3); // wait for client recvice
        if (!m_tcpclient->waitForBytesWritten(1e3)) {
            appendMsg(QString("timeout: %1").arg(m_tcpclient->errorString()));
            return false;
        }

        return true;
    };


    // 文件打开失败
    if(!file.open(QIODevice::ReadOnly)){
        appendMsg("Fail to open file");
        return false;
    }


    // send file info

    if(cbk_tx(MsgType::FileInfo, [&](QDataStream& stream){stream << fileinfo.fileName() << fileinfo.size();})) {

        // send file data
        qint64 bytesWritten = 0; // 已发送字节数
        qint64 fileSize = file.size(); // 要发送字节数
        qint64 payloadSize = qMin(fileSize,qint64(512)); // 单次发送字节数

        while( bytesWritten < fileSize ){

            QByteArray filedata = file.read(qMin(payloadSize,fileSize - bytesWritten));

            if( !cbk_tx(MsgType::FileData, [&](QDataStream& stream){stream << filedata;})) goto send_fail;

            bytesWritten += filedata.size();
            ui->progress->setValue((int) (double)bytesWritten / (double)fileSize * 100); // 进度
        }


    }

    if( cbk_tx(MsgType::FileOver) ){
        appendMsg("Success to Send");
        file.close();
        return true;
    }else{
send_fail:
        appendMsg("Fail to Send");
        file.close();
        return false;
    }

}

void Widget::appendMsg(QString msg){
    // QDateTime::currentDataTime().toString("yyyy-MM-dd hh:mm:ss")
    ui->edit_msg->append(QString("[%1] %2").
                         arg(QDateTime::currentDateTime().toString("hh:mm:ss")).
                         arg(msg));
}

