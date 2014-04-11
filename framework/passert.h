#ifndef PASSERT_H
#define PASSERT_H

#define passert(condition,message) Q_ASSERT(condition)

#ifdef QT_CORE_LIB
#include "qdebugprint.h"
#define qlog(text) qDebugPrint::print(text)
#else
#define qlog(text)
#endif

//#define DRAWING_MODE_LOOPED
#define DRAWING_MODE_CHANGESONLY

#ifndef DRAWING_MODE_CHANGESONLY
#ifndef DRAWING_MODE_LOOPED
#error "Drawing mode not selected"
#endif
#endif

#ifdef DRAWING_MODE_CHANGESONLY
#ifdef DRAWING_MODE_LOOPED
#error "Both drawing modes selected"
#endif
#endif

#define writeenableassert() passert(IsReadOnly() == 0,"is readonly")
#define wea() writeenableassert()

#endif // PASSERT_H
