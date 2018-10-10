#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QOpenGLWidget>
#include <memory>

class QDisplay : public QOpenGLWidget
{
    Q_OBJECT
private:
    std::shared_ptr<QImage> m_Backend;
public:
    explicit QDisplay(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void RenderFrame(std::shared_ptr<QImage> frame);
};

#endif // QDISPLAY_H
