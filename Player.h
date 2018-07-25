/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: default
 *
 * Created on May 17, 2018, 2:41 PM
 */
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "EventManager.h"

class Player : public Character {
public:
    Player(EntityManager* manager);
    virtual ~Player();
    
    void onEntityCollision(EntityBase* collider, bool attack) override;
    void react(EventDetails* details);

private:

};

#endif /* PLAYER_H */

