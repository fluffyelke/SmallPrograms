/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: default
 *
 * Created on May 14, 2018, 10:18 AM
 */

#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "graphics/TextureManager.h"
#include "EntityManager.h"


class Game {
public:
    Game();
    ~Game();
    
    void update();
    void render();
    void lateUpdate();
    
    sf::Time getElapsed();
    Window* getWindow();
    
private:
    
    void restartClock();
    
    sf::Clock m_clock;
    sf::Time m_elapsed;
    SharedContext m_context;
    Window m_window;
    EntityManager m_entityManager;
    TextureManager m_textureManager;
    StateManager m_stateManager;
    
};

#endif /* GAME_H */

