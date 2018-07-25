/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimDirectional.h
 * Author: default
 *
 * Created on May 15, 2018, 9:54 AM
 */

#ifndef ANIMDIRECTIONAL_H
#define ANIMDIRECTIONAL_H

#include "AnimBase.h"
#include "Directions.h"

class AnimDirectional : public AnimBase{
protected:
    void cropSprite() override;
    void frameStep() override;
    void readIn(std::stringstream& stream) override;
};

#endif /* ANIMDIRECTIONAL_H */

