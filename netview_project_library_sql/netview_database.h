#ifndef NETVIEW_DATABASE_H
#define NETVIEW_DATABASE_H

#include <netview_project_library_sql_global.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

class NETVIEW_PROJECT_LIBRARY_SQL_EXPORT netview_database
{
public:
    netview_database();
    ~netview_database();

public:
    bool netview_connection(const QString&);
    bool netview_database_setting(const QString&);
    bool netview_database_update(const QString&, const QString&, const QString&);
    QSqlQuery netview_database_read();
    QSqlQuery netview_database_read(const QString&);
    QSqlQuery netview_database_read_2();
    QSqlQuery netview_database_read_2(const QString&);

private:
    bool create_table(const QString&);

private:
    QSqlDatabase db;
    QString name;
    QString tableN;
};

#endif // NETVIEW_DATABASE_H
