#include "pcap_ip.h"

pcap_ip::pcap_ip()
{

}

pcap_ip::pcap_ip(u_char byte1, u_char byte2, u_char byte3,
                 u_char byte4)
{
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
    this->byte4 = byte4;
}
