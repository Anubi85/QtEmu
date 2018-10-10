#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QOpenGLWidget>
#include <memory>

class QDisplay : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QDisplay(QWidget *parent = nullptr);

signals:

public slots:
    void RenderFrame(std::shared_ptr<QImage> frame);
};

#endif // QDISPLAY_H
