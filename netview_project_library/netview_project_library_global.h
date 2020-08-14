#ifndef NETVIEW_PROJECT_LIBRARY_GLOBAL_H
#define NETVIEW_PROJECT_LIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <QObject>
#include <QString>
#include <QTime>
#include <cstdlib>
#include "pcap.h"

#if defined(NETVIEW_PROJECT_LIBRARY_LIBRARY)
#  define NETVIEW_PROJECT_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define NETVIEW_PROJECT_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

#endif // NETVIEW_PROJECT_LIBRARY_GLOBAL_H
