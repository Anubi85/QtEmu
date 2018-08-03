#include "QtGB.h"
#include "ui_QtGB.h"

QtGB::QtGB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtGB)
{
    ui->setupUi(this);
}

QtGB::~QtGB()
{
    delete ui;
}
