#include "goal.h"

#include <QPainter>
#include <QPoint>

Goal::Goal( const QPoint& point, int r )
    :
    Object(point,r),
    m_pointSize(10)
{
}


Goal::~Goal()
{
}

void Goal::render( QPainter& painter )
{
    painter.setPen(Qt::black);
    painter.drawEllipse(QRectF(getPos().x() - m_pointSize,
                        getPos().y() - m_pointSize,
                        m_pointSize*2, m_pointSize*2));
}
