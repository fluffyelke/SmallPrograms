/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateGameOver.h
 * Author: default
 *
 * Created on May 14, 2018, 4:04 PM
 */
#pragma once
#ifndef STATEGAMEOVER_H
#define STATEGAMEOVER_H

#include "IBaseState.h"


class StateGameOver : public IBaseState{
public:
    StateGameOver(StateManager* stateMgr);
    virtual ~StateGameOver();
    
    void activate() override;
    void deActivate() override;
    void onCreate() override;
    void onDestroy() override;
    void draw() override;
    void update(const sf::Time& time) override;

private:

};

#endif /* STATEGAMEOVER_H */

