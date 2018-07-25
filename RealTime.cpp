/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RealTime.cpp
 * Author: default
 * 
 * Created on June 12, 2018, 2:58 PM
 */

#include "RealTime.h"
#include <iostream>
#include <ctime>

namespace MyTime {
    RealTime::RealTime() 
        : BaseTime() {
        
        std::time_t now = std::time(0);
        std::tm *ltm = std::localtime(&now);
        m_hours = ltm->tm_hour;
        m_minutes = ltm->tm_min;
        m_seconds = ltm->tm_sec;
        
    }

    RealTime::~RealTime() {
    }

    void RealTime::draw(sf::RenderWindow* l_window) {
        BaseTime::draw(l_window);
    }

    void RealTime::update(float l_dT) {
        BaseTime::update(l_dT);
        m_elapsed += l_dT;
        if(m_elapsed > 1) {
            std::time_t now = std::time(0);
            std::tm *ltm = std::localtime(&now);
            m_hours = ltm->tm_hour;
            m_minutes = ltm->tm_min;
            m_seconds = ltm->tm_sec;
            m_elapsed = 0;
        }
    }

}

