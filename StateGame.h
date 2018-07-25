/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGame.h
 * Author: default
 *
 * Created on May 14, 2018, 4:04 PM
 */
#pragma once
#ifndef STATEGAME_H
#define STATEGAME_H

#include "IBaseState.h"
#include "Map.h"
#include "EventManager.h"
#include "mystuff/BaseTime.h"

class StateGame : public IBaseState{
public:
    StateGame(StateManager* stateMgr);
    virtual ~StateGame();
    
    void onCreate() override;
    void onDestroy() override;
    
    void activate() override;
    void deActivate() override;
    
    void draw() override;
    void update(const sf::Time& time) override;
    
    void pause(EventDetails* details);
    
private:
    Map* m_gameMap;
    std::vector<MyTime::BaseTime*> m_timeObjects;
};

#endif /* STATEGAME_H */

