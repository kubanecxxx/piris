#include "qdebugprint.h"
#include "QTextBrowser"

#ifdef QT_CORE_LIB

QTextBrowser * qDebugPrint::edit;

void qDebugPrint::print(const QString &data)
{
    edit->append(data);
}

#endif
