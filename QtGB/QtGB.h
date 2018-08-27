#ifndef QTGB_H
#define QTGB_H

#include <QMainWindow>

namespace Ui {
class QtGB;
}

class QtGB : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtGB(QWidget *parent = nullptr);
    ~QtGB();

private:
    Ui::QtGB *ui;
};

#endif // QTGB_H
