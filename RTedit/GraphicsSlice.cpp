#include "GraphicsSlice.h"
#include <QObject>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <DCMScan.h>

extern DCMScan* scan;

GraphicsSlice::GraphicsSlice(QObject*){

}

GraphicsSlice::~GraphicsSlice(){

}

void GraphicsSlice::wheelEvent(QWheelEvent *e){
    if (e->modifiers() & Qt::ControlModifier) {
        // Zoom Functions go here
    } else {
        // Slice Change goes here...
        if (e->delta() > 0){
            scan->nextSlice();
        } else {
            scan->previousSlice();
        }
        QGraphicsView::wheelEvent(e);
    }
}
