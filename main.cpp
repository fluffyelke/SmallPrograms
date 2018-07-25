/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on May 14, 2018, 9:17 AM
 */

#include <cstdlib>

#include "Game.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Game game;
    while(!game.getWindow()->isDone()) {
        game.update();
        game.render();
        game.lateUpdate();
    }
    return 0;
}

