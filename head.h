//
// Created by isDamont on 13.06.2022.
//

#ifndef X_o_HEAD_H
#define X_o_HEAD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <cstdlib>


struct textures_x{
    std::string texture;
    std::vector<std::string> textures_;
    textures_x();
    ~textures_x();
};

class X : textures_x{
private:
    float x;
    float y;

    sf::Texture texture_main_x;
    sf::Texture set_texture_x();
public:
    X(float _x, float _y);
    sf::Sprite get_sprite_x();
};

struct textures_o{
    std::string texture;
    std::vector<std::string> textures_;
    textures_o();
    ~textures_o();
};

class O : textures_o{
private:
    float x;
    float y;

    sf::Texture texture_main_o;
    sf::Texture set_texture_o();
public:
    O(float _x, float _y);
    sf::Sprite get_sprite_o();
};

struct all_objects_of_field {
//x
    std::vector<X> x_obj = { X(5,35),  X(70,20),  X(140,10), X(10,110), X(80,85), X(145,70), X(20,180),
                             X(90,160), X(160,145)};
//o
    std::vector<O> o_obj = {O(5,35),  O(70,20),  O(140,10),O(10,110), O(80,85), O(145,70), O(20,180),
                            O(90,160), O(160,145)};
    ~all_objects_of_field();
};

struct bot{
    bool bot_turn = false;
    int turn_rand = -1;
    int turn_win = -1;
    bool better_turn = false;
    int num_of_turn = 0;
};

class game_field : public bot{
public:
    game_field();
    void field_restart();
    void player_turn(int where, int who);
    int get_cell_status(int cell);
    [[nodiscard]] int get_player_score() const;
    [[nodiscard]] bool get_player_won_status() const;
    void plus_player_score();
    void set_player_score(int score);
    void minus_player_score();
    void restart_player_score();
    bool finish();
    bool draw();

private:
   std::vector<int> field;
   int player_score;
   bool player_won;

};


struct X_o : public game_field{
    X_o();
    void start_game(sf::RenderWindow &_window, int thinking);
    void window_update(sf::RenderWindow& _window, all_objects_of_field &_obj);
    void player_make_a_turn(sf::RenderWindow &_window);
    static void wait_for_menu();
    void bot_make_a_turn();
    void score_on_screen(sf::Text & _text, sf::RenderWindow &_window);

    std::string get_player_name();
    void set_player_name(std::string name);

private:
    std::string player_name;
};


struct menu : public game_field{
    menu();
    static void buttons_on_the_screen(sf::RenderWindow &_window, sf::Text & _text, sf::Clock _clock, sf::Font& _font);
    inline static unsigned _switch = 0;
    inline static bool look_for_action = false;
    inline static bool run_game = false;
    inline static bool _continue = false;
    inline static bool field_was_restarted = true;

};

class profile : public X_o{
public:
    void slots_on_screen(sf::RenderWindow &_window, sf::Font &_font);

    profile();
    ~profile();
    void save(int num_of_slot);
    void open(int num_of_slot = 0);
    [[nodiscard]] int get_slot_num() const;
    [[nodiscard]] std::string get_slot_num_str() const;

    inline static bool to_new_name = false;
    inline static bool next_menu = false;
private:
    std::string * save_file;
    int num_of_slot_in_use;
};



int32_t getRandomNum(int32_t min, int32_t max);
#endif //X_o_HEAD_H
