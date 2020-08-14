#include "pcap_work.h"

pcap_work::pcap_work()
{

}

pcap_work::pcap_work(pcap_if_t pcap)
{
    this->device = pcap;
}

void pcap_work::set_pcap(pcap_if_t pcap)
{
    this->device = pcap;
}

pcap_if_t pcap_work::get_pcap()
{
    return this->device;
}

bool pcap_work::pcap_open()
{
    char _packet_filter[] = "";

    if((adhandle = pcap_open_live(device.name, 65536, 1,  1000,  errbuf)) == NULL)
    {
        QString str = ("\nUnable to open the adapter. %s is not supported by WinPcap\n", device.name);
        qDebug(str.toLatin1());
        return false;
    }

    if (pcap_compile(adhandle, &fcode, _packet_filter, 1, netmask) <0 )
    {
        QString str = ("\nUnable to compile the packet filter. Check the syntax.\n");
        qDebug(str.toLatin1());
        return false;
    }

    if (pcap_setfilter(adhandle, &fcode)<0)
    {
        QString str = ("\nError setting the filter.\n");
        qDebug(str.toLatin1());
        return false;
    }

    QString str2 = ("\nlistening on %s...\n", device.description);
    qDebug(str2.toLatin1());

    //이제 pcap_config 객체를 제거할지 생각하자.

    return true;
}
