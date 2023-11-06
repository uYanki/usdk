#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    QChart*     chart;
    QValueAxis* axisX;
    QValueAxis* axisY;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void refreshChart();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
