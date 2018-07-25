/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: default
 * 
 * Created on May 14, 2018, 10:18 AM
 */

#include "Game.h"

Game::Game() 
    : m_window{"SNES Super Mario Bros", sf::Vector2u{256, 224}},
      m_stateManager{&m_context}, 
      m_entityManager{&m_context, 100} {
          
        m_clock.restart();
        srand(time(NULL));
        
        m_context.m_window = &m_window;
        m_context.m_eventManager = m_window.getEventManager();
        m_context.m_textureManager = &m_textureManager;
        m_context.m_entityManager = &m_entityManager;
        
        m_stateManager.switchTo(StateType::MAIN_MENU);
}


Game::~Game() {
}

void Game::update() {
    m_window.update();
    m_stateManager.update(m_elapsed);
}

void Game::render() {
    m_window.beginDraw();
    
    //Render here
    m_stateManager.draw();
    
    m_window.endDraw();
}

void Game::lateUpdate() {
    m_stateManager.processRequests();
    restartClock();
}

sf::Time Game::getElapsed() {
    return m_clock.getElapsedTime();
}

void Game::restartClock() {
    m_elapsed = m_clock.restart();
}

Window* Game::getWindow() {
    return &m_window;
}
