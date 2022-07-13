#include "head.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(240, 240), "X_o: 0.4_SFML", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("../ttf/YouTube Sans Light.ttf");
    sf::Text score("", font, 20);
    score.setColor(sf::Color::Black);
    score.setStyle(sf::Text::Bold);

    //enter name text objects
    sf::Texture white_bg;
    white_bg.loadFromFile("../img/white.png");
    sf::Sprite bg_menu;
    bg_menu.setTexture(white_bg);

    sf::Text Enter("", font, 20);
    Enter.setStyle(sf::Text::Bold);
    Enter.setColor(sf::Color::Black);
    Enter.setString("Enter your nickname: ");
    Enter.setPosition(5,5);

    sf::Text nickname("", font, 20);
    nickname.setColor(sf::Color::Black);
    nickname.setPosition(5,40);




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
    ver.setColor(sf::Color::White);
    ver.setString("ver. 0.4_SFML");
    ver.setPosition(180,5);

    sf::Text author("", font, 15);
    author.setColor(sf::Color::White);
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

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        game ->slots_on_screen(window, font);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {break;}
        if (profile::to_new_name) {break;}


    }

    //start_menu!

    //new_name

        while (window.isOpen() && profile::to_new_name){
            sf::Event event{};
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            if (event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128) {
                    str += static_cast<char>(event.text.unicode);
                    nickname.setString(str);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {break;}

            window.clear();
            window.draw(bg_menu);
            window.draw(Enter);
            window.draw(nickname);
            window.display();

        }


    //new_name!

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
    menu::buttons_on_the_screen(window);
    time_now = false;
    menu::run_game = false;
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