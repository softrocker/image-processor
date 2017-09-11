#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class QGraphicsScene;
class QWidget;

class GraphicsView : public QGraphicsView
{
public:
	explicit GraphicsView (QWidget* parent = 0);
	explicit GraphicsView (QGraphicsScene* scene, QWidget* parent = 0);
protected:
    void wheelEvent(QWheelEvent* event);
};

#endif