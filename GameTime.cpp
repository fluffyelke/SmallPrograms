/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameTime.cpp
 * Author: default
 * 
 * Created on June 12, 2018, 3:02 PM
 */

#include "GameTime.h"

namespace MyTime {
    GameTime::GameTime()
        : BaseTime() {
              m_text.setPosition(sf::Vector2f{150, 20});
              m_text.setString("00:00:00");
    }

    GameTime::~GameTime() {
    }

    void GameTime::draw(sf::RenderWindow* l_window) {
        BaseTime::draw(l_window);
    }

    void GameTime::update(float l_dT) {
        BaseTime::update(l_dT);
        m_elapsed += l_dT;
        if(m_elapsed > 1) {
            setTime();
            m_elapsed = 0;
        }
    }

    void GameTime::setTime() {
        if(m_seconds < 59) {
            m_seconds += 1;
        }
        else {
            m_seconds = 0;
            if(m_minutes < 59) {
                m_minutes += 1;
            }
            else {
                m_minutes = 0;
                m_hours += 1;
            }
        }
    }

}

