#include "GraphicsSlice.h"
#include <QObject>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <DCMScan.h>

extern DCMScan* scan;

GraphicsSlice::GraphicsSlice(QObject*){
    axis = 0; // Default to Transverse
}

GraphicsSlice::~GraphicsSlice(){

}

void GraphicsSlice::setAxis(int newAxis){
    axis = newAxis;
}

void GraphicsSlice::wheelEvent(QWheelEvent *e){
    if (e->modifiers() & Qt::ControlModifier) {
        // Zoom Functions go here
    } else {
        // Slice Change goes here...
        if (e->delta() > 0){
            scan->nextSlice(axis);

        } else {
            scan->previousSlice(axis);
        }
        QGraphicsView::wheelEvent(e);
    }
}
