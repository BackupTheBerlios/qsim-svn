#ifndef NAVMESH_H
#define NAVMESH_H

#include <QVector>
#include <QLine>

#include "node.h"

class QPoint;
class QPainter;

class NavMesh
{
    public:

        NavMesh();
        ~NavMesh();

        void addNode(const QPoint& position);
        void addArc( Node* from, Node* to);

        void removeArc(Arc* arc);
        void removeArc(Node* from, Node* to);
        void removeNode(Node* n);

        // Busca
        Node* find( QPoint position );
		Node* findNearest( QPoint position );
        Node* searchDepthFirst(Node *start, Node* goal);
        Node* EulerianNext(Node *start);
        bool joint(Arc*);
        void render(QPainter&);
	    bool Conected();

        QVector<QPoint> getNodes();
        QVector<QLine> getArcs();

        typedef QVector<Node*> NodeVector;
        typedef QVector<Arc*>  ArcVector;

    private:

        friend class Simulator;
        
        NodeVector _vertices;
        ArcVector  _arcs;

};

#endif
