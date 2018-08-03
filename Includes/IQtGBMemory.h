#include <qstring.h>

class IQtGBMemory
{
public:
    virtual ~IQtGBMemory() {}
    virtual bool LoadBios(QString biosFilePath) = 0;
};
