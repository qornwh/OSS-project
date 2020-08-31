#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QChar>
#include <QDialog>
#include <QMessageBox>
#include <QThreadPool>
#include <QTimer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QChart>
#include "pcap_config.h"
#include "pcap_work.h"
#include "pcap_task.h"
#include "pcap_data.h"
#include "subwindow1.h"
#include "netview_database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_main_clicked();
    void on_btn_real_time_clicked();
    void on_btn_data_clicked();
    void on_btn_start_clicked();
    void sub_ok_slot(pcap_if_t);
    void sub_cls_slot(bool);

    void pcap_slots_data(pcap_data*);

private:
    Ui::MainWindow *ui;
    pcap_config *p;
    bool onoff;
    SubWindow1* sub1;
    pcap_work *work;
    netview_database *db;
    QDate nowDate;
    QtCharts::QChart *chart;
    QVector<QtCharts::QChart*> charts;
    QtCharts::QChartView *chartView;
    QTimer *timer;

    void create_chart(int);
    void view_charts(int);

public:
    void closeEvent(QCloseEvent *event);
    void init();

private slots:
    void view_chart();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
};
#endif // MAINWINDOW_H
