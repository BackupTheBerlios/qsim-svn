#ifndef THIEF_H
#define THIEF_H

#include <QtGlobal>

#include "agent.h"

/** 
    @class Thief
    
    Special Agent Marcos Valério, o ladrão de meteoritos!
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
        
            @return Retorna o agente mais próximo no raio do sensor ou NULL caso
                    não haja nenhum.
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
