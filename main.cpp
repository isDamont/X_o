#include "head.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(240, 240), "X_o: 0.4_SFML", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("../ttf/YouTube Sans Light.ttf");
    sf::Text score("", font, 20);
    score.setFillColor(sf::Color::Black);
    score.setStyle(sf::Text::Bold);

    //text objects
    sf::Texture white_bg;
    white_bg.loadFromFile("../img/white.png");
    sf::Sprite bg_menu;
    bg_menu.setTexture(white_bg);

    sf::Text Enter("", font, 20);
    Enter.setStyle(sf::Text::Bold);
    Enter.setFillColor(sf::Color::Black);
    Enter.setString("Enter your nickname: ");
    Enter.setPosition(20,7);

    sf::Text nickname("", font, 20);
    nickname.setFillColor(sf::Color::Black);
    nickname.setPosition(60,48);

    sf::Text slot("", font, 20);
    slot.setStyle(sf::Text::Bold);
    slot.setFillColor(sf::Color::Black);





    sf::Clock think;
    sf::Clock clock;
bool time_now = false;
int time_now_int;
std::string str;


    sf::Texture scene;
    scene.loadFromFile("../img/scene.png");
    sf::Sprite main;
    main.setTexture(scene);


    all_objects_of_field obj;
    auto* game = new profile;



    //pre_start

    sf::Text ver("", font, 10);
    ver.setFillColor(sf::Color::White);
    ver.setString("ver. 0.4_SFML");
    ver.setPosition(180,5);

    sf::Text author("", font, 15);
    author.setFillColor(sf::Color::White);
    author.setString(" dev by isDamont\n github.com/isDamont\n t.me/Damont");
    author.setPosition(5,176);


    sf::Texture pre_start_texture;
    pre_start_texture.loadFromFile("../img/black.png");
    sf::Sprite pre_start_sprite;
    pre_start_sprite.setTexture(pre_start_texture);

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {break;}
        if (clock.getElapsedTime().asSeconds() > 3) {break;}


        window.draw(pre_start_sprite);
        window.draw(ver);
        window.draw(author);
        window.display();
        window.clear();


    }
    //pre_start

    //start_menu
    start_menu:
    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        game ->slots_on_screen(window, font);
        if (profile::to_new_name) {break;}
        if (profile::next_menu) {break;}


    }
    //start_menu!

    //new_name
    sf::Texture enter_name_spot;
    enter_name_spot.loadFromFile("../img/name.png");
    sf::Sprite enter_name_spot_sprite;
    enter_name_spot_sprite.setTexture(enter_name_spot);
    enter_name_spot_sprite.setPosition(50, 40);

    slot.setString("slot # " + game -> get_slot_num_str());
    slot.setPosition(20,150);

    char cursor = '|';

        while (window.isOpen() && profile::to_new_name){
            sf::Event event{};
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }

if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 0){nickname.setString(str + cursor);}
else{nickname.setString(str);}


            if (event.type == sf::Event::TextEntered){

                if (event.text.unicode < 128) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                        if(!str.empty()){str.pop_back();}
                    }
                    if(str.size()<9){
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) &&
                            !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) &&
                            !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                        str += static_cast<char>(event.text.unicode);
                    }
                        if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 0){nickname.setString(str + cursor);}
                        else{nickname.setString(str);}
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {profile::to_new_name = false; goto start_menu;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !str.empty()) {
                game ->set_player_name(str);
                game ->save(game->get_slot_num());
                break;
            }

            window.clear();
            window.draw(bg_menu);

            if (str.size() == 9){
                sf::Text max("", font, 15);
                max.setFillColor(sf::Color::Red);
                max.setString("Max length 9 characters");
                max.setPosition(40,80);
                window.draw(max);
            }

            if (str.empty()){
                sf::Text max("", font, 15);
                max.setFillColor(sf::Color::Red);
                max.setString("Cannot be empty!");
                max.setPosition(60,80);
                window.draw(max);
            }

            ver.setFillColor(sf::Color::Black);
            ver.setPosition(90,225);

            window.draw(ver);
            window.draw(Enter);
            window.draw(enter_name_spot_sprite);
            window.draw(nickname);
            window.draw(slot);
            window.display();

        }


    //new_name!


    nickname.setString("Welcome,\n" + game -> get_player_name() + " !!!");
    nickname.setPosition(5,0);
    nickname.setCharacterSize(15);

    clock.restart();

    sf::Clock pause_slot;

    while (window.isOpen()){

        //time
       int thinking = think.getElapsedTime().asMilliseconds();
       think.restart();
        //time!

        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

if (!menu::look_for_action){
    menu::buttons_on_the_screen(window, nickname, clock);
    time_now = false;
    menu::run_game = false;
    if(pause_slot.getElapsedTime().asSeconds() > 1){  //pause for miss click
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){profile::next_menu = false; goto start_menu;}
    }
    }

        switch (menu::_switch) {
            case 1:
            case 2:{

                if(!menu::field_was_restarted){
                    game -> restart_player_score();
                    game -> field_restart();
                    game -> bot_turn = false;
                    menu::field_was_restarted = true;
                }

              /*
                if(clock.getElapsedTime().asSeconds() > 50){
                    clock.restart();
                }
              */

                if (!time_now){
                    time_now_int = static_cast<int>(clock.getElapsedTime().asSeconds());
                    time_now = true;
                }


                if(static_cast<int>(clock.getElapsedTime().asSeconds()) >= time_now_int + 1 && !menu::run_game){
                    menu::run_game = true;
                }

                //game cycle
                window.clear();
                window.draw(main);
                if(menu::run_game){game -> start_game(window, thinking);}

                game -> window_update(window, obj);
                game -> score_on_screen(score,window);
                pause_slot.restart();

                if (game -> finish()){
                    if(game -> get_player_won_status()){game -> plus_player_score(); std::cout<< "Player WON !!"<<std::endl;}
                    else if(!game -> get_player_won_status()){game -> minus_player_score(); std::cout<< "Bot WON !!"<<std::endl;}
                    game -> field_restart();
                    game -> bot_turn = false;
                    time_now = false;
                    menu::run_game = false;
                }

                if (game -> draw()){
                    game -> field_restart();
                    game -> bot_turn = false;
                    time_now = false;
                    menu::run_game = false;
                }

                window.display();
                //game cycle!
               break;
            }
            case 3:{
               window.close();
                break;
            }
            default:
               break;
        }

    }
    delete game;
    return 0;
}