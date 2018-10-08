#ifndef QTGB_H
#define QTGB_H

#include <QMainWindow>
#include "IEmulatorCore.h"

namespace Ui {
class QtEmu;
}

class QtEmu : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtEmu(QWidget *parent = nullptr);
    ~QtEmu();

private slots:
    void on_actionLoad_ROM_triggered();

private:
    Ui::QtEmu *ui;
    IEmulatorCore* m_Core;
    QThread* m_CoreExecutingThread;
    quint32* m_ScreenBuffer;
    QMutex* m_ScreenBuferMutex;

    void StopEmulatorCore();
    void StartEmulatorCore();
    void EmulatorLoop();
};

#endif // QTGB_H
