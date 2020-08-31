#ifndef PCAP_IP_HEADER_H
#define PCAP_IP_HEADER_H

#include "netview_project_library_global.h"
#include "pcap_ip.h"

typedef struct ip_address
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

typedef struct ip_header
{
    u_char ip_leng:4;
    u_char ip_version:4;
    u_char tos; // Type of service
    u_short tlen; // Total length
    u_short identification; // Identification
    u_short flags_fo; // Flags (3 bits) + Fragment offset (13 bits)
    u_char ttl; // Time to live
    u_char proto; // Protocol
    u_short crc; // Header checksum
    ip_address saddr; // Source address
    ip_address daddr; // Destination address
    u_int op_pad; // Option + Padding
}ip_header;

class NETVIEW_PROJECT_LIBRARY_EXPORT pcap_ip_header
{
public:
    pcap_ip_header();
    ~pcap_ip_header();

private:
    ip_header *ih;

public:
    void pkt_data_reader(u_char*);
    ip_header get_ih();
};

#endif // PCAP_IP_HEADER_H
