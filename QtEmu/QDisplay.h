#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QOpenGLWidget>

class QDisplay : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QDisplay(QWidget *parent = nullptr);

signals:

public slots:
    void RenderFrame(QImage* frame);
};

#endif // QDISPLAY_H
