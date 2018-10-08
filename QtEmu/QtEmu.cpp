#include "QtEmu.h"
#include "ui_QtEmu.h"
#include <QLibrary>

QtEmu::QtEmu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtEmu)
{
    ui->setupUi(this);
    m_Core = nullptr;
    m_CoreExecutingThread = nullptr;
    m_ScreenBuffer = nullptr;
    m_ScreenBuferMutex = new QMutex();
}

QtEmu::~QtEmu()
{
    delete ui;
    delete m_Core;
    delete m_CoreExecutingThread;
    free(m_ScreenBuffer);
    delete m_ScreenBuferMutex;
}

void QtEmu::on_actionLoad_ROM_triggered()
{
    //TODO: display file selection and check ROM extension
    QLibrary lib("GBCore");
    StopEmulatorCore();
    delete m_Core;
    try
    {
        m_Core = reinterpret_cast<IEmulatorCore*(*)()>(lib.resolve("GetCore"))();
        int screenWidth, screenHeight;
        m_Core->GetScreenSize(screenWidth, screenHeight);
        //set screen size
        ui->screen->setMinimumSize(screenWidth, screenHeight);
        //fix window size
        adjustSize();
        //load bios and rom
        //TODO: handle bios skip and rom selection
        if (!m_Core->LoadBios("Bios.gb"))
        {
            //TODO: handle failure in bios load
        }
        if (!m_Core->LoadRom("Tetris.gb"))
        {
            //TODO: handle failure in rom load
        }
        //prepare screen buffer
        m_ScreenBuffer = static_cast<quint32*>(malloc(static_cast<unsigned int>(screenHeight) * static_cast<unsigned int>(screenWidth) * sizeof(quint32)));
        //pass screen buffer and buffer mutex o the emulator core
        m_Core->SetScreenBuffer(m_ScreenBuffer, m_ScreenBuferMutex);
        //start the emulator main loop in a separate thread
        StartEmulatorCore();
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
            m_CoreExecutingThread->exit();
            m_CoreExecutingThread->wait();
            delete m_CoreExecutingThread;
        }
        free(m_ScreenBuffer);
        m_ScreenBuferMutex->unlock();
    }
    else
    {
        //TODO: handle error
    }
}

void QtEmu::StartEmulatorCore()
{
    if (m_Core != nullptr)
    {
        m_CoreExecutingThread = QThread::create([this] { EmulatorLoop(); });
        m_CoreExecutingThread->start(QThread::HighestPriority);
    }
    else
    {
        //TODO: handle error
    }
}

void QtEmu::EmulatorLoop()
{
    while(!m_Core->HasError())
    {
        m_Core->Exec();
    }
}
