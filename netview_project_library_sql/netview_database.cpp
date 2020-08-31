#include "netview_database.h"

netview_database::netview_database()
{
    if (QSqlDatabase::drivers().isEmpty())
            qDebug() << "No database drivers found This demo requires at least one Qt database driver. "
                        "Please check the documentation how to build the "
                        "Qt SQL plugins.";
}

bool netview_database::netview_connection(
        const QString &dbName)
{
    bool _onoff = true;
    name = "LocalDB";

    db = QSqlDatabase::addDatabase("QSQLITE", name);
    db.setDatabaseName(dbName);

    if(db.open())
    {
        _onoff = true;
        qDebug("sucess db connection.\n");
    }
    else
    {
        _onoff = false;
        qDebug("fail db connection.\n");
    }

    return _onoff;
}

bool netview_database::netview_database_setting(const QString &tableN)
{
    QSqlQuery query(QSqlDatabase::database(name));
    query.prepare(""
                  "select name "
                  "from sqlite_master "
                  "where name='"+tableN.toLatin1()+"'");

    this->tableN = tableN;
    query.exec();
    if(query.next())
    {
        qDebug("yes table = "+tableN.toLatin1());
        return true;
    }
    else
    {
        if(create_table(tableN))
            return true;
        else
            return false;
    }
    return true;
}

bool netview_database::create_table(const QString &tableN)
{
    QSqlQuery query(QSqlDatabase::database(name));
    query.prepare("CREATE TABLE "+tableN.toLatin1()+" (pcap_ip text PRIMARY KEY, ip_num integer, proto integer, proto2 integer)");

    if(query.exec())
    {
        qDebug("Create Table\n");
        return true;
    }
    else
    {
        qDebug("fail create table\n");
        return false;
    }
}

bool netview_database::netview_database_update(const QString &pcap_ip, const QString &proto, const QString &proto2)
{
    QSqlQuery query(QSqlDatabase::database(name));
    query.prepare("INSERT INTO "+tableN.toLatin1()+" "
                  "VALUES ('"+pcap_ip.toLatin1()+"',1,"+proto.toLatin1()+","+proto2.toLatin1()+") "
                  "on CONFLICT(pcap_ip) do UPDATE set ip_num = ip_num + 1;");
    if(query.exec())
    {
        return true;
    }
    else
    {
        qDebug("not update query");
        return false;
    }
}

QSqlQuery netview_database::netview_database_read()
{
    QSqlQuery query(QSqlDatabase::database(name));

    query.prepare(
                "select pcap_ip, ip_num "
                "from "+tableN.toLatin1()+" "
                "ORDER by ip_num desc");

    query.exec();

    return query;
}

QSqlQuery netview_database::netview_database_read(const QString& tableN2)
{
    QSqlQuery query(QSqlDatabase::database(name));

    query.prepare(
                "select pcap_ip, ip_num "
                "from "+tableN2.toLatin1()+" "
                "ORDER by ip_num desc;");

    query.exec();

    return query;
}

QSqlQuery netview_database::netview_database_read_2()
{
    QSqlQuery query(QSqlDatabase::database(name));

    query.prepare(
                "select pcap_ip, ip_num "
                "from "+tableN.toLatin1()+" "
                "where ip_num < 5 "
                "ORDER by ip_num;");

    query.exec();

    return query;
}

QSqlQuery netview_database::netview_database_read_2(const QString& tableN2)
{
    QSqlQuery query(QSqlDatabase::database(name));

    query.prepare(
                "select pcap_ip, ip_num "
                "from "+tableN2.toLatin1()+" "
                "where ip_num < 5 "
                "ORDER by ip_num;");

    query.exec();

    return query;
}
