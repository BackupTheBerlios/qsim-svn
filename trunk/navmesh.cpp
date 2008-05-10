#include "navmesh.h"
#include "node.h"

#include <QPainter>
#include <QPoint>
#include <QStack>

NavMesh::NavMesh()
{
}

NavMesh::~NavMesh()
{
    for( NodeVector::Iterator v = _vertices.begin(); v != _vertices.end(); ++v )
    {
        AdjacencyList::Iterator arc;
        for( arc = (*v)->adjacents.begin(); arc != (*v)->adjacents.end(); ++arc )
            delete (*arc);
        delete (*v);
    }
}

void NavMesh::render(QPainter& painter)
{
    // Itera entre os vertices do grafo
    for( NodeVector::Iterator v = _vertices.begin(); v != _vertices.end(); ++v )
    {
        int m_pointSize = 10;
        const QPoint point = (*v)->getPos();
        painter.setPen(Qt::gray);
        
        painter.setBrush( (*v)->getColor() );

        painter.drawEllipse(QRectF(point.x() - m_pointSize,
                    point.y() - m_pointSize,
                    m_pointSize*2, m_pointSize*2));

        // Desenha os arcos partindo deste nó
        /// @todo Fazer com que um arco A<->B não seja desenhado 2x
        AdjacencyList::Iterator arc;
        for( arc = (*v)->adjacents.begin(); arc != (*v)->adjacents.end(); ++arc )
        {
            painter.drawLine( (*arc)->from->getPos(), (*arc)->to->getPos() );
        }
    }
}

Node* NavMesh::findNearest( QPoint position )
{
    qreal distance = -1;
    Node* node;

    for( NodeVector::Iterator v = _vertices.begin(); v != _vertices.end(); ++v )
    {
        qreal d = QLineF(position, (*v)->getPos()).length();
        if ((distance < 0) || d < distance)
        {
            distance = d;
            node = (*v);
        }
    }
    return node;
}

Node* NavMesh::find( QPoint position )
{
    qreal distance = -1;
    for( NodeVector::Iterator v = _vertices.begin(); v != _vertices.end(); ++v )
    {
        qreal d = QLineF(position, (*v)->getPos()).length();
        if ((distance < 0 && d < 12) || d < distance)
            return (*v);
    }
    return 0;
}

void NavMesh::addNode(const QPoint& position)
{
    _vertices += new Node(position);
}


void NavMesh::removeArc(Arc* arc)
{
    removeArc( arc->from, arc->to );
}

void NavMesh::removeArc(Node* from, Node* to)
{
    // Remove arco da lista de arcos
    for( ArcVector::Iterator arc = _arcs.begin(); arc != _arcs.end(); ++arc )
        if( (*arc)->from == from && (*arc)->to == to  ||
            (*arc)->to == from && (*arc)->from == to  )
            _arcs.erase(arc);

    // Remove os arcos da lista de adjacência
    for( ArcVector::Iterator arc = from->adjacents.begin(); arc != from->adjacents.end(); ++arc )
        if( (*arc)->from == from && (*arc)->to == to  )
            from->adjacents.erase( arc );

    for( ArcVector::Iterator arc = to->adjacents.begin(); arc != to->adjacents.end(); ++arc )
        if( (*arc)->to == from && (*arc)->from == to  )
            to->adjacents.erase( arc );
}

void NavMesh::addArc(Node* from, Node* to)
{
    // Cria arcos nos dois sentidos
    Arc* ab = new Arc(from,to);
    Arc* ba = new Arc(to,from);
    
    // Adiciona os arcos no vetor de arcos
    _arcs += ab;
    _arcs += ba;

    // Adiciona os arcos nas respectivas listas de ajacências
    from->adjacents += ab;
    to->adjacents   += ba;
}

bool NavMesh::Conected()
{
    /// @todo implement me
	return false;
}

bool NavMesh::joint(Arc* arc)
{
    return 0;
}

Node* NavMesh::EulerianNext(Node *start)
{
    AdjacencyList::Iterator arc;
    for( arc = start->adjacents.begin(); arc != start->adjacents.end(); ++arc )
    {
        if( !joint(*arc) )
            return (*arc)->to;
    }
}

Node* NavMesh::searchDepthFirst(Node *start, Node* goal)
{
    QStack<Node*> stack;
    stack.push(start);
    while( !stack.empty() )
    {
        Node* node = stack.pop();
        if ( node->visited() ) 
            continue;
        if ( node == goal ) 
            return node;
        node->setVisited(true);
        AdjacencyList::Iterator arc;
        for( arc = node->adjacents.begin(); arc != node->adjacents.end(); ++arc )
        {
            if ( ! (*arc)->to->visited() )
                stack.push( (*arc)->to );
        }
    }
    return 0;
}

QVector<QPoint> NavMesh::getNodes()
{
    QVector<QPoint> points;
    NodeVector::Iterator v;
    for( v = _vertices.begin(); v != _vertices.end(); ++v )
    {
        points += (*v)->getPos();
    }
    return points;
}

QVector<QLine> NavMesh::getArcs()
{
    QVector<QLine> arcs;
    NodeVector::Iterator v;
    for( v = _vertices.begin(); v != _vertices.end(); ++v )
    {
        AdjacencyList::Iterator arc;
        for( arc = (*v)->adjacents.begin(); arc != (*v)->adjacents.end(); ++arc )
        {
            arcs += QLine( (*arc)->from->getPos(), (*arc)->to->getPos() );
        }
    }
    return arcs;
}