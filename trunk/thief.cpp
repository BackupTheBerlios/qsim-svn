#include "thief.h"
#include "navmesh.h"
#include "simulator.h"

#include <QLineF>
#include <QPainter>

Thief::Thief(Simulator* sim, const QPoint& point, int r)
    : Agent(sim, point, r),
      m_pointSize(10),
      _state(SEEK),
      _sensorRadius(20)
{
}

Thief::~Thief()
{
}

void Thief::think()
{
    switch( _state )
    {
        case SEEK:
            seek(); // Procura por uma vítima
            break;
        
        case CHASE:
            chase(); // Persegue uma vítima
            break;
            
        case STEAL:
            steal(); // Rouba o meteorito
            break;
    }
}

// Facilita o acesso à malha de navegação
//#define m_simulator->getNavMesh() MESH

void Thief::steal()
{
}

void Thief::chase()
{
    setPos( m_simulator->chase( getPos(), _victim->getPos() ) );
    if ( catched_meteorito( _victim ) )
    {
        _victim->steal();
        _state = SEEK;
    }
}

void Thief::seek()
{
    Agent* agent = senseAgent();
    if ( agent != NULL )
    {
        if ( agent->m_catched_meteorito )
        {
            reset_graph();
            _state = CHASE;
            _victim = agent;
        }
    }
    else
        walk_in_graph();
}

Agent* Thief::senseAgent()
{
    qreal best_distance = _sensorRadius;
    Agent* selected_agent = 0;

    // para todos os agentes...
    for( ObjectGroup<Agent*>::iterator a = m_simulator->getAgents().begin();
         a != m_simulator->getAgents().end();
         ++a )
    {
        // Calcula a distância entre o o ladrão e o agente
        qreal current_agent_distance = QLineF( m_center, (*a)->getPos()).length();

        if ( current_agent_distance < best_distance )
        {
            selected_agent = (*a);
            best_distance = current_agent_distance;
        }
    }
    return selected_agent;
}

void Thief::render( QPainter& painter )
{
    const QPoint& point = getPos();
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawEllipse(QRectF(point.x() - m_pointSize,
                        point.y() - m_pointSize,
                        m_pointSize*2, m_pointSize*2));
}
