/* 
 * File:   StateMachine.h
 * Author: usuario
 *
 * Created on 14 de octubre de 2013, 9:04
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include <cstdlib>
#include <assert.h>
#include <typeinfo>


#include "State.h"

template <class entity_type>
 
class StateMachine {
public:
    StateMachine(entity_type* owner):m_pOwner(owner), m_pCurrentState(NULL), m_pPreviousState(NULL), m_pGlobalState(NULL){}
    
    void SetCurrentState(State<entity_type>* s) {m_pCurrentState = s;}
    void SetGlobalState(State<entity_type>* s) {m_pGlobalState = s;}
    void SetPreviousState(State<entity_type>* s) {m_pPreviousState = s;}
    
    virtual ~StateMachine(){}

    void Update() const
    {
        if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
        if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
    }
    
    void ChangeState(State<entity_type>*  pNewState)
    {
        assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");
        m_pPreviousState = m_pCurrentState;
        m_pCurrentState->Exit(m_pOwner);
        m_pCurrentState = pNewState;
        m_pCurrentState->Enter(m_pOwner);
    }
    
    void RevertToPreviousState()
    {
        ChangeState(m_pPreviousState);
    }
    
    State<entity_type>* CurrentState() const{return m_pCurrentState;}
    State<entity_type>* GlobalState() const{return m_pGlobalState;}
    State<entity_type>* PreviousState() const{return m_pPreviousState;}
    
    bool isInState(const State<entity_type>*st)const
    {
        return typeid(*m_pCurrentState) == typeid(*st);
    }
    
private:
    entity_type* m_pOwner;

    State<entity_type>* m_pCurrentState;
    
    State<entity_type>* m_pPreviousState;
    
    State<entity_type>* m_pGlobalState;

};

#endif	/* STATEMACHINE_H */

