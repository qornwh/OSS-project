#include "subwindow1.h"
#include "ui_subwindow1.h"

SubWindow1::SubWindow1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWindow1)
{
    ui->setupUi(this);
}

SubWindow1::SubWindow1(std::vector<pcap_if_t> list_pcap_device ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWindow1)
{
    ui->setupUi(this);

    ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());

    int index = list_pcap_device.size();
    qDebug("index size %d\n", index);

    ui->tableWidget->setRowCount(index);

    for(int i=0; i<index; i++)
    {
        QString std1 = ("%s", list_pcap_device[i].name);
        QString std2 = ("%s", list_pcap_device[i].description);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(std1));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(std2));
    }

    clone_pcaps.clear();
    clone_pcaps = list_pcap_device;
}

SubWindow1::~SubWindow1()
{
    int index = clone_pcaps.size();
    ui->tableWidget->setRowCount(0);

    for(int i=0; i<index; i++)
    {
        clone_pcaps.pop_back();
    }

    delete ui;
}

void SubWindow1::closeEvent(QCloseEvent *event)
{
}

void SubWindow1::on_sub_btn_cle_clicked()
{
    emit cansle_singal(false);
    this->close();
}

void SubWindow1::on_sub_btn_ok_clicked()
{
    this->close();
    emit pcap_singal(clone_pcaps[ui->tableWidget->currentRow()]);
}
