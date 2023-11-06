
#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QChart>
#include <QFile>
#include <QFileSystemWatcher>
#include <QTextStream>

// QFile file("dat.csv");

#define FILE "D:/usdk/usdk/dat.csv"  // <--------- curve srouce

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileSystemWatcher* watcher = new QFileSystemWatcher(this);
    watcher->addPath(FILE);

    connect(watcher, &QFileSystemWatcher::fileChanged, [=](const QString& path) { refreshChart(); });

    // create chart

    QWidget* wdg = new QWidget(this);
    chart        = new QChart();

    QChartView* chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);  // 抗锯齿

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(chartview);
    ui->widget->setLayout(layout);

    chart->addAxis(axisX = new QValueAxis(this), Qt::AlignBottom);  // 下：Qt::AlignBottom  上：Qt::AlignTop
    chart->addAxis(axisY = new QValueAxis(this), Qt::AlignLeft);    // 左：Qt::AlignLeft    右：Qt::AlignRight

    chart->setAnimationOptions(QChart::NoAnimation);

    // 设置范围
    // 设置刻度的格式

    /************************************
        %u 无符号十进制整数
        %s 字符串
        %c 一个字符
        %d 有符号十进制整数
        %e 浮点数、e-记数法
        %f 浮点数、十进制记数法
        %s 字符串
    ****************************************/

    axisX->setLabelFormat("%.2f");
    axisX->setGridLineVisible(true);  // 网格线可见
    axisX->setTitleText("X");

    axisY->setLabelFormat("%.2f");
    axisY->setGridLineVisible(true);
    axisY->setTitleText("Y");

    //

    refreshChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshChart()
{
#if 1

    /* read from file */

    QFile file(FILE);

    // clear chart
    chart->removeAllSeries();

    // open file

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    // read lines
    QStringList lines;
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        lines.push_back(stream.readLine());
    }

    // close file
    file.close();

    // parse data

    QVector<QXYSeries*> arr_series;

    const QColor colors[] = {
        Qt::red,
        Qt::blue,
        Qt::green,
        Qt::darkYellow,
        Qt::darkRed,
        Qt::darkGreen,
        Qt::darkBlue,
        Qt::darkCyan,
        Qt::darkMagenta,
    };

    uint16_t row = 0, col = 0;
    float    ymin = INT32_MAX, ymax = INT32_MIN;

    Q_FOREACH (auto line, lines)
    {
        QStringList items = line.split(",");

        col = 0;
        if (row == 0)
        {
            // header
            Q_FOREACH (auto item, items)
            {
                // QLineSeries: 折线
                // QSplineSeries: 曲线

                auto series = new QLineSeries(chart);

                chart->addSeries(series);
                series->attachAxis(axisX);
                series->attachAxis(axisY);

                series->setName(item);
                series->setColor(colors[col]);
                arr_series.append(series);
                ++col;
            }
        }
        else
        {
            // data
            Q_FOREACH (auto item, items)
            {
                float val = item.toFloat();

                if (ymin > val)
                {
                    ymin = val;
                }
                if (ymax < val)
                {
                    ymax = val;
                }
                arr_series[col]->append(row, val);
                ++col;
            }
        }
        ++row;
    }

    axisX->setRange(0, row);

    ymin -= 1;
    ymax += 1;
    if (ymax > 0)
    {
        ymax *= 1.1f;
    }
    else if (ymax < 0)
    {
        ymax *= 0.9f;
    }
    if (ymin > 0)
    {
        ymin *= 0.9f;
    }
    else if (ymin < 0)
    {
        ymin *= 1.1f;
    }
    axisY->setRange(ymin, ymax);

    axisX->setTickCount(row % 5);  // 大格
    axisX->setMinorTickCount(1);   // 小格
    axisY->setTickCount(col % 5);
    axisY->setMinorTickCount(1);

#else

#endif
}

void MainWindow::on_pushButton_clicked()
{
    refreshChart();
}
