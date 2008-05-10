#ifndef MESSAGE_H
#define MESSAGE_H

class Action;

class Message
{
public:
    Message( Action& );
    ~Message();

protected:
    Action* _action;
};

#endif
