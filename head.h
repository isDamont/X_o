//
// Created by isDamont on 31.05.2022.
//

#ifndef X_O_HEAD_H
#define X_O_HEAD_H

#include <iostream>
#include <Windows.h>
#include <random>
#include <cstdlib>
#include <chrono>


struct x_o {
    std::string* field{ nullptr };
    std::string player_1{ 'X' };
    std::string player_2{ 'O' };
    unsigned int X = 0;
    unsigned int O = 0;
    unsigned int t_o_g = 0;
    std::string bot_id {"no"};
    unsigned int figure = 0;
    std::string bot;
    std::string buf;
    unsigned int did_a_turn = 0;

    ~x_o(){field = nullptr; delete[] field; std::cout<<"ver. 0.2";}

    void x_o_clear();
};

int32_t getRandomNum(int32_t min, int32_t max);
int finish(std::string* arr);
void vs_1(x_o& xo);
void field_on_screen(x_o& xo);
int draw(x_o& xo);
void init_field(x_o& xo);
void start_game(x_o& xo);
void bot_x(x_o& xo);
void bot_o(x_o& xo);
void bot_rand(x_o& xo);
void start_game_bot(x_o& xo);
void start_game_bot_bot(x_o& xo);
void game(x_o& xo);
void exit();
bool repeat();

#endif //X_O_HEAD_H
