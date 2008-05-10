#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

class Behaviour : public State
{
    public:

        Behaviour();
        ~Behaviour();
        
        virtual void exec(const Message& msg) = 0;

    protected:
        
        virtual void deliberate() = 0;
        virtual void act() = 0;

        //ActionContainer _actions;

};

/**
    Implementa o comportamento de coletar um objeto
*/
class BehaviourCollect : public Behaviour
{
    public:
        BehaviourCollect();
        virtual ~BehaviourCollect();
        
        virtual void exec(const Message& msg);
       
        // Transitions
        void enter_nav_mesh(const Message& event);
        void next_node(const Message& event);
        void sense(const Message& event);
        void goto_goal(const Message& event);
        void collect(const Message& event);

        void enter_nav_mesh();
        void next_node();
        void sense();
        void goto_goal();
        void collect();
        
    protected:

        virtual void deliberate();
        virtual void act();
};

#endif
