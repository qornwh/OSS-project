#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onoff = false;
    p = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_main_clicked()
{
    ui->page_manage->setCurrentIndex(0);
}

void MainWindow::on_btn_real_time_clicked()
{
    ui->page_manage->setCurrentIndex(1);
}

void MainWindow::on_btn_data_clicked()
{
    ui->page_manage->setCurrentIndex(2);
}

void MainWindow::sub_ok_slot(pcap_if_t pcap)
{
    onoff = true;

    QString std1 = ("%s", pcap.name);
    QString std2 = ("%s", pcap.description);
    qDebug(std1.toLatin1()+" : "+std2.toLatin1());

    ui->p1_lb_ethName->setText(std2);
    ui->p1_lb_onoff->setText(QString("ON"));
    ui->btn_start->setText(QString("Stop"));
    //test
    pcap_work *work = new pcap_work(pcap);

    bool test = work->pcap_open();

    if(test)
        qDebug("yes");
    else
        qDebug("no");
    //test--
}

void MainWindow::sub_cls_slot(bool _bool)
{
    qDebug("no selected\n");
    QMessageBox msgBox;
    msgBox.setText("No Selected.");
    msgBox.setInformativeText("No Selected Network");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_btn_start_clicked()
{
    if(!onoff)
    {
        if(p == NULL)
        {
            p = new pcap_config();
        }

        if(p->setting() == false)
        {
            QMessageBox msgBox;
            msgBox.setText("ethernet device read Error.");
            msgBox.setInformativeText("Error : "+p->get_errbuf());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        else
        {
            sub1 = new SubWindow1(p->get_alldevs());
            sub1->show();
            connect(sub1, SIGNAL(pcap_singal(pcap_if_t)), this, SLOT(sub_ok_slot(pcap_if_t)));
            connect(sub1, SIGNAL(cansle_singal(bool)), this, SLOT(sub_cls_slot(bool)));
        }
    }
    else
    {
        delete p;
        p = NULL;
        ui->btn_start->setText(QString("Start"));
        ui->p1_lb_ethName->setText(QString("NO"));
        ui->p1_lb_onoff->setText(QString("-----------"));

        //stop과 동시에
        //일단 pcap_config메모리 해제한다.
        //모든것을 멈춘다.
        onoff = false;
    }

}

