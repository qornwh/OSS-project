#include "pcap_task.h"

#define IP_HEADER 0x0800
#define ARP_HEADER 0x0806
#define REVERSE_ARP_HEADER 0x0835

pcap_task::pcap_task(pcap_t* _adhandle)
{
    this->adhandle = _adhandle;
    stopper = false;
    set_my_ip();
}

pcap_task::~pcap_task()
{

}

void pcap_task::set_stopper(bool data)
{
    this->stopper = data;
}

void pcap_task::run()
{
    const u_char *pkt_data;
    unsigned int ptype;
    pcap_mac *destmac;          //수신자 mac
    pcap_mac *srcmac;           //송신자 mac
    pcap_ether_header *eth ;    //이더넷 헤더
    pcap_ip_header *ih;         //ip 헤더

    while((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0)
    {
        if(stopper)
            break;
        if (res == 0)
           continue;

        destmac = new pcap_mac();
        destmac->pkt_data_reader((u_char*)pkt_data);
        srcmac = new pcap_mac();
        srcmac->pkt_data_reader((u_char*)(pkt_data+6));

        eth = new pcap_ether_header();
        eth->pkt_data_reader((u_char*)pkt_data);

        ptype = ntohs(eth->get_ether_type());

        ih = new pcap_ip_header();

        ih->pkt_data_reader((u_char*)(pkt_data));

        /*
         * 프로토콜 정보 출력
        */
        if(ntohs(eth->get_ether_type()) == IP_HEADER)
        {
            qDebug("Upper Protocol is IP HEADER(%04x)\n",ptype);

            qDebug("********************** IP Header ***********************\n");
            qDebug("ip versioin is %d\n",ih->get_ih().ip_version);
            qDebug("ip lengh is %d\n",(ih->get_ih().ip_leng)*4);

            /*
             * IP헤더에서 목적지 및 발신지 IP정보를 가리키고 있는 필드인
             * daddr, sadder의 정보를 이용하여 출력
            */
            qDebug("Destination IP Address : %d.%d.%d.%d \n",
                   ih->get_ih().daddr.byte1, ih->get_ih().daddr.byte2,
                   ih->get_ih().daddr.byte3, ih->get_ih().daddr.byte4 );
            qDebug("Source IP Address : %d.%d.%d.%d \n",
                   ih->get_ih().saddr.byte1, ih->get_ih().saddr.byte2,
                   ih->get_ih().saddr.byte3, ih->get_ih().saddr.byte4);

            if(ih->get_ih().saddr.byte1 == myIPs[0] && ih->get_ih().saddr.byte2 == myIPs[1] && ih->get_ih().saddr.byte3 == myIPs[2] /*&& ih->get_ih().saddr.byte4 == myIPs[3]*/)
            {
                continue;   //송신 데이터가 내주소 패스
            }

            if(ih->get_ih().saddr.byte1 == myDnsIPs[0] && ih->get_ih().saddr.byte2 == myDnsIPs[1] && ih->get_ih().saddr.byte3 == myDnsIPs[2] && ih->get_ih().saddr.byte4 == myDnsIPs[3])
            {
                continue;   //송신 데이터가 내 dns주소 패스
            }

            /*
             * 1. 여기서 부터 네이버, 구글, 티스토리, 네이트, 다음을 분류
            */

            u_char datas[6] = {
                ih->get_ih().saddr.byte1,
                ih->get_ih().saddr.byte2,
                ih->get_ih().saddr.byte3,
                ih->get_ih().saddr.byte4,
                0,
                0,
            };

            if(pkt_data[54] == 72 && pkt_data[55] == 84 && pkt_data[56] == 84 && pkt_data[57] == 80 && pkt_data[34] == 0)
            {
                datas[5] = 0x01;
                qDebug("HTTP protocol\n");
            }

            if(ih->get_ih().proto == 0x06)
            {
                datas[4] = 0x06;
                qDebug("Upper Protocol is TCP\n");
            }
            else if(ih->get_ih().proto == 0x11)
            {
                datas[4] = 0x11;
                qDebug("Upper Protocol is UDP\n");
            }
            else if(ih->get_ih().proto == 0x01)
            {
                datas[4] = 0x01;
                qDebug("Upper Protocol is ICMP\n");
            }
            else
            {
                datas[4] = 0x00;
                qDebug("Upper Protocol is Unknown\n");
            }

            pcap_data *_data = new pcap_data(datas);

            //시그널 데이터 전송
            emit pcap_singal_data(_data);

            qDebug("********************** IP Header End *******************\n");
        }
        else if(ntohs(eth->get_ether_type()) == ARP_HEADER)
        {
            qDebug("Upper Protocol is ARP HEADER(%04x)\n",ptype);
        }
        else if(ntohs(eth->get_ether_type()) == REVERSE_ARP_HEADER)
        {
            qDebug("Upper Protocol is REVERSE ARP HEADER(%04x)\n",ptype);
        }
        else
        {
            qDebug("Upper Protocol is Unknown(%04x)\n",ptype);
        }

        delete destmac;
        delete srcmac;
        delete eth;
        delete ih;
    }
}

bool pcap_task::get_state()
{
    return stopper;
}

void pcap_task::set_my_ip()
{
    WSADATA wsaData;

    if(WSAStartup(0x202, &wsaData) == SOCKET_ERROR)
    {
        qDebug("not");
    }
    else
    {
        char myaddr[256];
        PHOSTENT pHostInfo;
        struct sockaddr_in addr;

        QString msgIP;

        gethostname(myaddr, sizeof(myaddr));

        pHostInfo = gethostbyname(myaddr);

        if(pHostInfo)
        {
            for(int i= 0; pHostInfo->h_addr_list[i] != NULL; i++)
            {
                memcpy(&addr.sin_addr, pHostInfo->h_addr_list[i], pHostInfo->h_length);

                myIPArray.append(addr);

                QString std = ("%s\n", inet_ntoa(addr.sin_addr));
                qDebug(std.toLatin1());
            }
        }
        myIP = inet_ntoa(myIPArray.front().sin_addr);
        myIPs[0] = myIPArray.front().sin_addr.S_un.S_un_b.s_b1;
        myIPs[1] = myIPArray.front().sin_addr.S_un.S_un_b.s_b2;
        myIPs[2] = myIPArray.front().sin_addr.S_un.S_un_b.s_b3;
        myIPs[3] = myIPArray.front().sin_addr.S_un.S_un_b.s_b4;
        qDebug("my IP %d.%d.%d.%d\n", myIPs[0], myIPs[1], myIPs[2], myIPs[3]);
    }

    myDnsIPs[0] = 168;
    myDnsIPs[1] = 126;
    myDnsIPs[2] = 63;
    myDnsIPs[3] = 1;
}

char* pcap_task::get_my_ip()
{
    return myIP;
}

//            이 부근 요청시 주소위치는  54  55  56  57(16진수 36 37 38 39)
//            실제 데이터 값    HTTP = 72  84  84  80(16진수 48 54 54 50)
//            get 수신시    주소위치는 118 119 120 121(16진수 76 77 78 79)

//            struct addrinfo *res = 0;
//            int status;
//            status = getaddrinfo(str1.toLatin1(),0,0,&res);
//            char host[512];
//            status = getnameinfo(res->ai_addr,res->ai_addrlen,host,512,0,0,0);
//            qDebug("%s", host);
//            freeaddrinfo(res);
//            HOSTENT *ptr = gethostbyaddr(str1.toLatin1(),
//                                         sizeof(str1.toLatin1()),
//                                         AF_INET);
//            if(ptr == NULL)
//            {
//                qDebug("No gethostbyaddr()\n");
//            }
//            qDebug("host : %s\n",ptr->h_name);
