#include "obstacle.h"

#include <QPoint>
#include <QPainter>

Obstacle::Obstacle(const QPoint& point, int r)
    :
	 m_catched(false),
    Object(point,r)
{
}

Obstacle::~Obstacle(void)
{
}


void Obstacle::render( QPainter& painter )
{
    int m_pointSize = 6;
    painter.drawEllipse(QRectF(getPos().x() - m_pointSize,
                        getPos().y() - m_pointSize,
                        m_pointSize*2, m_pointSize*2));
}
