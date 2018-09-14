#include "QtGB.h"
#include "ui_QtGB.h"
#include "IEmulatorCore.h"
#include <QLibrary>
#include <memory>

QtGB::QtGB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtGB)
{
    ui->setupUi(this);

    QLibrary lib("GBCore2");
    std::unique_ptr<IEmulatorCore> core(reinterpret_cast<IEmulatorCore*(*)()>(lib.resolve("GetCore"))());
    core->LoadBios("Bios.gb");
    while (!core->HasError())
    {
        core->Exec();
    }
}

QtGB::~QtGB()
{
    delete ui;
}
