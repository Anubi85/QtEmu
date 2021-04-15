#include "QtEmu.h"
#include <QApplication>

Q_DECLARE_METATYPE(std::shared_ptr<QImage>)

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::shared_ptr<QImage>>();
    QApplication a(argc, argv);
    QtEmu w;
    w.show();
    return a.exec();
}
