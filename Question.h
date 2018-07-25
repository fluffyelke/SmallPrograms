/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Question.h
 * Author: default
 *
 * Created on June 13, 2018, 2:56 PM
 */

#ifndef QUESTION_H
#define QUESTION_H

#include "AnimatedTile.h"
//#include "EntityManager.h"


class Question : public AnimatedTile {
public:
    Question(EntityManager* l_manager);
    virtual ~Question();
    
    void onEntityCollision(EntityBase* collider, bool attack) override;

private:

};

#endif /* QUESTION_H */

