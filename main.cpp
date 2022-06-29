#include "head.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(240, 240), "X_o by isDamont", sf::Style::Close);
    window.setVerticalSyncEnabled(true);


    sf::Texture scene;
    scene.loadFromFile("../img/scene.png");
    sf::Sprite main;
    main.setTexture(scene);

    all_objects_of_field obj;
    auto* game = new X_o;

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

//if (!menu::look_for_action){
     //   menu::buttons_on_the_screen(window);
  //  }

       // switch (menu::_switch) {
           // case 1:

                //game cycle

                window.clear();
                window.draw(main);
                game -> start_game(window);
                game -> window_update(window, obj);

                if (game->finish()){std::cout<< "Finish !!"<<std::endl;}
                if (game->draw()){std::cout<< "draw !!"<<std::endl;}

                window.display();

                //game cycle!

             //   break;

           // case 2:
           //     window.close();
          //      break;

          //  default:
           //     break;
       // }

    }
    return 0;
}