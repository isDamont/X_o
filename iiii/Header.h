#pragma once
#include <iostream>


void __fastcall game(x_o& xo);
void start_game_bot(x_o& xo);
void start_game(x_o& xo);
void init_field(x_o& xo);
int draw(x_o& xo);
void __fastcall field_on_screen(x_o& xo);
void vs_1(x_o& xo);
int inline finish(std::string* arr);
int32_t getRandomNum(int32_t min, int32_t max);