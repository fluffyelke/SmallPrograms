/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameTime.h
 * Author: default
 *
 * Created on June 12, 2018, 3:02 PM
 */

#ifndef GAMETIME_H
#define GAMETIME_H

#include "BaseTime.h"


namespace MyTime {
    class GameTime : public BaseTime {
    public:
        GameTime();
        virtual ~GameTime();
        
        void draw(sf::RenderWindow* l_window) override;
        void update(float l_dT) override;

    private:
        void setTime();
    };
}

#endif /* GAMETIME_H */

