/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatePause.cpp
 * Author: default
 * 
 * Created on May 14, 2018, 4:04 PM
 */

#include "StatePause.h"
#include "StateManager.h"

StatePause::StatePause(StateManager* stateMgr) 
    : IBaseState(stateMgr) {
}

StatePause::~StatePause() {
}

void StatePause::onCreate() {

}

void StatePause::onDestroy() {

}

void StatePause::activate() {

}

void StatePause::deActivate() {

}

void StatePause::draw() {

}

void StatePause::update(const sf::Time& time) {

}
