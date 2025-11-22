#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "ball.h"
#include "paddle.h"
#include "stone.h"

class Game{
    private:

        float width, height;
        int columns, rows;
        float blockSizeY, blockSizeX;

        Ball b;
        Paddle p;
        std::vector<Stone> stones;

        sf::RenderWindow window;

    public:
        Game();
        void run();
};

Game::Game():

width(800), height(600),
window(sf::VideoMode(width, height), "SFML"),
b(width/2, height/2, 20, 5, 5),
p(width/2, height - (height/6), 150, 50, 10)

{
    columns = 6;
    rows = 7;
    blockSizeY = 25;
    blockSizeX = (width - (columns-1)*2) / columns;

    window.setFramerateLimit(60);

    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int hp = (i < 1) ? 3 : (i < 3) ? 2 : 1;
            stones.push_back(
                Stone((0.5 + j) * (blockSizeX+2), 50 + (i * (blockSizeY+2)), blockSizeX, blockSizeY, hp)
            );
        }
    }
}

void Game::run(){
    
    while (window.isOpen()) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            p.moveLeft();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            p.moveRight();
        }
        p.block(width);

        b.move();

        if(b.pos().y + b.radius() >= height){
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
            break;
        }

        for (int i = 0; i < stones.size(); i++) {
            stones[i].collideBall(b.pos().x,b.pos().y,b.radius());
        }

        b.collideWall(width,height);
        b.collideRectangle(p.pos().x, p.pos().y, p.size().x, p.size().y); //paddle
        for (int i = 0; i < stones.size(); i++) {
            b.collideRectangle(
            stones[i].pos().x,
            stones[i].pos().y,
            stones[i].size().x,
            stones[i].size().y
            );

        }

        window.clear(sf::Color::Black);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                stones[(i*columns) + j].draw(window);
            }
        }
        b.draw(window);
        p.draw(window);
        window.display();
    }
}