#ifndef PCAP_CONFIG_H
#define PCAP_CONFIG_H

#include "netview_project_library_global.h"

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_config
{
public:
    pcap_config();
    ~pcap_config();

private:
    pcap_if_t *device;
    u_int netmask;
    std::vector<pcap_if_t> alldevs;
    std::vector<char> packet_filter;
    int i;

public:
    bool setting();

    std::vector<pcap_if_t> get_alldevs();
    pcap_if_t get_device();

    void set_errbuf(char *);
    char get_errbuf();

    //void set_adhandle(pcap_if_t* _adhandle);
    //pcap_if_t* get_adhandle();

public:
    char errbuf[PCAP_ERRBUF_SIZE];

};

#endif // PCAP_CONFIG_H
