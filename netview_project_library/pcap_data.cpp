#include "pcap_data.h"

pcap_data::pcap_data()
{

}

pcap_data::pcap_data(uchar data[])
{
    for(int i =0; i< 6; i++)
    {
        datas[i] = data[i];
    }
}

u_char* pcap_data::get_data()
{
    return this->datas;
}
