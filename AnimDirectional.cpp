/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimDirectional.cpp
 * Author: default
 * 
 * Created on May 15, 2018, 9:54 AM
 */

#include <SFML/Graphics/Rect.hpp>

#include "AnimDirectional.h"
#include "SpriteSheet.h"

void AnimDirectional::cropSprite() {
    sf::IntRect rect{m_spriteSheet->getSpriteSize().x * m_frameCurrent, 
        m_spriteSheet->getSpriteSize().y * m_frameRow,
    m_spriteSheet->getSpriteSize().x, m_spriteSheet->getSpriteSize().y};
    m_spriteSheet->cropSprite(rect);
}

void AnimDirectional::frameStep() {
    if(m_frameStart < m_frameEnd) {
        ++m_frameCurrent;
    }
    else {
        --m_frameCurrent;
    }
    
    if(m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd ||
        m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd) {
        if(m_loop) {
            m_frameCurrent = m_frameStart;
            return;
        }
        m_frameCurrent = m_frameStart;
        pause();
    } 
}

void AnimDirectional::readIn(std::stringstream& stream) {
    stream >> m_frameStart >> m_frameEnd >> m_frameRow 
        >> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}
