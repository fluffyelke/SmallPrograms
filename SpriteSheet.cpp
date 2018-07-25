/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpriteSheet.cpp
 * Author: default
 * 
 * Created on May 15, 2018, 9:57 AM
 */

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(TextureManager* textureMgr) 
    : m_textureManager{textureMgr}, 
      m_animationCurrent{nullptr},
      m_spriteScale{1.f, 1.f},
      m_direction{Direction::Right} {
}


SpriteSheet::~SpriteSheet() {
    releaseSheet();
}

void SpriteSheet::releaseSheet() {
    m_textureManager->releaseResource(m_texture);
    m_animationCurrent = nullptr;
    while(m_animations.begin() != m_animations.end()) {
        delete m_animations.begin()->second;
        m_animations.erase(m_animations.begin());
    }
}

sf::Vector2i SpriteSheet::getSpriteSize() const {
    return m_spriteSize;
}

AnimBase* SpriteSheet::getCurrentAnim() {
    return m_animationCurrent;
}

Direction SpriteSheet::getDirection() const {
    return m_direction;
}

sf::Vector2f SpriteSheet::getSpritePos() const {
    return m_sprite.getPosition();
}

void SpriteSheet::setSpriteSize(const sf::Vector2i& size) {
    m_spriteSize = size;
    m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y / 2);
}

void SpriteSheet::setSpritePos(const sf::Vector2f& pos) {
    m_sprite.setPosition(pos);
}

void SpriteSheet::setDirection(const Direction& dir) {
    if(dir == m_direction) {
        return;
    }
    m_direction = dir;
    if(m_direction == Direction::Right) {
        m_sprite.setScale(1.0f, 1.0f);
    }
    else {
        m_sprite.setScale(-1.0f, 1.0f);
    }
    
    m_animationCurrent->cropSprite();
}

void SpriteSheet::cropSprite(const sf::IntRect& rect) {
    m_sprite.setTextureRect(rect);
}

bool SpriteSheet::loadSheet(const std::string& file) {
    std::ifstream sheet;
    sheet.open(file);
    
    if(sheet.is_open()) {
        releaseSheet();
        std::string line;
        while(std::getline(sheet, line)){
            if(line[0] == '|') {
                continue;
            }
            std::stringstream keystream{line};
            std::string type;
            keystream >> type;
            if(type == "Texture") {
                if(m_texture != "") {
                    std::cerr << "! Duplicate textures entries in: " << file << std::endl;
                    continue;
                }
                std::string texture;
                keystream >> texture;
                if(!m_textureManager->requireResource(texture)) {
                    std::cerr << "! Could not set up texture: " << texture << std::endl;
                    continue;
                }
                m_texture = texture;
                m_sprite.setTexture(*m_textureManager->getResource(m_texture));
            }
            else if(type == "Size") {
                keystream >> m_spriteSize.x >> m_spriteSize.y;
                setSpriteSize(m_spriteSize);
            }
            else if(type == "Scale") {
                keystream >> m_spriteScale.x >> m_spriteScale.y;
                m_sprite.setScale(m_spriteScale);
            }
            else if(type == "AnimationType") {
                keystream >> m_animType;
            }
            else if(type == "Animation") {
                std::string name;
                keystream >> name;
                if(m_animations.find(name) != m_animations.end()) {
                    std::cerr << "! Duplicate animation(" << name << ") in: " << file << std::endl;
                    continue;
                }
                AnimBase* anim = nullptr;
                if(m_animType == "Directional") {
                    anim = new AnimDirectional();
                }
                else {
                    std::cerr << "! Unknown Animation type: " << m_animType << std::endl;
                    continue;
                }
                keystream >> *anim;
                anim->setSpriteSheet(this);
                anim->setName(name);
                anim->reset();
                
                m_animations.emplace(name, anim);
                
                if(m_animationCurrent) {
                    continue;
                }
                m_animationCurrent = anim;
                m_animationCurrent->play(); 
            }
        }
        sheet.close();
        return true;
    }
    std::cerr << "! Failed loading spritesheet: " << file << std::endl;
    return false;
}

bool SpriteSheet::setAnimation(const std::string& name, const bool& play, const bool& loop) {
    auto it = m_animations.find(name);
    if(it == m_animations.end()) {
        return false;
    }
    if(it->second == m_animationCurrent) {
        return false;
    }
    if(m_animationCurrent) {
        m_animationCurrent->stop();
    }
    m_animationCurrent = it->second;
    m_animationCurrent->setLooping(loop);
    
    if(play) {
        m_animationCurrent->play();
    }
    m_animationCurrent->cropSprite();
    return true;
}

void SpriteSheet::update(const float& dt) {
    m_animationCurrent->update(dt);
}

void SpriteSheet::draw(sf::RenderWindow* window) {
    window->draw(m_sprite);
}

