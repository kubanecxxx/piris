#include "qdebugprint.h"

#ifdef QT_CORE_LIB
#include "QTextBrowser"

QTextBrowser * qDebugPrint::edit;

void qDebugPrint::print(const QString &data)
{
    edit->append(data);
}

#endif
