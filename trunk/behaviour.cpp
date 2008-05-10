#include "state.h"
#include "message.h"
#include "behaviour.h"

Behaviour::Behaviour()
{
}

Behaviour::~Behaviour()
{
}

BehaviourCollect::BehaviourCollect()
{
}

BehaviourCollect::~BehaviourCollect()
{
}

/* -----------------------------------------------------------------------------------------
    Transition table

     State                  Event                  Next State
    ==========================================================================
    ENTER_NAVIGATION_MESH   IN_NAVIGATION_MESH     NEXT_NODE
    NEXT_NODE               NODE_NOT_REACHED       NEXT_NODE
    NEXT_NODE               NODE_REACHED           SENSE
    SENSE                   OBJECT_DETECTED        GOTO_GOAL
    SENSE                   NO_OBJECT_DETECTED     NEXT_NODE
    GOTO_GOAL               NODE_REACHED           COLLECT
    GOTO_GOAL               NODE_NOT_REACHED       NEXT_NODE
    COLLECT                 COLLECT_OK             FINISH
    COLLECT                 COLLECT_FAIL           NEXT_NODE

    State Actions:
    
    ENTER_NAVIGATION_MESH
        - find nearest node
        - goto node

    NEXT_NODES
        - test if object detected
        - generate next node (object or node)
        - goto node

    FINISH
*/

/*
void StateEnterNavMesh::transition(const Message& event)
{
    if( event == IN_NAVIGATION_MESH ) {
        _state = NEXT_NODE;
    }
}
*/
void StateNextNode::transition(const Message& event)
{
    if( event == NODE_REACHED )
        _state = SENSE;
    else if( event == NODE_NOT_REACHED )
        _state = NEXT_NODE;
}

void StateSense::transition(const Message& event)
{
    if( event == OBJECT_DETECTED )
        _state = GOTO_GOAL;
    else if( event == NO_OBJECT_DETECTED )
        _state = NEXT_NODE;
}

void StateGotoGoal::transition(const Message& event)
{
    if( event == NODE_REACHED )
        _state = COLLECT;
    else if( event == NODE_NOT_REACHED )
        _state = NEXT_NODE;
}

void StateCollect::transition(const Message& event)
{
    if( event == COLLECT_OK)
        _state = FINISH;
    else if( event == COLLECT_FAIL)
        _state = NEXT_NODE;
}

BehaviourCollect::exec(const Message& event)
{
    _state = _sate->transition(event);
    _state->deliberate();
}

/*
void StateEnterNavMesh::deliberate()
{
    find_next_node(); // deliberation
    goto_node(); // action
}
*/

void StateNextNode::deliberate()
{
}

void StateSense::deliberate()
{
}

void StateGotoGoal::deliberate()
{
}

void StateCollect::deliberate()
{
}

/*
    // Sense
    switch( _state )
{
        case ENTER_NAVIGATION_MESH : enter_nav_mesh(event); break;
        case NEXT_NODE: next_node(event); break;
        case SENSE: sense(event); break;
        case GOTO_GOAL: goto_goal(event); break;
        case COLLECT: collect(event); break;
}
    deliberate();
    act();
    */