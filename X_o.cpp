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
    textures_ = {"../img/x/x.png", "../img/x/x1.png", "../img/x/x2.png", "../img/x/x3.png",
                "../img/x/x4.png", "../img/x/x5.png", "../img/x/x6.png", "../img/x/x7.png",
                "../img/x/x8.png"};
    shuffle(textures_.begin(),textures_.end(), std::mt19937(std::random_device()()));
    texture = textures_[getRandomNum(0,8)];
}

textures_x::~textures_x() {
textures_.clear();
}

textures_o::textures_o() {
    textures_.reserve(9);
    textures_ = {"../img/o/o.png", "../img/o/o1.png", "../img/o/o2.png", "../img/o/o3.png",
                 "../img/o/o4.png", "../img/o/o5.png", "../img/o/o6.png", "../img/o/o7.png",
                 "../img/o/o8.png"};
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
       // std::cout << "won !! " << field[1];
       // std::cout << std::endl;
        return true;
    }

    if (field[3] == field[4] && field[3] == field[5] && field[3] != -1) {
      //  std::cout << "won !! " << field[4];
      //  std::cout << std::endl;
        return true;
    }

    if (field[6] == field[7] && field[6] == field[8] && field[6] != -1) {
      //  std::cout << "won !! " <<field[7];
      //  std::cout << std::endl;
        return true;
    }

    //ungle

    if (field[0] == field[4] && field[0] == field[8] && field[0] != -1) {
       // std::cout << "won !! " << field[0];
       // std::cout << std::endl;
        return true;
    }

    if (field[2] == field[4] && field[2] == field[6] && field[2] != -1) {
       // std::cout << "won !! " << field[2];
       // std::cout << std::endl;
        return true;
    }

    //column

    if (field[0] == field[3] && field[0] == field[6] && field[0] != -1) {
       // std::cout << "won !! " << field[0];
       // std::cout << std::endl;
        return true;
    }

    if (field[1] == field[4] && field[1] == field[7] && field[1] != -1) {
       // std::cout << "won !! " << field[1];
       // std::cout << std::endl;
        return true;
    }

    if (field[2] == field[5] && field[2] == field[8] && field[2] != -1) {
       // std::cout << "won !! " << field[2];
       // std::cout << std::endl;
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


void X_o::start_game(sf::RenderWindow &_window) {

   //turn player if it is not bot turn
  if(!bot_turn){player_make_a_turn(_window);}

    //turn bot if it is bot torn
  if(bot_turn){bot_make_a_turn();}

}

X_o::X_o() = default;

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



all_objects_of_field::~all_objects_of_field() {
x_obj.clear();
o_obj.clear();
}

menu::menu() = default;

void menu::buttons_on_the_screen(sf::RenderWindow &_window) {
    sf::Sprite play = button_play();
    sf::Sprite exit = button_exit();

_window.clear();

    ///// если наехали на кнопку мышкой меняем цвет////////
    if (sf::IntRect(70, 20, 20, 20).contains(sf::Mouse::getPosition(_window))) { play.setColor(sf::Color::Blue); }
    if (sf::IntRect(90, 160, 20, 20).contains(sf::Mouse::getPosition(_window))) { exit.setColor(sf::Color::Blue); }
    ////////////обработчик нажатия на кнопку///////
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (sf::IntRect(70, 20, 20, 20).contains(sf::Mouse::getPosition(_window))) {
            _switch = 1;
            look_for_action = true;
        }
        if (sf::IntRect(90, 160, 20, 20).contains(sf::Mouse::getPosition(_window))) {
            _switch = 2;
            look_for_action = true;
        }
    }

_window.draw(play);
_window.draw(exit);

_window.display();

}

sf::Sprite menu::button_play() {
    sf::Texture play;
    play.loadFromFile("../img/x/x1.png");
    sf::Sprite play_sprite;
    play_sprite.setTexture(play);
    play_sprite.setPosition(70,20);
    return play_sprite;
}

sf::Sprite menu::button_exit() {
    sf::Texture exit;
    exit.loadFromFile("../img/o/o.png");
    sf::Sprite exit_sprite;
    exit_sprite.setTexture(exit);
    exit_sprite.setPosition(90,160);
    return exit_sprite;
}

