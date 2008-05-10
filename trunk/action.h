#ifndef ACTION_H
#define ACTION_H

class Object;

class Action
{
    public:
        Action();

        virtual ~Action();
        virtual void Execute()=0;
};

class ActGotoNode : public Action
{
    public:

        ActGotoNode(Object*, Object*);
        virtual ~ActGotoNode();
        virtual void Execute();

    private:
        Object* _from;
        Object* _to;
};


#endif
