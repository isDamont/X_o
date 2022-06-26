#include "head.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(240, 240), "X_o by isDamont", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Texture scene;
    scene.loadFromFile("../img/scene.png");
    sf::Sprite main;
    main.setTexture(scene);

all_objects_of_field obj;

    X_o game;

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(main);
        game.start_game(window);
        game.window_update(window, obj);

        if (game.finish()){std::cout<< "Finish !!"<<std::endl;}
        if (game.draw()){std::cout<< "draw !!"<<std::endl;}

        window.display();

    }
    return 0;
}