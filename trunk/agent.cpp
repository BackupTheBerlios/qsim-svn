#include <math.h>

#include <QPainter>
#include <QMessageBox>

#include "agent.h"
#include "building.h"
#include "simulator.h"
#include "message.h"
#include "goal.h"

Agent::Agent( Simulator* sim, const QPoint& point, int r )
    :
    Object(point,r),
    m_simulator(sim),
    m_oldpos(point),
    m_storeTrajectory(false),
    m_pointSize(10),
    velocity(10),
	_state(0),
    m_agent_state(SEARCH_METEORITO),
    m_catched_meteorito(false),
    m_sensor_radio(15),
    m_currentNode(NULL),
	 FACTOR_RANDOM(0.0),
    m_meteorito(NULL),
    goal_changed(true),
    m_color(Qt::green),
    m_change(false)
{
}

Agent::~Agent()
{
}

bool Agent::ICB_near()
{
   for( ObjectGroup<Building*>::iterator build = m_simulator->m_buildings.begin(); 
						 build != m_simulator->m_buildings.end(); ++build )
	{
		if ( (*build)->isICB )
		{
			int x, y, w, h;
	  		QPoint current = Object::getPos();
			(*build)->_rect.getRect( &x, &y, &w, &h );
			x += w/2;
			y += h/2;
 			if( sqrt(mypow(current.x() -x ,2) + mypow(current.y() - y,2)) < m_sensor_radio )
			{
				return true;
			}
		}
	}
	return false;
}

void Agent::setPos( const QPoint& newpos )
{

    if ( ICB_near() && m_agent_state != DRINK_BEER )
	 {
		reset_graph();
		int probability = 0;
		srand(QDateTime::currentDateTime().toTime_t());
		if ( m_agent_state == DRUNK )
		{
			FACTOR_RANDOM = 3.5f;
		}
		else FACTOR_RANDOM = 0.0f;

		if ( m_agent_state == GO_BACK_IGC )
			probability = (rand()%30);
		else if ( m_agent_state == SEARCH_METEORITO )
			probability = (rand()%10);
		else if ( m_agent_state == DRUNK )
			probability = (rand()%1);

		if ( probability > 0  && probability < 4 )
		{
			m_last_state = m_agent_state;
		 	m_agent_state = DRINK_BEER;
			m_started_drink_beer = QDateTime::currentDateTime();
		}
	 }
	

    if( m_storeTrajectory ) {
        m_trajectory += newpos;
    }
    Object::setPos(newpos);
}

void Agent::go_back_igc()
{
    switch( _state )
    {
        case ENTER_NAVIGATION_MESH:
        {
            m_goal = m_simulator->getNavMesh().findNearest( getPos() );
            m_goal->setVisited(false);
            m_gradient = m_simulator->getGradient( m_goal->getPos() );
            _state = GOTO_NODE;
        }
        break;

        case STUCK:    
            if (m_meteorito != NULL) 
                delete m_meteorito;
            m_meteorito = NULL;
            m_catched_meteorito = false;
            reset_graph();
	 			 m_last_state = m_agent_state;

				m_agent_state = SEARCH_METEORITO;
            _state = ENTER_NAVIGATION_MESH;
        break; 
					
        case GOTO_NODE:
        {
            QPoint current = Object::getPos();
            QPoint pos_goal = m_goal->getPos();

            // Verifica se o objetivo já foi atingido
            if( sqrt(mypow((current.x() - m_goal->getPos().x()),2) +
                 mypow((current.y() - m_goal->getPos().y()),2) ) > m_pointSize )
            {
                // Não foi, continua perseguindo
                setPos( m_simulator->chase( getPos(), m_goal->getPos() ) );
            }
            else {
                // Chegou no objetivo, 
                m_currentNode = m_goal;
                _state = FIND_NEXT_NODE;
            }
        }
        break;

        case FIND_NEXT_NODE:
        {
            // Pega a lista de nós adjacentes a posição atual.
            /// @todo Verificar se o ponteiro m_currentNode é válido (se é que é necessário)
            Node* old_goal = m_goal;
            AdjacencyList::Iterator arc;
            for( arc = m_currentNode->adjacents.begin();
                 arc != m_currentNode->adjacents.end();
                 ++arc )
            {
                (*arc)->to->setColor(Qt::red);
                QPoint ajacent_pot = m_simulator->getGradient( (*arc)->to->getPos() );
                QPoint current_pot = m_simulator->getGradient( m_center );
                double potencial_adjacente = (mypow(ajacent_pot.x(),2) + mypow(ajacent_pot.y(),2));
                double potencial_atual = (mypow(current_pot.x(),2) + mypow(current_pot.y(),2));
                if( potencial_adjacente < potencial_atual )
                {
                    m_goal  = (*arc)->to;
                }
                else
                    (*arc)->to->setColor(Qt::gray);
            }
            if( old_goal != m_goal )
                _state = GOTO_NODE;
            else
                _state = STUCK;
        }
        break;
    }
}

void Agent::drink_beer()
{
  ObjectGroup<Building*>::iterator build;
  QDateTime now;

	for( build = m_simulator->m_buildings.begin(); 
						 	build != m_simulator->m_buildings.end(); ++build )
	{
		if ( (*build)->isICB )
		{
	  		QPoint agentPos = Object::getPos();
			int x, y, w, h;
			(*build)->_rect.getRect( &x, &y, &w, &h );
			x += w/2;
			y += h/2;
			const QPoint point(x,y);
			
			if ((*build)->_rect.contains(agentPos))
			{
				if ( m_last_state == DRUNK )
					m_times_drunk_in_icb++;
				now = QDateTime::currentDateTime();
				break;
			}
			else setPos(m_simulator->chase(agentPos, point));
		}
	}
	if (build != m_simulator->m_buildings.end())
	{
		if ( m_started_drink_beer.secsTo(now) >  TIME_TO_DRINK_BEER+FACTOR_RANDOM )
		{
		  	m_started_drink_beer = QDateTime::currentDateTime();
			reset_graph();
   		m_last_state = m_agent_state;
			m_agent_state = DRUNK;
			_state = ENTER_NAVIGATION_MESH;	
			
		}
	}
}

void Agent::drunk()
{
  QDateTime now = QDateTime::currentDateTime();
	if ( m_started_drink_beer.secsTo(now) >  TIME_DRUNK )
	{
		reset_graph();
		if ( m_times_drunk_in_icb > 3 )
		{
			m_times_drunk_in_icb = 0;
			m_catched_meteorito = false;
			m_simulator->addObstacle( m_meteorito->getPos() );

			if (m_meteorito != NULL)
			{
				delete m_meteorito;
				m_meteorito = NULL;
			}
		}
		if ( m_catched_meteorito )
		{
  			m_last_state = m_agent_state;
		  m_agent_state = GO_BACK_IGC;
		_state = ENTER_NAVIGATION_MESH;	
		}
		else
		{
  			m_last_state = m_agent_state;
		  m_agent_state = SEARCH_METEORITO;
			_state = ENTER_NAVIGATION_MESH;	
		}
	}
	walk_in_graph();
	QPoint point(getPos().x()+1, getPos().y()+1);
	setPos( point );
}

Obstacle* Agent::there_is_meteorito_near()
{
	for( ObjectGroup<Obstacle*>::iterator meteorito = m_simulator->m_obstacles.begin(); 
						 	meteorito != m_simulator->m_obstacles.end();	++meteorito )
   {
	   const QPoint point = (*meteorito)->getPos();
  		QPoint current = Object::getPos();
		if( sqrt(mypow((current.x() - point.x()),2) +
           mypow((current.y() - point.y()),2) ) < m_sensor_radio &&
		 	!(*meteorito)->m_catched )
		{
			return (*meteorito);
		}
	}
	return NULL;
}

Agent* Agent::there_is_agent_near()
{
	for( ObjectGroup<Agent*>::iterator meteorito = m_simulator->getAgents().begin(); 
						 	meteorito != m_simulator->getAgents().end();	++meteorito )
   {
       if ((*meteorito) == this)
           continue;

	   const QPoint point = (*meteorito)->getPos();
  		QPoint current = Object::getPos();
		if( sqrt(mypow((current.x() - point.x()),2) +
           mypow((current.y() - point.y()),2) ) < m_sensor_radio)
		{
			return (*meteorito);
		}
	}
	return NULL;
}

bool Agent::catched_meteorito( Object* meteorito )
{
   QPoint current = Object::getPos();
	if( sqrt(mypow((current.x() - meteorito->getPos().x()),2) +
   		mypow((current.y() - meteorito->getPos().y()),2) ) < m_pointSize )
	{
		return true;
	}
	return false;
}

Node* Agent::reset_graph()
{
	AdjacencyList::Iterator arc;
	for( arc = m_currentNode->adjacents.begin(); arc != m_currentNode->adjacents.end(); ++arc )
	{
		if ( (*arc)->to != NULL)
			(*arc)->to->setVisited(false);
		
		if ( (*arc)->from != NULL)
			(*arc)->from->setVisited(false);
	}
   return m_simulator->getNavMesh().findNearest( getPos() );
}

void Agent::walk_in_graph()
{
	if (m_currentNode == NULL)
       m_currentNode = m_simulator->getNavMesh().findNearest( getPos() );
	else
	{			  
		setPos(m_simulator->chase( getPos(), m_currentNode->getPos() ));
  	 	QPoint current = Object::getPos();
		if ( sqrt(mypow((current.x() - m_currentNode->getPos().x()),2) +
   		mypow((current.y() - m_currentNode->getPos().y()),2) ) < m_pointSize )
		{
			Node* node = NULL;
  			AdjacencyList::Iterator arc;
			srand(QDateTime::currentDateTime().toTime_t());
			int nodo_rand = rand()%m_currentNode->adjacents.count();
			int i = 0;
	      for( arc = m_currentNode->adjacents.begin(); arc != m_currentNode->adjacents.end(); ++arc )
			{
				if ( i == nodo_rand )
				{
					if ( (*arc)->to != NULL )
					{
						node = (*arc)->to;
					}
					else if ( (*arc)->from != NULL )
					{
						node = (*arc)->from;
					}
					break;
				}
				i++;				
			}
			if (node == NULL)
				node =m_simulator->getNavMesh().findNearest( getPos() );

			m_currentNode = node;
		}

	}
}

void Agent::catch_meteorito()
{
	if ( m_meteorito->m_catched )
	{
		m_last_state = m_agent_state;
 		m_agent_state = SEARCH_METEORITO;
		_state = ENTER_NAVIGATION_MESH;	
		return;
	}
			
	if ( catched_meteorito(m_meteorito) )
	{
		// remove o objeto meteorito da lista do simulador
		m_meteorito->m_catched = true;
		for( ObjectGroup<Obstacle*>::iterator it = m_simulator->m_obstacles.begin(); it != 
												   m_simulator->m_obstacles.end(); ++it )
    	{
      	if( *it == m_meteorito ) 
			{
      		m_simulator->m_obstacles.erase(it);
				break;
			}
       }

		m_catched_meteorito = true;
		reset_graph();
		m_last_state = m_agent_state;
		m_agent_state = GO_BACK_IGC;
	}
	else	setPos(m_simulator->chase( getPos(), m_meteorito->getPos() ));
}

void Agent::search_meteorito()
{
	Obstacle* meteorito = there_is_meteorito_near();
	if ( meteorito != NULL )
	{
		reset_graph();
		m_last_state = m_agent_state;
		m_agent_state = CATCH_METEORITO;
		m_meteorito = meteorito;
	}
	else
		walk_in_graph();
}

void Agent::enterMesh()
{
    m_goal = m_simulator->getNavMesh().findNearest(getPos());
}

/*void Agent::gotoGoal()
{
    ObjectGroup<Goal*>& goals = m_simulator->getGoals();
    
    if (goals.isEmpty())
        return 0;

    Goal* goal = *goals.begin();
    m_goal = m_simulator->getNavMesh().findNearest(goal->getPos());
}*/

unsigned int Agent::think(const QPoint &p, bool change)
{
    // guarda comando de mudar de pista
    if (!m_change)
        m_change = m_simulator->m_change;

    // Select next node to go
    switch (_state) {
        case ENTER_NAVIGATION_MESH: {
            enterMesh();
        }
        break;
    }

    if (!m_goal) {
        // removeAgent();
        return 0;
    }

    if(there_is_agent_near())
        return 0;

    // Vai até o m_goal
    QPoint current = Object::getPos();
    QPoint pos_goal = m_goal->getPos();

    // Verifica se o objetivo já foi atingido
    if( sqrt(mypow((current.x() - m_goal->getPos().x()),2) +
         mypow((current.y() - m_goal->getPos().y()),2) ) > m_pointSize )
    {
        // Não foi, continua perseguindo
        setPos( m_simulator->chase( getPos(), m_goal->getPos() ) );
        if (velocity != m_pointSize)
            setPos( m_simulator->chase( getPos(), m_goal->getPos() ) );
    }
    else {
        // Chegou no objetivo, 
        m_currentNode = m_goal;
        m_goal = m_simulator->getNavMesh().findNext(m_goal, m_change);
        m_change = false; // desliga o mudar de pista
        _state = FIND_NEXT_NODE;
    }

    return 0;
}

void Agent::render( QPainter& painter )
{
    QPen pen;
    pen.setWidth(2);
    if ( m_agent_state == DRINK_BEER ) {
        pen.setColor(Qt::darkYellow);
    }
    else if ( m_agent_state == DRUNK ) {
        pen.setColor(Qt::darkMagenta);
    }
    else if ( m_agent_state == CATCH_METEORITO ) {
        pen.setColor(Qt::yellow);
    }
    else if ( m_catched_meteorito ) {
        pen.setColor(Qt::cyan);
    }
    else {
        pen.setColor(Qt::black);
        pen.setWidth(1);
    }
    
    // Draw sensor
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QRectF(getPos().x() - m_sensor_radio,
                        getPos().y() - m_sensor_radio,
                        m_sensor_radio*2, m_sensor_radio*2));

    // Draw agent
    painter.setPen(Qt::black);
    painter.setBrush(m_color);
    
    painter.drawRect(QRectF(getPos().x() - m_pointSize,
                        getPos().y() - m_pointSize,
						m_pointSize*2, m_pointSize*2));
}
//     if( m_storeTrajectory )
//     {
//         painter.setPen(Qt::green);
//           
//         for( QVector<QPoint>::Iterator i = trajectory().begin();
//              i != trajectory().end();
//              ++i )
//         {
//             painter.drawEllipse(QRectF(i->x() - m_pointSize/2,
//                                 i->y() - m_pointSize/2,
//                                 m_pointSize, m_pointSize));
//         }
//     }


void Agent::steal()
{
	 m_simulator->addObstacle( m_meteorito->getPos() );
	 if (m_meteorito != NULL)
	 {
		delete m_meteorito;
		m_meteorito = NULL;
	 }
   m_catched_meteorito = false;
    m_agent_state = SEARCH_METEORITO;
    _state = ENTER_NAVIGATION_MESH;
}

void Agent::send(Message& msg)
{
    m_simulator->onMessage(msg);
}

void Agent::Observe()
{
    /// @todo implement me
}
