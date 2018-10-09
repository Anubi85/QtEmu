#include "QtEmu.h"
#include "ui_QtEmu.h"
#include <QLibrary>

QMap<QString, QtEmu::SupportedRomType> QtEmu::s_RomTypeMap =
{
    { "gb", SupportedRomType::gb}
};

QtEmu::QtEmu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtEmu),
    m_CoreLibrary(),
    m_VideoDataBuffer()
{
    ui->setupUi(this);
    m_Core = nullptr;
    m_CoreExecutingThread = nullptr;
    m_StopCore = false;
    m_VideoDataBuffer.clear();
}

QtEmu::~QtEmu()
{
    delete ui;
    delete m_Core;
    delete m_CoreExecutingThread;
}

void QtEmu::on_actionLoad_ROM_triggered()
{
    //TODO: display file selection
    QString biosFilePath = "Bios.gb";
    QString romFilePath = "Tetris.gb";
    StopEmulatorCore();
    try
    {
        switch (s_RomTypeMap[QFileInfo(romFilePath).suffix()])
        {
        case SupportedRomType::gb:
            m_CoreLibrary.setFileName("GBCore");
            break;
        }
        m_Core = reinterpret_cast<IEmulatorCore*(*)()>(m_CoreLibrary.resolve("GetCore"))();
        int screenWidth, screenHeight;
        m_Core->GetScreenSize(screenWidth, screenHeight);
        //set screen size
        ui->screen->setMinimumSize(screenWidth, screenHeight);
        //fix window size
        adjustSize();
        //prepare screen buffer
        m_VideoDataBuffer.resize(screenWidth * screenHeight);
        //initialize emulator core
        if (m_Core->Initialize(biosFilePath, romFilePath))
        {
            //start the emulator main loop in a separate thread
            StartEmulatorCore();
        }
        else
        {
            //TODO: handle initialization error
        }
    }
    catch (QException)
    {
        //TODO: proper error handling
    }
}

void QtEmu::StopEmulatorCore()
{
    if (m_Core != nullptr)
    {
        if (m_CoreExecutingThread != nullptr && m_CoreExecutingThread->isRunning())
        {
            m_StopCore = true;
            m_CoreExecutingThread->wait();
            delete m_CoreExecutingThread;
        }
        delete m_Core;
    }
    if (m_CoreLibrary.isLoaded())
    {
        m_CoreLibrary.unload();
    }
    m_VideoDataBuffer.clear();
}

void QtEmu::StartEmulatorCore()
{
    if (m_Core != nullptr)
    {
        m_CoreExecutingThread = QThread::create([this] { EmulatorLoop(); });
        m_CoreExecutingThread->start(QThread::HighestPriority);
    }
}

void QtEmu::EmulatorLoop()
{
    while(!m_Core->HasError() && !m_StopCore)
    {
        m_Core->Exec();
    }
}

void QtEmu::VideoLoop()
{
    while(!m_Core->HasError() && !m_StopCore)
    {
        memcpy(m_VideoDataBuffer.data(), m_Core->GetFrame(), static_cast<unsigned int>(m_VideoDataBuffer.size()));
        //TODO: process frame data
    }
}
