#include "pcap_config.h"

pcap_config::pcap_config()
{
    qDebug("create");
}

pcap_config::~pcap_config()
{
    //
}

bool pcap_config::setting()
{
    this->i = 0;

    pcap_if_t* _a;

    bool data = pcap_findalldevs(&_a, errbuf);

    /*  */
    if(pcap_findalldevs(&_a, errbuf) == -1)
    {
        QString _str = ("Error in pcap_findalldevs: %s\n", errbuf);
        qDebug(_str.toLatin1());
        return false;
    }

    /*  */
    for(device = _a; device; device=device->next)
    {
        QString _str = ("%d. %s", ++i, this->device->name);
        qDebug("%d. %s", ++i, this->device->name);

        if(this->device->description)
        {
            alldevs.push_back(*device);
            qDebug(" (%s)\n", this->device->description);
        }
        else
            qDebug(" (No description available)\n");
    }

    if(this->i==0)
    {
        qDebug("\nNo interfaces found! Make sure LiPcap is installed.\n");
        return false;
    }

    /*  */
    return true;
}

std::vector<pcap_if_t> pcap_config::get_alldevs()
{
    return alldevs;
}

pcap_if_t pcap_config::get_device()
{
    return *device;
}

void pcap_config::set_errbuf(char* _errbuf)
{
    QString str = _errbuf;
}

char pcap_config::get_errbuf()
{
    return *this->errbuf;
}
