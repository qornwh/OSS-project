#ifndef PCAP_IP_H
#define PCAP_IP_H

#include "netview_project_library_global.h"

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_ip
{
public:
    pcap_ip();
    pcap_ip(u_char, u_char, u_char, u_char);

private:
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
};

#endif // PCAP_IP_H
