//
// Created by mrybs on 13.08.22.
//

#include<iostream>
#include<string>
#include<vector>
#include <unistd.h>
#include "termios.h"

#ifndef BRAINFUCK_BFINTERPRETER_H
#define BRAINFUCK_BFINTERPRETER_H
#pragma once

struct BFinterpreter {
    char getch();
    std::string simplification(std::string code);
    void interpretation(std::string code);
};


#endif//BRAINFUCK_BFINTERPRETER_H
