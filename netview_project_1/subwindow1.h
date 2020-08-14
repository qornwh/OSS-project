#ifndef SUBWINDOW1_H
#define SUBWINDOW1_H

#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <iostream>
#include "pcap_config.h"

namespace Ui {
class SubWindow1;
}

class SubWindow1 : public QWidget, public QCloseEvent
{
    Q_OBJECT

public:
    explicit SubWindow1(QWidget *parent = nullptr);
    explicit SubWindow1(std::vector<pcap_if_t> , QWidget *parent = nullptr);
    ~SubWindow1();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_sub_btn_cle_clicked();

    void on_sub_btn_ok_clicked();

private:
    Ui::SubWindow1 *ui;
    std::vector<pcap_if_t> clone_pcaps;

signals:
    void pcap_singal(pcap_if_t);
    void cansle_singal(bool);
};

#endif // SUBWINDOW1_H
