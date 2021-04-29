#pragma once

#include <QMainWindow>
#include "IEmulatorCore.h"
#include <memory>
#include <QLibrary>

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
    void FrameReady(std::shared_ptr<QImage> frame);

private slots:
    void on_actionLoad_ROM_triggered();

private:
    enum class SupportedRomType
    {
		unknown,
        gb,
    };

    static QMap<QString, SupportedRomType> s_RomTypeMap;

    Ui::QtEmu *ui;
    QLibrary m_CoreLibrary;
    IEmulatorCore* m_Core;
    bool m_StopCore;
    QThread* m_CoreExecutingThread;
    QThread* m_VideoUpdateThread;
    QThread* m_AudioUpdateThread;

	void LoadCore(SupportedRomType romType);
    void StopEmulatorCore();
    void StartEmulatorCore();
    void EmulatorLoop();
    void VideoLoop();
    void AudioLoop();
};
