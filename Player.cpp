/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: default
 * 
 * Created on May 17, 2018, 2:41 PM
 */

#include "Player.h"
#include "EntityManager.h"
#include "StateManager.h"

Player::Player(EntityManager* manager) 
    : Character{manager}  {
    load("resources/media/Characters/Mario.char");
    m_type = EntityType::Player;
    
    EventManager* events = m_entityManager->getContext()->m_eventManager;
    events->addCallback<Player>(StateType::GAME, "Player_MoveLeft", &Player::react, this);
    events->addCallback<Player>(StateType::GAME, "Player_MoveRight", &Player::react, this);
    events->addCallback<Player>(StateType::GAME, "Player_Jump", &Player::react, this);
}


Player::~Player() {
    m_entityManager->getContext()->m_eventManager->removeCallback(StateType::GAME, "Player_MoveLeft");
    m_entityManager->getContext()->m_eventManager->removeCallback(StateType::GAME, "Player_MoveRight");
    m_entityManager->getContext()->m_eventManager->removeCallback(StateType::GAME, "Player_Jump");
}

void Player::react(EventDetails* details) {
    if(details->m_name == "Player_MoveLeft") {
        Character::move(Direction::Left);
    }
    else if(details->m_name == "Player_MoveRight") {
        Character::move(Direction::Right);
    }
    else if(details->m_name == "Player_Jump") {
        Character::jump();
    }
}

void Player::onEntityCollision(EntityBase* collider, bool attack) {
    Character* entity = (Character*)collider;
    std::cout << collider->getName() << std::endl;
    if(m_state == EntityState::Dying) {
        return;
    }
    else if(collider->getType() != EntityType::Question) {
        if(m_position.y + Sheet::TILE_SIZE >= entity->getPosition().y) {
            std::cout << "11111111111111\n";
            m_position.y = entity->getPosition().y - Sheet::TILE_SIZE;
//            EntityBase::move(0, 0);
//            m_spriteSheet.setDirection(Direction::Left);
        }
        else {
            accelerate(0, -m_speed.y);
            std::cout << "22222222222222\n";
//            EntityBase::move(0, -15);
//            m_spriteSheet.setDirection(Direction::Right);
        }
    }  
}   
