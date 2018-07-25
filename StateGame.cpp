/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGame.cpp
 * Author: default
 * 
 * Created on May 14, 2018, 4:04 PM
 */

#include "StateGame.h"
#include "StateManager.h"
#include "mystuff/RealTime.h"
#include "mystuff/GameTime.h"

StateGame::StateGame(StateManager* stateMgr) 
    : IBaseState(stateMgr) {
}

StateGame::~StateGame() {
}

void StateGame::onCreate() {
    
    EventManager* eventMgr = m_stateManager->getContext()->m_eventManager;
    
    eventMgr->addCallback(StateType::GAME, "Key_P", &StateGame::pause, this);
    
    sf::Vector2u size = m_stateManager->getContext()->m_window->getWindowSize();
    m_view.setSize(size.x, size.y);
    m_view.setCenter(size.x / 2, size.y / 2);
//    m_view.zoom(0.6f);
    m_stateManager->getContext()->m_window->getRenderWindow()->setView(m_view);
    
    m_gameMap = new Map(m_stateManager->getContext(), this);
    m_gameMap->loadMap("resources/media/Maps/world1-1");
    
    m_timeObjects.push_back(new MyTime::RealTime);
    m_timeObjects.push_back(new MyTime::GameTime);
}

void StateGame::onDestroy() {
    m_stateManager->getContext()->m_eventManager->removeCallback(StateType::GAME, "Key_P");
    
    delete m_gameMap;
    m_gameMap = nullptr;
    
    if(m_timeObjects.empty()) {
        return;
    }
    for(auto& it : m_timeObjects) {
        delete it;
        m_timeObjects.pop_back();
    }
}

void StateGame::activate() {

}

void StateGame::deActivate() {

}


void StateGame::draw() {
    m_gameMap->draw();
    m_stateManager->getContext()->m_entityManager->draw();
    
    if(m_timeObjects.empty()) {
        return;
    }
    for(auto& it : m_timeObjects) {
        it->draw(m_stateManager->getContext()->m_window->getRenderWindow());
    }
}

void StateGame::update(const sf::Time& time) {
    SharedContext* context = m_stateManager->getContext();
    EntityBase* player = context->m_entityManager->find("Player");

    if (!player) {
        std::cout << "Respawning player..." << std::endl;
        context->m_entityManager->add(EntityType::Player, "Player");
        player = context->m_entityManager->find("Player");
        player->setPosition(m_gameMap->getPlayerStart());
    }
    else {
        m_view.setCenter(player->getPosition());
        context->m_window->getRenderWindow()->setView(m_view);
    }

    sf::FloatRect viewSpace = context->m_window->getViewSpace();
    if (viewSpace.left <= 0) {
        if(viewSpace.top + viewSpace.height >= 224) {
            m_view.setCenter(viewSpace.width / 2, m_view.getCenter().y / 1.7);
        }
        else {
            m_view.setCenter(viewSpace.width / 2, m_view.getCenter().y);
        }
        context->m_window->getRenderWindow()->setView(m_view);
    }
    else if(viewSpace.top + viewSpace.height >= m_gameMap->getMapSize().y + 1) {
        m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y / 1.7);
        context->m_window->getRenderWindow()->setView(m_view);
    }
    else if (viewSpace.left + viewSpace.width > (m_gameMap->getMapSize().x + 1) * Sheet::TILE_SIZE) {
        m_view.setCenter(((m_gameMap->getMapSize().x + 1) * Sheet::TILE_SIZE) - (viewSpace.width / 2), m_view.getCenter().y);
        context->m_window->getRenderWindow()->setView(m_view);
    }

    m_gameMap->update(time.asSeconds());
    m_stateManager->getContext()->m_entityManager->update(time.asSeconds());
    if(!m_timeObjects.empty()) {
        for(auto& it : m_timeObjects) {
            it->update(time.asSeconds());
        }
    }
}

void StateGame::pause(EventDetails* details) {
    m_stateManager->switchTo(StateType::PAUSED);
}
