#ifndef PCAP_DATA_H
#define PCAP_DATA_H

#include "netview_project_library_global.h"

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_data
{
public:
    pcap_data();
    pcap_data(u_char []);

private:
    u_char datas[6];

public:
    u_char* get_data();

};

#endif // PCAP_DATA_H
