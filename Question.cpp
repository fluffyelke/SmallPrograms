/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Question.cpp
 * Author: default
 * 
 * Created on June 13, 2018, 2:56 PM
 */

#include "Question.h"
#include "EntityManager.h"

Question::Question(EntityManager* l_manager) 
    : AnimatedTile(l_manager)  {
}


Question::~Question() {
}

void Question::onEntityCollision(EntityBase* collider, bool attack) {
    Character* entity = (Character*) collider;
    if(collider->getType() == EntityType::Player) {
        std::cout << "55555555555555\n";
//        if(getState() != EntityState::Dying) {
////            setState(EntityState::Dying);
//            hitAnimation();
//        }
    }
}
