#ifndef STATE_H
#define STATE_H

class State
{
public:
    State();
    virtual ~State();
};

class StateGoHome : public State
{
    public:
        StateGoHome();
        virtual ~StateGoHome();
};


#endif
