#include "head.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(240, 240), "X_o by isDamont", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Clock think;
    sf::Clock clock;
bool time_now = false;
int time_now_int;


    sf::Texture scene;
    scene.loadFromFile("../img/scene.png");
    sf::Sprite main;
    main.setTexture(scene);


    all_objects_of_field obj;
    auto* game = new X_o;

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
                    game -> field_restart();
                    game -> bot_turn = false;
                    menu::field_was_restarted = true;
                }


                if(clock.getElapsedTime().asSeconds() > 50){
                    clock.restart();
                }

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

                if (game -> finish()){
                    std::cout<< "Finish !!"<<std::endl;
                    menu::field_was_restarted = false;
                    game -> bot_turn = false;
                    time_now = false;
                    menu::run_game = false;
                }

                if (game -> draw()){
                    std::cout<< "draw !!"<<std::endl;
                    menu::field_was_restarted = false;
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