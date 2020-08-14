#ifndef PCAP_MAC_H
#define PCAP_MAC_H

#include "netview_project_library_global.h"

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_mac
{
public:
    pcap_mac();

private:
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;

public:
    void pkt_data_reader(u_char*);
    u_char* get_mac_data();
};

#endif // PCAP_MAC_H
