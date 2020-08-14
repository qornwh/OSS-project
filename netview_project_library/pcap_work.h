#ifndef PCAP_WORK_H
#define PCAP_WORK_H

#include "netview_project_library_global.h"

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_work
{
private:
    pcap_if_t device;
    pcap_t* adhandle;
    char *packet_filter;
    struct bpf_program fcode;
    u_int netmask;

public:
    char errbuf[PCAP_ERRBUF_SIZE];

public:
    pcap_work();
    pcap_work(pcap_if_t);

public:
    void set_pcap(pcap_if_t);
    pcap_if_t get_pcap();
    bool pcap_open();

};

#endif // PCAP_WORK_H
