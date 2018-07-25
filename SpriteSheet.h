/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpriteSheet.h
 * Author: default
 *
 * Created on May 15, 2018, 9:57 AM
 */

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "AnimDirectional.h"
#include "TextureManager.h"

using Animations = std::unordered_map<std::string, AnimBase*>;

class SpriteSheet {
public:
    SpriteSheet(TextureManager* textureMgr);
    virtual ~SpriteSheet();
    
    void cropSprite(const sf::IntRect& rect);
    sf::Vector2i getSpriteSize() const;
    sf::Vector2f getSpritePos() const;
    
    void setSpriteSize(const sf::Vector2i& size);
    void setSpritePos(const sf::Vector2f& pos);
    
    void setDirection(const Direction& dir);
    Direction getDirection() const;
    
    bool loadSheet(const std::string& file);
    void releaseSheet();
    
    AnimBase* getCurrentAnim();
    bool setAnimation(const std::string& name, const bool& play = false, const bool& loop = false);
    
    void update(const float& dt);
    void draw(sf::RenderWindow* window);
    
private:
    std::string m_texture;
    sf::Sprite m_sprite;
    sf::Vector2i m_spriteSize;
    sf::Vector2f m_spriteScale;
    Direction m_direction;
    
    std::string m_animType;
    Animations m_animations;
    AnimBase* m_animationCurrent;
    
    TextureManager* m_textureManager;
};

#endif /* SPRITESHEET_H */

