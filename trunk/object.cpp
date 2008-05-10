#include "object.h"

Object::Object(const QPoint& c, int r)
    :
    m_center( c ),
    m_radius( r )
{
}


Object::~Object()
{
}

QDataStream &operator<<( QDataStream & out, const Object* obj )
{
    return out;
}

QDataStream &operator>>( QDataStream & in, Object* obj )
{
    return in;
}