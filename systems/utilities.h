#ifndef UTILITIES_H
#define UTILITIES_H
///Inclusions
#include <iostream>
#include <cstdlib>
#include <thread> ///If you don't use mutithreading than delete this inclusion
#include <chrono>
#include "bcn_namespace.h"


///Prototyping
void new_game();
int main_menu();
int gameover_check();
int glow_cave_hidden_entrance();
int glow_cave_left();
int glow_cave_right();

///CPP System inclusions
#include "systems.cpp"
#include "battles.cpp"
#include "random_encounter.cpp"
///CPP inclusions | Keep below Prototyping
#include "../dungeon/glow_cave.cpp"


#endif
