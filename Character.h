/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: default
 *
 * Created on May 17, 2018, 1:51 PM
 */

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityBase.h"
#include "graphics/SpriteSheet.h"

class Character : public EntityBase{
    friend class EntityManager;
public:
    Character(EntityManager* entMgr);
    virtual ~Character();
    
    void move(const Direction& dir);
    void jump();
    void attack();
    void getHurt(const int& damage);
    void load(const std::string& path);
    
    virtual void onEntityCollision(EntityBase* collider, bool attack) = 0;
    virtual void update(float dt);
    
    void draw(sf::RenderWindow* window);
    
protected:
    void updateAttackAABB();
    void animate();
    SpriteSheet m_spriteSheet;
    
    float m_jumpVelocity;
    int m_hitPoints;
    sf::FloatRect m_attackAABB;
    sf::Vector2f m_attackAABBoffset;
};

#endif /* CHARACTER_H */

