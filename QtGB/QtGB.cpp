#include "QtGB.h"
#include "ui_QtGB.h"
#include "IQtGBMemory.h"
#include "IQtGBCPU.h"
#include <QLibrary>

QtGB::QtGB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtGB)
{
    ui->setupUi(this);

    QLibrary lib("GBCore");
    lib.resolve("GetCore")();

	IQtGBMemory* memory = IQtGBMemory::GetInstance();
#ifdef Q_OS_MACX
	memory->LoadBios("../../../Bios.gb");
#else
	memory->LoadBios("Bios.gb");
#endif
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
