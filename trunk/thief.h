#ifndef THIEF_H
#define THIEF_H

#include <QtGlobal>

#include "agent.h"

/** 
    @class Thief
    
    Special Agent Marcos Val�rio, o ladr�o de meteoritos!
*/
class Thief : public Agent
{
    public:
        Thief(Simulator* sim, const QPoint& point, int r);
        virtual ~Thief();

        virtual void render(QPainter&);
        virtual void think();
        
        
    protected:

        void seek();
        void chase();
        void steal();
        
        /** Sensor de agentes
        
            @return Retorna o agente mais pr�ximo no raio do sensor ou NULL caso
                    n�o haja nenhum.
         */
        Agent* senseAgent();

        enum ThiefState
        {
            SEEK,
            CHASE,
            STEAL
        };


        qreal _sensorRadius;
        Agent* _victim;
        int m_pointSize;
        int _state;
};

#endif
