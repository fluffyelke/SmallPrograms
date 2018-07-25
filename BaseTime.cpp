/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseTime.cpp
 * Author: default
 * 
 * Created on June 12, 2018, 2:51 PM
 */

#include "BaseTime.h"
#include <iostream>

namespace MyTime {
    BaseTime::BaseTime()
        : m_seconds{0},
          m_minutes{0},
          m_hours{0},
          m_elapsed{0}{
              
              m_font.loadFromFile("resources/media/Fonts/fallout.ttf");
              m_text.setFont(m_font);
              m_text.setFillColor(sf::Color::Green);
              m_text.setCharacterSize(18);
              m_timerPos.x = 20;
              m_timerPos.y = 20;
              m_text.setPosition(m_timerPos);
              setZeros();
    }

    BaseTime::~BaseTime() {
    }
    
    void BaseTime::draw(sf::RenderWindow* l_window) {
        l_window->draw(m_text);
    }

    void BaseTime::update(float l_dT) {
        setZeros();
    }

    void BaseTime::setZeros() {
        if(m_hours < 10) {
            if(m_minutes < 10) {
                if(m_seconds < 10) {
                    m_text.setString("0" + std::to_string(m_hours) + ":0" + std::to_string(m_minutes) + ":0" + std::to_string(m_seconds));
                }
                else {
                    m_text.setString("0" + std::to_string(m_hours) + ":0" + std::to_string(m_minutes) + ":" + std::to_string(m_seconds));
                }
            }
            else if(m_seconds < 10) {
                m_text.setString("0" + std::to_string(m_hours) + ":" + std::to_string(m_minutes) + ":0" + std::to_string(m_seconds));
            }
        }
        else if(m_minutes < 10){
            if(m_seconds < 10 ) {
                m_text.setString(std::to_string(m_hours) + ":0" + std::to_string(m_minutes) + ":0" + std::to_string(m_seconds));
            }
            else {
                m_text.setString(std::to_string(m_hours) + ":0" + std::to_string(m_minutes) + ":" + std::to_string(m_seconds));
            }
        }
        else if(m_seconds < 10) {
            m_text.setString(std::to_string(m_hours) + ":" + std::to_string(m_minutes) + ":0" + std::to_string(m_seconds));
        }
        else {
            m_text.setString(std::to_string(m_hours) + ":" + std::to_string(m_minutes) + ":" + std::to_string(m_seconds));
        }
    }
}

