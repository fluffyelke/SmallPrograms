/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimatedTile.h
 * Author: default
 *
 * Created on June 13, 2018, 2:47 PM
 */

#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H

#include "EntityBase.h"
#include "graphics/SpriteSheet.h"


class AnimatedTile : public EntityBase {
    friend class EntityManager;
public:
    AnimatedTile(EntityManager* l_manager);
    virtual ~AnimatedTile();
    
    void load(const std::string& l_name);
    void onEntityCollision(EntityBase* collider, bool attack) = 0;
    void draw(sf::RenderWindow* window) override;
    void update(float dt) override;

    void hitAnimation();
private:
    void animate();
    float m_pauseAnim;
    float m_jumpVelocity;
    SpriteSheet m_spriteSheet;
};

#endif /* ANIMATEDTILE_H */

