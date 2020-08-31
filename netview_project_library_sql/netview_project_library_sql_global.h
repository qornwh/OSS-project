#ifndef NETVIEW_PROJECT_LIBRARY_SQL_GLOBAL_H
#define NETVIEW_PROJECT_LIBRARY_SQL_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QtSql>

#if defined(NETVIEW_PROJECT_LIBRARY_SQL_LIBRARY)
#  define NETVIEW_PROJECT_LIBRARY_SQL_EXPORT Q_DECL_EXPORT
#else
#  define NETVIEW_PROJECT_LIBRARY_SQL_EXPORT Q_DECL_IMPORT
#endif

#endif // NETVIEW_PROJECT_LIBRARY_SQL_GLOBAL_H
