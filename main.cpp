#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "ball.h"
#include "paddle.h"
#include "stone.h"

int main() {

    const float width = 800;
    const float height = 600;
    
    std::vector<Stone> aliveStones;
    std::vector<Stone> stones;
    const int columns = 6;
    const int rows = 7;
    const float blockSizeY = 25;
    const float blockSizeX = (width - (columns-1)*2) / columns;

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML");
    window.setFramerateLimit(60);

    Ball b(width/2, height/2, 20, 10, 10);
    Paddle p(width/2, height - (height/6), 100, 200, 10);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int hp = (i < 1) ? 3 : (i < 3) ? 2 : 1;
            stones.push_back(
                Stone((0.5 + j) * (blockSizeX+2), 50 + (i * (blockSizeY+2)), blockSizeX, blockSizeY, hp)
            );
        }
    }

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

        for (int i = 0; i < stones.size(); i++) {
            stones[i].collideBall(b.pos().x,b.pos().y,b.radius());
        }

        /*for (int i = 0; i < stones.size(); i++) {
            bool check = stones[i].getIsDead();
            if (check = false){
                aliveStones.push_back(stones[i]);
            }
        }

        stones = aliveStones;*/

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


        /*if(b.pos().y + b.radius() >= height){
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
            break;
        }*/

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

    return 0;
}
