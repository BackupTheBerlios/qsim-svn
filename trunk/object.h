#ifndef OBJECT_H
#define OBJECT_H

#include <QPoint>
#include <QDataStream>

class QPainter;

class Object
{
public:

    Object(const QPoint& center, int radius);
    virtual ~Object();

    inline const QPoint& getPos() const { return m_center; }
    inline void setPos(const QPoint& pos) { m_center = pos; }

    inline void setRadius( int r ) { m_radius = r; }
    virtual void render(QPainter&)=0;
    
protected:

        QPoint m_center;
        int    m_radius;
};

QDataStream &operator<<( QDataStream & out, const Object* obj );
QDataStream &operator>>( QDataStream & in, Object* obj );

#endif
