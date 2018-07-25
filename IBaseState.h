/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IBaseState.h
 * Author: default
 *
 * Created on May 14, 2018, 2:01 PM
 */

#ifndef IBASESTATE_H
#define IBASESTATE_H

#include <SFML/Graphics.hpp>

class StateManager;

class IBaseState {
    friend class StateManager;
public:
    IBaseState(StateManager* state) 
        : m_stateManager{state},
          m_transparent{false},
          m_transcendent{false} {
              
    }   //End Constructor
    //Virtual deconstructor.
    virtual ~IBaseState() {}
    
    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
    
    virtual void activate() = 0;
    virtual void deActivate() = 0;
    
    virtual void update(const sf::Time& time) = 0;
    virtual void draw() = 0;
    
    void setTransparent(const bool& transparent) {
        m_transparent = transparent;
    }
    bool isTransparent() {
        return m_transparent;
    }
    void setTranscendent(const bool& transcendent) {
        m_transcendent = transcendent;
    }
    bool isTranscendent() {
        return m_transcendent;
    }
    StateManager* getStateManager() {
        return m_stateManager;
    }
    sf::View& getView() {
        return m_view;
    }
protected:
    StateManager* m_stateManager;
    bool m_transparent;
    bool m_transcendent;
    sf::View m_view;
};

#endif /* IBASESTATE_H */

