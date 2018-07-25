/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateManager.h
 * Author: default
 *
 * Created on May 10, 2018, 3:02 PM
 */
#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <SFML/System/Time.hpp>
#include "StateMainMenu.h"
#include "StateGame.h"
#include "StatePause.h"
#include "SharedContext.h"

enum class StateType {
    MAIN_MENU = 1,
    GAME,
    PAUSED,
    GAMEOVER,
    CREDITS
};

using StateContainer = std::vector<std::pair<StateType, IBaseState*>>;

using TypeContainer = std::vector<StateType>;

//Factory for automatic creations of different types derived from BaseState class.
using StateFactory = std::unordered_map<StateType, std::function<IBaseState*(void)>>;


class StateManager {
public:
    StateManager(SharedContext* shared);
//    StateManager(const StateManager& orig);
    virtual ~StateManager();
    
    void update(sf::Time& time);
    void draw();
    
    void processRequests();
    
    SharedContext* getContext();
    bool hasState(const StateType& type);
    
    void switchTo(const StateType& type);
    void remove(const StateType& type);
    
private:
    // Methods
    void createState(const StateType& type);
    void removeState(const StateType& type);
    
    
    //?!?!?
    template<class T>
    void registerState(const StateType& type) {     //Using lambda
        m_stateFactory[type] = [this]()->IBaseState*
        {
            return new T(this);
        };
    }
    
    //Members
    SharedContext* m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
    
};

#endif /* STATEMANAGER_H */

