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

signals:
    void FrameReady(QImage* frame);

private slots:
    void on_actionLoad_ROM_triggered();

private:
    enum class SupportedRomType
    {
        gb,
    };

    static QMap<QString, SupportedRomType> s_RomTypeMap;

    Ui::QtEmu *ui;
    QLibrary m_CoreLibrary;
    IEmulatorCore* m_Core;
    bool m_StopCore;
    QThread* m_CoreExecutingThread;
    QThread* m_VideoUpdateThread;

    void StopEmulatorCore();
    void StartEmulatorCore();
    void EmulatorLoop();
    void VideoLoop();
};

#endif // QTGB_H
