/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RealTime.h
 * Author: default
 *
 * Created on June 12, 2018, 2:58 PM
 */

#ifndef REALTIME_H
#define REALTIME_H

#include "BaseTime.h"

namespace MyTime {
    class RealTime : public BaseTime{
    public:
        RealTime();
        virtual ~RealTime();

        void update(float l_dT) override;
        void draw(sf::RenderWindow* l_window) override;

    private:

    };
}

#endif /* REALTIME_H */

