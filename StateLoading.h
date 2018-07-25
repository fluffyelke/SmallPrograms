/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateLoading.h
 * Author: default
 *
 * Created on May 14, 2018, 4:04 PM
 */
#pragma once
#ifndef STATELOADING_H
#define STATELOADING_H

#include "IBaseState.h"


class StateLoading : public IBaseState {
public:
    StateLoading(StateManager* stateMgr);
    virtual ~StateLoading();
    
    void onCreate() override;
    void onDestroy() override;
    void activate() override;
    void deActivate() override;
    void draw() override;
    void update(const sf::Time& time) override;

private:

};

#endif /* STATELOADING_H */

