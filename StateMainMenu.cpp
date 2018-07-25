/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateMainMenu.cpp
 * Author: default
 * 
 * Created on May 14, 2018, 2:51 PM
 */

#include "StateMainMenu.h"
#include "StateManager.h"
#include <iostream>

StateMainMenu::StateMainMenu(StateManager* stateMgr)
    : IBaseState(stateMgr) {
    
    
    
}

StateMainMenu::~StateMainMenu() {
}

void StateMainMenu::onCreate() {
    
    sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize(); 
    
    m_playerOne = true;
    
    TextureManager* textureMgr = m_stateManager->getContext()->m_textureManager;
    textureMgr->requireResource("MainMenu");
    m_introSprite.setTexture(*textureMgr->getResource("MainMenu"));
    m_introSprite.setTextureRect(sf::IntRect{2, 60, 175, 88});
    m_introSprite.setOrigin(m_introSprite.getTextureRect().height / 2.f, m_introSprite.getTextureRect().width / 2.f);
    m_introSprite.setScale(1, 1);
    m_introSprite.setPosition(windowSize.x / 2.f - 80, windowSize.y / 2.f);
    
    textureMgr->requireResource("MainMenuBG");
    m_background.setTexture(*textureMgr->getResource("MainMenuBG"));
    m_background.setPosition(0, 0);
    
    m_mushroomSprite.setTexture(*textureMgr->getResource("MainMenu"));
    m_mushroomSprite.setTextureRect(sf::IntRect{0, 154, 13, 13});
    m_mushroomSprite.setOrigin(m_mushroomSprite.getTextureRect().height / 2, m_mushroomSprite.getTextureRect().width / 2);
    m_mushroomSprite.setScale(1, 1);
    m_mushroomSprite.setPosition(windowSize.x / 2.f - 80, windowSize.y / 2.f + 40);

    m_stateManager->getContext()->m_eventManager->addCallback(StateType::MAIN_MENU, "MainMenu_Select", &StateMainMenu::selectOption, this);
    m_stateManager->getContext()->m_eventManager->addCallback(StateType::MAIN_MENU, "MainMenu_DownArrow", &StateMainMenu::moveMushroom, this);
    m_stateManager->getContext()->m_eventManager->addCallback(StateType::MAIN_MENU, "MainMenu_UpArrow", &StateMainMenu::moveMushroom, this);
}

void StateMainMenu::onDestroy() {
    m_stateManager->getContext()->m_textureManager->releaseResource("MainMenu");
    m_stateManager->getContext()->m_textureManager->releaseResource("MainMenuBG");
    
    m_stateManager->getContext()->m_eventManager->removeCallback(StateType::MAIN_MENU, "MainMenu_Select");
    m_stateManager->getContext()->m_eventManager->removeCallback(StateType::MAIN_MENU, "MainMenu_DownArrow");
    m_stateManager->getContext()->m_eventManager->removeCallback(StateType::MAIN_MENU, "MainMenu_UpArrow");
}

void StateMainMenu::activate() {

}

void StateMainMenu::deActivate() {

}

void StateMainMenu::draw() {
    sf::RenderWindow* window = m_stateManager->getContext()->m_window->getRenderWindow();
    window->draw(m_background);
    window->draw(m_introSprite);
    window->draw(m_mushroomSprite);

}

void StateMainMenu::update(const sf::Time& time) {

}

void StateMainMenu::moveMushroom(EventDetails* details) {
    m_playerOne = !m_playerOne;
    if(m_playerOne) {
        m_mushroomSprite.setPosition(240, 320);
        
    }
    else {
        m_mushroomSprite.setPosition(240, 360);
    }
}


//Class Functions
void StateMainMenu::selectOption(EventDetails* details) {
    if(m_playerOne) {
        m_stateManager->switchTo(StateType::GAME);
    }
    else {
        
    }
}

