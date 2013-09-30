#ifndef PASSERT_H
#define PASSERT_H

#define passert(condition,message) Q_ASSERT(condition)

#ifdef QT_CORE_LIB
#include "qdebugprint.h"
#define qlog(text) qDebugPrint::print(text)
#else
#define qlog(text)
#endif

#endif // PASSERT_H
