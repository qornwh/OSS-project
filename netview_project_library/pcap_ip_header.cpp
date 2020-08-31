#include "pcap_ip_header.h"

pcap_ip_header::pcap_ip_header()
{

}

pcap_ip_header::~pcap_ip_header()
{

}

void pcap_ip_header::pkt_data_reader(u_char *pkt_data)
{
    ih = (ip_header *)(pkt_data+14);
}

ip_header pcap_ip_header::get_ih()
{
    return *ih;
}
