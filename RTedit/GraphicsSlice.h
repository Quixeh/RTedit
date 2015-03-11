#ifndef GRAPHICSSLICE_H
#define GRAPHICSSLICE_H

#include <QObject>
#include <QGraphicsView>

class GraphicsSlice : public QGraphicsView {
    Q_OBJECT
    public:
        explicit GraphicsSlice(QObject *parent = 0);
        ~GraphicsSlice();
        void setAxis(int);

    signals:

    public slots:

    protected:
        void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
        int axis;
};

#endif // GRAPHICSSLICE_H
