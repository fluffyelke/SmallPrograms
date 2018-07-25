/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateManager.cpp
 * Author: default
 * 
 * Created on May 10, 2018, 3:02 PM
 */

#include <algorithm>

#include "StateManager.h"

StateManager::StateManager(SharedContext* shared) 
    : m_shared{shared} {
    registerState<StateMainMenu>(StateType::MAIN_MENU);
    registerState<StateGame>(StateType::GAME);
    registerState<StatePause>(StateType::PAUSED);
}

//StateManager::StateManager(const StateManager& orig) {
//}

StateManager::~StateManager() {
    for(auto& it : m_states) {
        it.second->onDestroy();
        delete it.second;
    }
}

void StateManager::draw() {
    
    if(m_states.empty()) {
        return;
    }
    
    if(m_states.back().second->isTransparent() && m_states.size() > 1) {
        
        auto it = m_states.end();
        
        while(it != m_states.begin()) {
            
            if(it != m_states.end()) {
                
                if(!it->second->isTransparent()) {
                    break;
                }
                
            }
            
            --it;
            
        }
        
        for(; it != m_states.end(); ++it) {
            m_shared->m_window->getRenderWindow()->setView(it->second->getView());
            it->second->draw();
        }
        
    }
    else {
        m_states.back().second->draw();
    }
    
    
}   //End Draw

void StateManager::update(sf::Time& time) {
    
    if(m_states.empty()) {
        return;
    }
    
    if(m_states.back().second->isTranscendent() && m_states.size() > 1) {
        
        auto it = m_states.end();
        while(it != m_states.begin()) {
            if(it != m_states.end()) {
                if(!it->second->isTranscendent()) {
                    break;
                }
            }
            --it;
        }
        for(; it != m_states.end(); ++it) {
            it->second->update(time);
        }
        
    }
    else {
        m_states.back().second->update(time);
    }
}   //End update

SharedContext* StateManager::getContext() {
    return m_shared;
}

bool StateManager::hasState(const StateType& type) {
    for(auto it = m_states.begin(); it != m_states.end(); ++it) {
        if(it->first == type) {
            auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
            if(removed == m_toRemove.end() ) {
                return true;
            }
            return false;
        }
    }
    return false;
}

void StateManager::remove(const StateType& type) {
    m_toRemove.push_back(type);
}

void StateManager::processRequests() {
    while(m_toRemove.begin() != m_toRemove.end()) {
        removeState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}

void StateManager::switchTo(const StateType& type) {
    
    m_shared->m_eventManager->setCurrentState(type);
    
    for(auto it = m_states.begin(); it != m_states.end(); ++it) {
        if(it->first == type) {
            m_states.back().second->deActivate();
            
            StateType tmpType = it->first;
            IBaseState* tmpState = it->second;
            m_states.erase(it);
            m_states.emplace_back(tmpType, tmpState);
            tmpState->activate();
            
            m_shared->m_window->getRenderWindow()->setView(tmpState->getView());
            
            return;
        }
    }
    //The state "type" not found
    if(!m_states.empty()) {
        m_states.back().second->deActivate();
    }
    createState(type);
    m_states.back().second->activate();
    
    m_shared->m_window->getRenderWindow()->setView(m_states.back().second->getView());
    
    
}

void StateManager::createState(const StateType& type) {
    
    auto newState = m_stateFactory.find(type);
    
    if(newState == m_stateFactory.end()) {
        return;
    }
    IBaseState* state = newState->second();
    
    state->m_view = m_shared->m_window->getRenderWindow()->getDefaultView();
    
    m_states.emplace_back(type, state);
    state->onCreate();
    
}

void StateManager::removeState(const StateType& type) {
    
    for(auto it = m_states.begin(); it != m_states.end(); ++it) {
        if(it->first == type) {
            it->second->onDestroy();
            delete it->second;
            m_states.erase(it);
            return;
        }
    }
    
}
