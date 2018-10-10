#include <QPainter>
#include "QDisplay.h"

QDisplay::QDisplay(QWidget *parent) :
    QOpenGLWidget (parent),
    m_Backend()
{

}

void QDisplay::RenderFrame(std::shared_ptr<QImage> frame)
{
    m_Backend = frame;
    update();
}

void QDisplay::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    if (m_Backend.get() != nullptr)
    {
        QPainter painter(this);
        painter.drawImage(QPoint(), *m_Backend.get());
    }
}
