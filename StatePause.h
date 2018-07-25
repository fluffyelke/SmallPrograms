/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatePause.h
 * Author: default
 *
 * Created on May 14, 2018, 4:04 PM
 */
#pragma once
#ifndef STATEPAUSE_H
#define STATEPAUSE_H

#include "IBaseState.h"


class StatePause : public IBaseState{
public:
    StatePause(StateManager* stateMgr);
    virtual ~StatePause();
    
    void onCreate() override;
    void onDestroy() override;
    
    void activate() override;
    void deActivate() override;
    
    void draw() override;
    void update(const sf::Time& time) override;

private:

};

#endif /* STATEPAUSE_H */

