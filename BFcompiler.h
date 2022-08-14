//
// Created by mrybs on 13.08.22.
//

#include<iostream>
#include<string>
#include<vector>

#ifndef BRAINFUCK_BFCOMPILER_H
#define BRAINFUCK_BFCOMPILER_H
#pragma once


struct BFcompiler {
    std::string simplification(std::string code);
    std::string compile(std::string code);
};


#endif//BRAINFUCK_BFCOMPILER_H
