/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateMainMenu.h
 * Author: default
 *
 * Created on May 14, 2018, 2:51 PM
 */
#pragma once
#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#include "EventManager.h"
#include "IBaseState.h"

class StateMainMenu : public IBaseState{
public:
    StateMainMenu(StateManager* stateMgr);
    virtual ~StateMainMenu();
    
    void onCreate() override;
    void onDestroy() override;
    
    void activate() override;
    void deActivate() override;

    void update(const sf::Time& time) override;
    void draw() override;
    
    void selectOption(EventDetails* details);
    void moveMushroom(EventDetails* details);
    
private:
    sf::Sprite m_introSprite;
    sf::Sprite m_mushroomSprite;
    sf::Sprite m_background;
    int m_playerOne;
};

#endif /* STATEMAINMENU_H */

