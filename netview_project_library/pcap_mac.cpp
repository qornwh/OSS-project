#include "pcap_mac.h"

pcap_mac::pcap_mac()
{

}

void pcap_mac::pkt_data_reader(u_char* pkt_data)
{
    this->byte1 = pkt_data[0];
    this->byte2 = pkt_data[1];
    this->byte3 = pkt_data[2];
    this->byte4 = pkt_data[3];
    this->byte5 = pkt_data[4];
    this->byte6 = pkt_data[5];
}

u_char* pcap_mac::get_mac_data()
{
    u_char _data[6] = {this->byte1, this->byte2, this->byte3, this->byte4, this->byte5, this->byte6};

    return _data;
}
