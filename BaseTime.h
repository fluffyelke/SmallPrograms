/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseTime.h
 * Author: default
 *
 * Created on June 12, 2018, 2:51 PM
 */

#ifndef BASETIME_H
#define BASETIME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

namespace MyTime {
    class BaseTime {
    public:
        BaseTime();
        virtual ~BaseTime();

        virtual void draw(sf::RenderWindow* l_window);
        virtual void update(float l_dT);
        
        void setTimePos(const sf::Vector2f& pos);
        float getTimeXPos();
    protected:
        int m_seconds;
        int m_minutes;
        int m_hours;

        float m_elapsed;

        sf::Font m_font;
        sf::Text m_text;
        
        sf::Vector2f m_timerPos;
    private:
        void setZeros();
    };
}

#endif /* BASETIME_H */

