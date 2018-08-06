#ifndef IQTGBCPU_H
#define IQTGBCPU_H

#include <QtCore/qglobal.h>

#ifdef QTGBCPU_LIBRARY
#define QTGBCPU_EXPORT Q_DECL_EXPORT
#else
#define QTGBCPU_EXPORT Q_DECL_IMPORT
#endif

class QTGBCPU_EXPORT IQtGBCPU
{
public:
    static IQtGBCPU* GetInstance();
    virtual ~IQtGBCPU();
    virtual void Reset() = 0;
    virtual void Exec() = 0;
    virtual bool HasError() = 0;
};

#endif // IQTGBCPU_H
