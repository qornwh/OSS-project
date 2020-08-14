#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QChar>
#include <QDialog>
#include <QMessageBox>
#include "pcap_config.h"
#include "subwindow1.h"
#include "pcap_work.h"

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

private:
    Ui::MainWindow *ui;
    pcap_config *p;
    bool onoff;
    SubWindow1* sub1;

};
#endif // MAINWINDOW_H
