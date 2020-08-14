#include "pcap_ether_header.h"

pcap_ether_header::pcap_ether_header()
{

}

void pcap_ether_header::pkt_data_reader(u_char *pkt_data)
{
    std::copy(pkt_data   , pkt_data+6 , this->ether_dhost);
    std::copy(pkt_data+6 , pkt_data+12, this->ether_shost);
    this->ether_type = *(pkt_data+12);
}

u_char* pcap_ether_header::get_ether_dhost()
{
    return this->ether_dhost;
}

u_char* pcap_ether_header::get_ether_shost()
{
    return this->ether_shost;
}

u_char pcap_ether_header::get_ether_type()
{
    return this->ether_type;
}
