/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.cpp
 * Author: default
 * 
 * Created on May 22, 2018, 2:21 PM
 */

#include <complex>

#include "Enemy.h"
#include "EntityManager.h"

Enemy::Enemy(EntityManager* entityMgr) 
    : Character(entityMgr),
      m_hasDestination{false} {
    m_type == EntityType::Enemy;
    
}


Enemy::~Enemy() {
}

void Enemy::onEntityCollision(EntityBase* collider, bool attack) {
    Character* entity = (Character*)collider;
    if(collider->getType() == EntityType::Player) {
        entity->getHurt(1);
//        if()
    }
    else if(collider->getType() != EntityType::Enemy) {
        if(m_position.x > entity->getPosition().x) {
            entity->addVelocity(-m_speed.x, 0);
            m_spriteSheet.setDirection(Direction::Left);
        }
        else {
            entity->addVelocity(m_speed.x, 0);
            m_spriteSheet.setDirection(Direction::Right);
        }
    }  
}

void Enemy::update(float dt) {
    Character::update(dt);
    
    if(m_hasDestination) {
        if(std::abs(m_destination.x - m_position.x) < 16) {
            m_hasDestination = false;
            return;
        }
        if(m_destination.x - m_position.x > 0) {
            move(Direction::Right);
        }
        else {
            move(Direction::Left);
        }
        if(m_collidingOnX) {
            m_hasDestination = false;
            return;
        }
    }
    
    EntityBase* player = m_entityManager->find("Player");
    int newX = m_position.x - player->getPosition().x; 

    m_destination.x = m_position.x - newX;
    if(m_destination.x < 0) {
        m_destination.x = 0;
    }
    m_hasDestination = true;
}
