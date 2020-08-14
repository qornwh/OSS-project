#ifndef PCAP_ETHER_HEADER_H
#define PCAP_ETHER_HEADER_H

#include "netview_project_library_global.h"

#define ETHER_ADDR_LEN 6

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_ether_header
{
public:
    pcap_ether_header();

private:
    u_char ether_dhost[ETHER_ADDR_LEN];
    u_char ether_shost[ETHER_ADDR_LEN];
    u_char ether_type;

public:
    void pkt_data_reader(u_char*);
    u_char* get_ether_dhost();
    u_char* get_ether_shost();
    u_char get_ether_type();
};

#endif // PCAP_ETHER_HEADER_H
