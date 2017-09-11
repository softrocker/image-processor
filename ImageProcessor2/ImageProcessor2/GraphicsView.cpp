#include "GraphicsView.h"
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QWidget>

GraphicsView::GraphicsView(QWidget* parent) :
    QGraphicsView(parent)
{

}

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent) :
	QGraphicsView(scene, parent)
{

}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    const double scaleFactor = 1.15;
    if(event->delta() > 0)
        scale(scaleFactor, scaleFactor);
    else
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
}