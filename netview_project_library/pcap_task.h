#ifndef PCAP_TASK_H
#define PCAP_TASK_H

#include "netview_project_library_global.h"
#include <QRunnable>
#include <QObject>
#include "pcap_mac.h"
#include "pcap_ether_header.h"
#include "pcap_ip_header.h"
#include "pcap_data.h"

class pcap_task : public QObject, public QRunnable
{
    Q_OBJECT
public:
    pcap_task(pcap_t*);
    ~pcap_task();

public:
    void run() override;
    void set_stopper(bool);
    bool get_state();

    void set_my_ip();
    char* get_my_ip();

signals:
    void pcap_singal_data(pcap_data*);

private:
    int res;
    int stopper;
    pcap_t* adhandle;
    struct pcap_pkthdr *header;

    QVector<sockaddr_in> myIPArray;
    char* myIP;
    u_char myIPs[4];
    u_char myDnsIPs[4];

};

#endif // PCAP_TASK_H
