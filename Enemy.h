/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.h
 * Author: default
 *
 * Created on May 22, 2018, 2:21 PM
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"


class Enemy : public Character{
public:
    Enemy(EntityManager* entityMgr);
    virtual ~Enemy();
    void onEntityCollision(EntityBase* collider, bool attack) override;
    void update(float dt) override;

private:
    sf::Vector2f m_destination;
    bool m_hasDestination;
};

#endif /* ENEMY_H */

