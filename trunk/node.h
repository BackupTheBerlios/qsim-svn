#ifndef NODE_H
#define NODE_H

#include <QPoint>
#include <QVector>
#include <QColor>

#include "object.h"

class Arc;
typedef QVector<Arc*> AdjacencyList;

class Node : public Object
{
    public:
        Node(const QPoint& pos, int r = 0) : Object(pos,r), _color(Qt::gray) {}

        bool visited() { return _visited; }
        void setVisited(bool val) { _visited = val; }

        virtual void render(QPainter&){}
        AdjacencyList adjacents;

        void setColor(QColor color) { _color = color; }
        const QColor& getColor() const { return _color; }

    private:

        bool _visited;
        QColor _color;
};

class Arc
{
    public:
        Arc(Node* f, Node* t) : from(f), to(t) {}
        Node* from;
        Node* to;
};

#endif
