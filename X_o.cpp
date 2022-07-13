#include "head.h"

int32_t getRandomNum(int32_t min, int32_t max){
    const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}


X::X(float _x, float _y) : x(_x), y(_y) {texture_main_x = set_texture_x();}

sf::Texture X::set_texture_x() {
    sf::Texture texture_x;
    texture_x.loadFromFile(texture);
    return texture_x;
}

sf::Sprite X::get_sprite_x() {
    sf::Sprite sprite;
    sprite.setTexture(texture_main_x);
    sprite.setPosition(x,y);
    return sprite;
}

textures_x::textures_x() {
    textures_.reserve(9);
    textures_ = {"img/x/x.png", "img/x/x1.png", "img/x/x2.png", "img/x/x3.png",
                "img/x/x4.png", "img/x/x5.png", "img/x/x6.png", "img/x/x7.png",
                "img/x/x8.png"};
    shuffle(textures_.begin(),textures_.end(), std::mt19937(std::random_device()()));
    texture = textures_[getRandomNum(0,8)];
}

textures_x::~textures_x() {
textures_.clear();
}

textures_o::textures_o() {
    textures_.reserve(9);
    textures_ = {"img/o/o.png", "img/o/o1.png", "img/o/o2.png", "img/o/o3.png",
                 "img/o/o4.png", "img/o/o5.png", "img/o/o6.png", "img/o/o7.png",
                 "img/o/o8.png"};
    shuffle(textures_.begin(),textures_.end(), std::mt19937(std::random_device()()));
    texture = textures_[getRandomNum(0,8)];
}

textures_o::~textures_o() {
textures_.clear();
}

sf::Texture O::set_texture_o() {
    sf::Texture texture_o;
    texture_o.loadFromFile(texture);
    return texture_o;
}

O::O(float _x, float _y) : x(_x), y(_y) {texture_main_o = set_texture_o();}

sf::Sprite O::get_sprite_o() {
    sf::Sprite sprite;
    sprite.setTexture(texture_main_o);
    sprite.setPosition(x,y);
    return sprite;
}


game_field::game_field() {
field.reserve(9);
    for (size_t i = 0; i < 9 ; ++i) {
        field[i] = -1;
    }
    player_won = false;
    player_score = 0;
}

void game_field::field_restart() {
field.clear();
    for (size_t i = 0; i < 9 ; ++i) {
        field[i] = -1;
    }
}

void game_field::player_turn(int where, int who) {
    field[where] = who;

}

int game_field::get_cell_status(int cell) {
    return field[cell];
}

bool game_field::finish() {
//string

    if (field[0] == field[1] && field[0] == field[2] && field[0] != -1) {
        //check for winner
       if (field[1] == 1){
           player_won = true;
       } else if (field[1] == 0){
           player_won = false;
       }
        return true;
    }

    if (field[3] == field[4] && field[3] == field[5] && field[3] != -1) {
        //check for winner
        if (field[4] == 1){
            player_won = true;
        } else if (field[4] == 0){
            player_won = false;
        }
        return true;
    }

    if (field[6] == field[7] && field[6] == field[8] && field[6] != -1) {
        //check for winner
        if (field[7] == 1){
            player_won = true;
        } else if (field[7] == 0){
            player_won = false;
        }
        return true;
    }

    //ungle

    if (field[0] == field[4] && field[0] == field[8] && field[0] != -1) {
        //check for winner
        if (field[0] == 1){
            player_won = true;
        } else if (field[0] == 0){
            player_won = false;
        }
        return true;
    }

    if (field[2] == field[4] && field[2] == field[6] && field[2] != -1) {
        //check for winner
        if (field[2] == 1){
            player_won = true;
        } else if (field[2] == 0){
            player_won = false;
        }
        return true;
    }

    //column

    if (field[0] == field[3] && field[0] == field[6] && field[0] != -1) {
        //check for winner
        if (field[0] == 1){
            player_won = true;
        } else if (field[0] == 0){
            player_won = false;
        }
        return true;
    }

    if (field[1] == field[4] && field[1] == field[7] && field[1] != -1) {
        //check for winner
        if (field[1] == 1){
            player_won = true;
        } else if (field[1] == 0){
            player_won = false;
        }
        return true;
    }

    if (field[2] == field[5] && field[2] == field[8] && field[2] != -1) {
        //check for winner
        if (field[2] == 1){
            player_won = true;
        } else if (field[2] == 0){
            player_won = false;
        }
        return true;
    }

    else
        return false;
}

bool game_field::draw() {
    int draw = 0;
    for (size_t i = 0; i < 9; i++){
        if (field[i] == 1 || field[i] == 0) {
            draw = draw + 1;
        }
        if (draw == 9){
            std::cout << std::endl;
            std::cout << "DRAW !!!" << std::endl;
            return true;
        }
    }
    return false;
}

int game_field::get_player_score() const {
    return player_score;
}

void game_field::plus_player_score() {
    player_score++;
}

void game_field::minus_player_score() {
    player_score --;
}

void game_field::restart_player_score() {
    player_score = 0;
}

bool game_field::get_player_won_status() const {
    return player_won;
}

void game_field::set_player_score(int score) {
player_score = score;
}

void X_o::wait_for_menu(){
    if (menu::look_for_action){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        menu::look_for_action = false;
        menu::_switch = 0;
        }
    }else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            menu::look_for_action = true;
        }
    }
}

void X_o::bot_make_a_turn() {
        // better place

        if (get_cell_status(4) == -1) {
            bot_turn = false;
            player_turn(4,0);
            better_turn = true;
            num_of_turn++;
            return;
        }

       // rand place
if(!better_turn) { //if the better place is taken it's time to get random turn
    if (num_of_turn == 0) {
        if (get_cell_status(4) != -1) {
            bot_turn = false;
            //if (turn_rand == -1) { // if no turn yet
                do {
                    turn_rand = getRandomNum(0, 8);
                } while (get_cell_status(turn_rand) != -1); // only not in center
            //}
            player_turn(turn_rand, 0);
            num_of_turn++;
            return;
        }
    }
}
     if(!better_turn || num_of_turn >= 1) {  //look for win  //if the better place turned - the next turn will get in through num_of_turn
             bot_turn = false;
            // if (turn_win == -1) {
                     //pre win
                     for (int i = 0; i < 9; i++){
                        int buf = get_cell_status(i);
                         if (get_cell_status(i) != 0 && get_cell_status(i) != 1) {
                             player_turn(i,0);
                             if (finish()) {
                                 bot_turn = false;
                                 turn_win = i;
                                 break;
                             }
                             else {
                                 player_turn(i,1);
                                 if (finish()) {
                                     bot_turn = false;
                                     turn_win = i;
                                     break;
                                 }
                                 else {
                                     player_turn(i,buf);
                                     turn_win = -1;
                                 }
                             }
                         }
                     }
                     //random if the pre win does not give a result
                 bot_turn = false;
                 if (turn_win == -1) {
                     do {
                         turn_win = getRandomNum(0, 8);
                     } while (get_cell_status(turn_win) != -1); //for not turn in place that is taken
                 }
            // }
             player_turn(turn_win, 0);
             num_of_turn++;
     }
 }


void X_o::start_game(sf::RenderWindow &_window, int thinking) {

   //turn player if it is not bot turn
  if(!bot_turn){player_make_a_turn(_window);}

    //turn bot if it is bot torn
  if(bot_turn && thinking == 9){bot_make_a_turn();}

    //wait for Esc button to go to menu

    wait_for_menu();

}

X_o::X_o() : player_name("X_o"){}

void X_o::window_update(sf::RenderWindow &_window, all_objects_of_field &_obj) {
    //x objects to display
        if (get_cell_status(0) == 1){
            _window.draw(_obj.x_obj[0].get_sprite_x());
        }
        if (get_cell_status(1) == 1){
            _window.draw(_obj.x_obj[1].get_sprite_x());
        }
        if (get_cell_status(2) == 1){
            _window.draw(_obj.x_obj[2].get_sprite_x());
        }
        if (get_cell_status(3) == 1){
            _window.draw(_obj.x_obj[3].get_sprite_x());
        }
        if (get_cell_status(4) == 1){
            _window.draw(_obj.x_obj[4].get_sprite_x());
        }
        if (get_cell_status(5) == 1){
            _window.draw(_obj.x_obj[5].get_sprite_x());
        }
        if (get_cell_status(6) == 1){
            _window.draw(_obj.x_obj[6].get_sprite_x());
        }
        if (get_cell_status(7) == 1){
            _window.draw(_obj.x_obj[7].get_sprite_x());
        }
        if (get_cell_status(8) == 1){
            _window.draw(_obj.x_obj[8].get_sprite_x());
        }
    //o objects to display
        if (get_cell_status(0) == 0){
            _window.draw(_obj.o_obj[0].get_sprite_o());
        }
        if (get_cell_status(1) == 0){
            _window.draw(_obj.o_obj[1].get_sprite_o());
        }
        if (get_cell_status(2) == 0){
            _window.draw(_obj.o_obj[2].get_sprite_o());
        }
        if (get_cell_status(3) == 0){
            _window.draw(_obj.o_obj[3].get_sprite_o());
        }
        if (get_cell_status(4) == 0){
            _window.draw(_obj.o_obj[4].get_sprite_o());
        }
        if (get_cell_status(5) == 0){
            _window.draw(_obj.o_obj[5].get_sprite_o());
        }
        if (get_cell_status(6) == 0){
            _window.draw(_obj.o_obj[6].get_sprite_o());
        }
        if (get_cell_status(7) == 0){
            _window.draw(_obj.o_obj[7].get_sprite_o());
        }
        if (get_cell_status(8) == 0){
            _window.draw(_obj.o_obj[8].get_sprite_o());
        }

  // X x0(5,35);  X x1(70,20);  X x2(140,10);
  // X x3(10,110); X x4(80,85); X x5(145,70);
  // X x6(20,180); X x7(90,160); X x8(160,145);

  //  O o0(5,35);  O o1(70,20);  O o2(140,10);
  //  O o3(10,110); O o4(80,85); O o5(145,70);
  //  O o6(20,180); O o7(90,160); O o8(160,145);
}

void X_o::player_make_a_turn(sf::RenderWindow &_window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::IntRect(0, 0, 55, 85).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(0) == -1 && !finish()) {
                    player_turn(0, 1);
                    bot_turn = true;
                }
            }
            if (sf::IntRect(60, 0, 75, 75).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(1) == -1 && !finish()) {
                    player_turn(1, 1);
                    bot_turn = true;
                }
            }
            if (sf::IntRect(140, 0, 150, 60).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(2) == -1 && !finish()) {
                    player_turn(2, 1);
                    bot_turn = true;
                }
            }

            if (sf::IntRect(0, 110, 60, 60).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(3) == -1 && !finish()) {
                    player_turn(3, 1);
                    bot_turn = true;
                }
            }
            if (sf::IntRect(61, 80, 80, 70).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(4) == -1 && !finish()) {
                    player_turn(4, 1);
                    bot_turn = true;
                }
            }
            if (sf::IntRect(141, 70, 150, 60).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(5) == -1 && !finish()) {
                    player_turn(5, 1);
                    bot_turn = true;
                }
            }

            if (sf::IntRect(0, 171, 65, 60).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(6) == -1 && !finish()) {
                    player_turn(6, 1);
                    bot_turn = true;
                }
            }
            if (sf::IntRect(72, 160, 85, 70).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(7) == -1 && !finish()) {
                    player_turn(7, 1);
                    bot_turn = true;
                }
            }
            if (sf::IntRect(160, 140, 150, 75).contains(sf::Mouse::getPosition(_window))) {
                if (get_cell_status(8) == -1 && !finish()) {
                    player_turn(8, 1);
                    bot_turn = true;
                }
            }
        }
}

void X_o::score_on_screen(sf::Text &_text, sf::RenderWindow &_window) {

    std::ostringstream player_score_string;    // int to string
    player_score_string << get_player_score();		//put the player score to ostringstream object

    _text.setString("Score: " + player_score_string.str());
    _text.setPosition(150,215);

    _window.draw(_text);
}

std::string X_o::get_player_name() {
    return player_name;
}

void X_o::set_player_name(std::string name) {
    player_name = std::move(name);
}


all_objects_of_field::~all_objects_of_field() {
x_obj.clear();
o_obj.clear();
}

menu::menu() = default;


void menu::buttons_on_the_screen(sf::RenderWindow &_window, sf::Text& _text, sf::Clock _clock, sf::Font& _font) {
    //set texture to play button
    sf::Texture play_texture;
    play_texture.loadFromFile("img/buttons/new_game.png");
    sf::Sprite play_button;
    play_button.setTexture(play_texture);
    play_button.setPosition(55,88);


    //set texture to exit button
    sf::Texture exit_texture;
    exit_texture.loadFromFile("img/buttons/quit.png");
    sf::Sprite exit_button;
    exit_button.setTexture(exit_texture);
    exit_button.setPosition(70,140);

    //bg
    sf::Texture white_bg;
    white_bg.loadFromFile("img/white.png");
    sf::Sprite bg_menu;
    bg_menu.setTexture(white_bg);

    //set texture to continue button
    sf::Texture continue_texture;
    continue_texture.loadFromFile("img/buttons/continue.png");
    sf::Sprite continue_button;
    continue_button.setTexture(continue_texture);
    continue_button.setPosition(55,40);

    //Countdown
    std::stringstream clock_str;
    clock_str << 1 - _clock.getElapsedTime().asSeconds();
    sf::Text countdown("", _font, 15);
    countdown.setFillColor(sf::Color::Black);
    countdown.setString(clock_str.str());
    countdown.setPosition(100,5);

_window.clear();
_window.draw(bg_menu);

if(_clock.getElapsedTime().asSeconds() > 1){  //pause for missclick

if (_continue) {
    if (sf::IntRect(55, 40, 131, 37).contains(sf::Mouse::getPosition(_window))) {
        continue_button.setColor(sf::Color::Green);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            _switch = 1;
            look_for_action = true;
        }
    }
}else{
    continue_button.setColor(sf::Color::Red);
}

    if (sf::IntRect(55, 88, 131, 37).contains(sf::Mouse::getPosition(_window))) {
        play_button.setColor(sf::Color::Green);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            _switch = 2;
            menu::field_was_restarted = false;
            look_for_action = true;
            _continue = true;
        }
    }
    if (sf::IntRect(70, 140, 100, 70).contains(sf::Mouse::getPosition(_window))) {
       exit_button.setColor(sf::Color::Cyan);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            _switch = 3;
            look_for_action = true;
        }
    }
}

_window.draw(_text);
_window.draw(play_button);
_window.draw(exit_button);
_window.draw(continue_button);

if(1 - _clock.getElapsedTime().asSeconds() > 0){
_window.draw(countdown);
} else {
    countdown.setString("Ready to play :D");
    _window.draw(countdown);
}
_window.display();

}

profile::profile() {
    save_file = new std::string[6];
    std::fstream f_in;
    f_in.open("save.xo", std::ios::in);
    for (int i = 0; i < 6; ++i) {
       f_in >> *(save_file+i);
    }
    if(save_file->empty()){
        for (int i = 0; i < 6; ++i) {
            save_file[i] = "0";
        }
    }
    f_in.close();
    num_of_slot_in_use = 0;
}

void profile::save(int num_of_slot) {
    std::ostringstream player_score_slot;           // int to string
    player_score_slot << get_player_score();		//put the player score to ostringstream object

    std::ofstream f_out;

    switch (num_of_slot) {
        case 1:{
            //slot 1
            save_file[0] = player_score_slot.str();
            save_file[1] = get_player_name();
            break;
        }
        case 2:{
            //slot 2
            save_file[2] = player_score_slot.str();
            save_file[3] = get_player_name();
            break;
        }
        case 3:{
            //slot 3
            save_file[4] = player_score_slot.str();
            save_file[5] = get_player_name();
            break;
        }
        default:
            break;
    }

    f_out.open("save.xo", std::ios::out);

    for (int i = 0; i < 6; ++i) {
       f_out << *(save_file+i) << " ";
    }

    f_out.close();

}

void profile::open(int num_of_slot) {
    std::ostringstream player_score_slot;           // int to string

int score;

    switch (num_of_slot) {
        case 1:{
            //slot 1
            player_score_slot.str(save_file[0]);
            score = atoi(player_score_slot.str().c_str());
            set_player_score(score);
            set_player_name(save_file[1]);
            break;
        }
        case 2:{
            //slot 2
            player_score_slot.str(save_file[2]);
            score = atoi(player_score_slot.str().c_str());
            set_player_score(score);
            set_player_name(save_file[3]);
            break;
        }
        case 3:{
            //slot 3
            player_score_slot.str(save_file[4]);
            score = atoi(player_score_slot.str().c_str());
            set_player_score(score);
            set_player_name(save_file[5]);
            break;
        }
        default:
            break;
    }
    std::ifstream f_in;
    f_in.open("save.xo", std::ios::in);

    for (int i = 0; i < 6; ++i) {
        f_in >> *(save_file+i);
    }

    f_in.close();
}

profile::~profile() {
    save(num_of_slot_in_use);
    delete[] save_file;
}

void profile::slots_on_screen(sf::RenderWindow &_window, sf::Font &_font) {
    sf::Texture slots;
    slots.loadFromFile("img/buttons/empty.png");

    sf::Text slot("", _font, 15);
    slot.setFillColor(sf::Color::Black);

    //bg
    sf::Texture white_bg;
    white_bg.loadFromFile("img/white.png");
    sf::Sprite bg_menu;
    bg_menu.setTexture(white_bg);

    sf::Text choose("", _font, 20);
    choose.setStyle(sf::Text::Bold);
    choose.setFillColor(sf::Color::Black);
    choose.setString("choose a save slot:");
    choose.setPosition(40,5);

    //set texture to slot 1
    sf::Sprite slot_1;
    slot_1.setTexture(slots);
    slot_1.setPosition(55,50);

    //set texture to slot 2
    sf::Sprite slot_2;
    slot_2.setTexture(slots);
    slot_2.setPosition(55,98);

    //set texture to slot 3
    sf::Sprite slot_3;
    slot_3.setTexture(slots);
    slot_3.setPosition(55,146);


    _window.clear();
    _window.draw(bg_menu);

        if (sf::IntRect(55, 50, 131, 37).contains(sf::Mouse::getPosition(_window))) {
            slot_1.setColor(sf::Color::Green);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                num_of_slot_in_use = 1;
                if(save_file[1] == "0"){
                    profile::to_new_name = true;
                }else{
                open(num_of_slot_in_use);
                profile::next_menu = true;
                menu::_continue = true;
                }
        //action
            }
        }

    if (sf::IntRect(55, 98, 131, 37).contains(sf::Mouse::getPosition(_window))) {
        slot_2.setColor(sf::Color::Green);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            num_of_slot_in_use = 2;
            if(save_file[3] == "0"){
                profile::to_new_name = true;
            }else{
                open(num_of_slot_in_use);
                profile::next_menu = true;
                menu::_continue = true;
            }
     //action
        }
    }

    if (sf::IntRect(55, 146, 131, 37).contains(sf::Mouse::getPosition(_window))) {
        slot_3.setColor(sf::Color::Green);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            num_of_slot_in_use = 3;
            if(save_file[5] == "0"){
                profile::to_new_name = true;
            }else{
                open(num_of_slot_in_use);
                profile::next_menu = true;
                menu::_continue = true;
            }
          //action
        }
    }

    _window.draw(choose);

    _window.draw(slot_1);
    if (save_file[1] == "0"){
        slot.setString("(empty)");
        slot.setPosition(95,57);
        _window.draw(slot);
    } else {
        slot.setString(save_file[1]);
        slot.setPosition(90,57);
        _window.draw(slot);
    }

    _window.draw(slot_2);
    if (save_file[3] == "0"){
        slot.setString("(empty)");
        slot.setPosition(95,106);
        _window.draw(slot);
    } else {
        slot.setString(save_file[3]);
        slot.setPosition(90,106);
        _window.draw(slot);
    }

    _window.draw(slot_3);
    if (save_file[5] == "0"){
        slot.setString("(empty)");
        slot.setPosition(95,155);
        _window.draw(slot);
    } else {
        slot.setString(save_file[5]);
        slot.setPosition(90,155);
        _window.draw(slot);
    }

    _window.display();

}

int profile::get_slot_num() const {
return num_of_slot_in_use;
}

std::string profile::get_slot_num_str() const {
    std::ostringstream slot;           // int to string
    slot << num_of_slot_in_use;
    return slot.str();
}


