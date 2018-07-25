/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimatedTile.cpp
 * Author: default
 * 
 * Created on June 13, 2018, 2:47 PM
 */

#include "AnimatedTile.h"
#include "EntityManager.h"
#include "StateManager.h"

AnimatedTile::AnimatedTile(EntityManager* l_manager) 
    : EntityBase(l_manager),
      m_spriteSheet{m_entityManager->getContext()->m_textureManager},
      m_pauseAnim{0},
      m_jumpVelocity{30} {
    m_name = "AnimatedTile";
    m_maxVelocity.x = 0;
    m_maxVelocity.y = 50;
}

AnimatedTile::~AnimatedTile() {
}

void AnimatedTile::load(const std::string& l_name) {
    std::ifstream file;
    file.open(l_name);
    if(!file.is_open()) {
        std::cerr << "! Error loading AnimatedTile: " << l_name << std::endl;
        return;
    }
    
    std::string line;
    while(std::getline(file, line)) {
        std::stringstream keystream{line};
        if(line.at(0) == '|'){
            continue;
        }
        std::string type;
        keystream >> type;
        if(type == "Name") {
            keystream >> m_name;
        }
        else if(type == "Spritesheet") {
            std::string path;
            keystream >> path;
            m_spriteSheet.loadSheet("resources/media/SpriteSheet/" + path);
        }
        else if(type == "BoundingBox") {
            sf::Vector2f box;
            keystream >> box.x >> box.y;
            setSize(box.x , box.y);
        }
        else {
            std::cout << "! Unknown types in AnimateTile file: " << type << std::endl;
        }
    }
    file.close();
}

void AnimatedTile::animate() {
    EntityState state = getState();
    
    if(state == EntityState::Jumping && m_spriteSheet.getCurrentAnim()->getName() != "Jumping") {
        std::cout << "333333333333\n";
        m_spriteSheet.setAnimation("Jumping", true, false);
    }
    else if(state == EntityState::Idle && m_spriteSheet.getCurrentAnim()->getName() != "Idle") {
        m_spriteSheet.setAnimation("Idle", true, true);
    }
    else if(state == EntityState::Dying && m_spriteSheet.getCurrentAnim()->getName() != "Dying") {
        m_spriteSheet.setAnimation("Dying", true, false);
    }
    
}

void AnimatedTile::update(float dt) {
//    EntityBase::update(dt);
//    std::cout << abs(m_velocity.y) << std::endl;
    if(getState() != EntityState::Dying) {
        if(abs(m_velocity.y >= 0.001f)) {
//            std::cout << "44444444444\n";
            setState(EntityState::Jumping);
        }
        else {
//            std::cout << "555555555555\n";
            setState(EntityState::Idle);  
        }
    }
    else {
        setState(EntityState::Dying);
        m_spriteSheet.getCurrentAnim()->play();
    }
    if(!m_spriteSheet.getCurrentAnim()->isPlaying()) {
        m_pauseAnim += dt;
        if(m_pauseAnim > 0.7) {
            m_spriteSheet.getCurrentAnim()->play();
            m_pauseAnim = 0;
        }
    }
    animate();
    m_spriteSheet.update(dt);
    m_spriteSheet.setSpritePos(m_position);
}

void AnimatedTile::draw(sf::RenderWindow* window) {
    m_spriteSheet.draw(window);
}

void AnimatedTile::hitAnimation() {
//    if(getState() == EntityState::Dying || getState() == EntityState::Jumping) {
//        return;
//    }
    setState(EntityState::Jumping);
//    std::cout << "2222222222\n";
    addVelocity(0, -m_jumpVelocity);
    std::cout << -m_jumpVelocity << std::endl;
}
