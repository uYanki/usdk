#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("TCP Server");

    m_tcpserver = new QTcpServer(this);
    m_tcpserver->setMaxPendingConnections(10);

    // download dirpath
    QDir dir;
    m_downpath = QCoreApplication::applicationDirPath() + "/download/";
    if (!dir.exists(m_downpath)) dir.mkdir(m_downpath);

    connect(ui->btn_run,&QPushButton::clicked,[=](bool checked){
        Q_UNUSED(checked);
        if(m_tcpserver->isListening()){
            m_tcpserver->close();
            ui->btn_run->setText("run");
        }else{
            m_tcpserver->listen(QHostAddress::Any,ui->spn_ser_port->value());
            ui->btn_run->setText("stop");
        }
    });

    // client connected
    connect(m_tcpserver,&QTcpServer::newConnection,[=](){

        QTcpSocket* client = m_tcpserver->nextPendingConnection();
        appendMsg(client,"connected");

        // client disconnected
        connect(client,&QTcpSocket::disconnected,[=](){
            appendMsg(client,"disconnected");
        });

        // read data
        connect(client,&QTcpSocket::readyRead,[=](){

             qint8 type;
             QDataStream RxDatStream(client);
             RxDatStream.setVersion(QDataStream::Qt_5_14);

             RxDatStream >> type;

             switch ((MsgType)type) {
                 case FileInfo:{

                     QString filename;
                     RxDatStream>>filename>>m_filesize;
                     appendMsg(client,QString("recv file: %1 (%2B)").arg(filename).arg(m_filesize));

                     if(m_downfile.isOpen()){
                        m_downfile.close();
                     }

                     m_downfile.setFileName(m_downpath + filename);
                     qDebug() << m_downfile.fileName() << m_filesize;
                     if (!m_downfile.open(QIODevice::WriteOnly| QIODevice::Append)) {
                         appendMsg(client, "fail to open file");
                         return;
                     }

                     break;
                 }
                 case FileData:{

                    if(!m_downfile.isOpen()) qDebug()<<"err";

                     QByteArray bytes;
                     RxDatStream >> bytes;
                     m_filesize -= m_downfile.write(bytes);
                     qDebug() << QString::fromLocal8Bit(bytes) << bytes.size();

                     break;
                 }
                 case FileOver:{
                     m_downfile.close();
                     appendMsg(client, "accept success");
                     break;
                 }
                 default:{
                     qDebug() << "error";
                 }
             }

        });
    });

}

void Widget::appendMsg(QTcpSocket* client,QString msg){
    qDebug() << "["<< client->peerAddress().toString() << "]" << msg;
    ui->edit_msg->append(QString( "[%1] %2" ).arg(client->peerAddress().toString()).arg(msg));
}

Widget::~Widget()
{
    delete ui;
}
