#include "QtGB.h"
#include "ui_QtGB.h"
#include "IQtGBMemory.h"
#include "IQtGBCPU.h"

QtGB::QtGB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtGB)
{
    ui->setupUi(this);
    IQtGBMemory* memory = IQtGBMemory::GetInstance();
    memory->LoadBios("Bios.gb");
    IQtGBCPU* cpu = IQtGBCPU::GetInstance();
    cpu->Reset();
    while (!cpu->HasError())
    {
        cpu->Exec();
    }
}

QtGB::~QtGB()
{
    delete ui;
}
