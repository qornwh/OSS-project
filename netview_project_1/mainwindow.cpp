#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(this->window()->size());
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    onoff = false;
    p = NULL;
    sub1 = NULL;

    nowDate = QDate::currentDate();
    db = new netview_database();
    db->netview_connection("test200828.db");

    QString _str(
                "nv_"+
                QString::number(nowDate.year())+"_"+
                QString::number(nowDate.month())+"_"+
                QString::number(nowDate.day()));
    if(!db->netview_database_setting(_str))
    {
        close();
        exit(0);
    }

    create_chart(1);
    view_charts(1);
    view_chart();

    timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(view_chart()));
    //timer->start();
    QThreadPool::globalInstance()->start((QRunnable*)timer);
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
    work = new pcap_work(pcap);

    bool test = work->pcap_open();

    work->pcap_start();

    connect(work->get_queue().front(), SIGNAL(pcap_singal_data(pcap_data*)), this, SLOT(pcap_slots_data(pcap_data*)));

    if(test)
        qDebug("yes");
    else
        qDebug("no");
    //test--
}

void MainWindow::sub_cls_slot(bool _bool)
{
    if(!_bool)
    {
        qDebug("no selected\n");
        QMessageBox msgBox;
        msgBox.setText("No Selected.");
        msgBox.setInformativeText("No Selected Network");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
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
        delete sub1;
        sub1 = NULL;
        ui->btn_start->setText(QString("Start"));
        ui->p1_lb_ethName->setText(QString("NO"));
        ui->p1_lb_onoff->setText(QString("-----------"));

        if(work != NULL)
        {
            if(work->get_queue_size()>0)
            {
                work->pcap_stop();
            }
        }
        onoff = false;
    }
}

void MainWindow::pcap_slots_data(pcap_data* _data)
{
    db->netview_database_update(
            QString("%1.%2.%3.%4").arg(_data->get_data()[0]).arg(_data->get_data()[1]).arg(_data->get_data()[2]).arg(_data->get_data()[3]),
            QString::number(_data->get_data()[4]),
            QString::number(_data->get_data()[5])
        );
}

void MainWindow::create_chart(int x)
{
    chart = new QtCharts::QChart();
    chart->setTitle(nowDate.toString("yyyy-MM-dd"));
    //chart->legend()->setAlignment(Qt::AlignRight);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->page_wdg_2->addWidget(chartView);

    for(int i = 0; i<x; i++)
    {
        QtCharts::QChart *_chart = new QtCharts::QChart();

        QtCharts::QChartView *_chartView = new QtCharts::QChartView(_chart);
        _chartView->setRenderHint(QPainter::Antialiasing);

        if(i<2){
            ui->page_wdg_3->addWidget(_chartView,1,i);
        }
        else{
            ui->page_wdg_3->addWidget(_chartView,2,i-2);
        }
        charts.append(_chart);
    }
}

void MainWindow::view_charts(int x=1)
{
    for(int i=0;i<charts.size(); i++)
    {
        QDate date;
        if(charts.size() == 1)
            date = nowDate.addDays(-(x));
        else
            date = nowDate.addDays(-(i+1));

        QString _str(
                    "nv_"+
                    QString::number(date.year())+"_"+
                    QString::number(date.month())+"_"+
                    QString::number(date.day()));

        QtCharts::QPieSeries *pie = new QtCharts::QPieSeries();
        QSqlQuery query = db->netview_database_read(_str);
        int index = 0;
        int otherdatavalue = 0;

        charts[i]->setTitle(date.toString("yyyy-MM-dd")+" no data");
        while(query.next())
        {
            if(index < 5){
                QString ip = query.value(0).toString();
                int num = query.value(1).toInt();
                pie->append(ip, num);
                index++;
            }
            else{
                otherdatavalue += query.value(1).toInt();
            }
            charts[i]->setTitle(date.toString("yyyy-MM-dd"));
        }
        pie->append("etc",otherdatavalue);

        charts[i]->removeAllSeries();
        charts[i]->addSeries(pie);
        pie->setLabelsVisible();
    }
}

void MainWindow::view_chart()
{
    QtCharts::QPieSeries *pie = new QtCharts::QPieSeries();
    QSqlQuery query = db->netview_database_read();
    int index = 0;
    int otherdatavalue = 0;
    while(query.next())
    {
        if(index < 10){
            QString ip = query.value(0).toString();
            int num = query.value(1).toInt();
            pie->append(ip, num);
            index++;
        }
        else{
            otherdatavalue += query.value(1).toInt();
        }
    }
    pie->append("etc",otherdatavalue);

    for(auto slice : pie->slices())
        slice->setLabel(slice->label()+QString(" %1%").arg(100*slice->percentage(), 0, 'f', 1));

    chart->removeAllSeries();
    chart->addSeries(pie);
    pie->setLabelsVisible();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(onoff)
        work->pcap_stop();
    timer->stop();
    qDebug("close");
}

void MainWindow::on_btn_1_clicked()
{
    view_charts(1);
}

void MainWindow::on_btn_2_clicked()
{
    view_charts(2);
}

void MainWindow::on_btn_3_clicked()
{
    view_charts(3);
}

void MainWindow::on_btn_4_clicked()
{
    view_charts(4);
}
