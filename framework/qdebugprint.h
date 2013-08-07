#ifndef QDEBUGPRINT_H
#define QDEBUGPRINT_H

#ifdef QT_CORE_LIB

#include <QString>

class QTextBrowser;

class qDebugPrint
{
public:
    static QTextBrowser * edit;
    static void print (const QString & data);

};

#endif

#endif // QDEBUGPRINT_H
