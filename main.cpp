#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "ball.h"
#include "paddle.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
    window.setFramerateLimit(60);

    Ball b(400, 300, 20, 10, 10);
    Paddle p(400, 500, 100, 20, 10);

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
        p.block(800);

        b.move();
        b.bounceW(800,600);
        if(b.pos().y + b.radius() >= p.pos().y - (p.size().y/2) && b.pos().y - b.radius() <= p.pos().y + (p.size().y/2)){
            if(b.pos().x + b.radius() >= p.pos().x - (p.size().x/2) && b.pos().x - b.radius() <= p.pos().x + (p.size().x/2)){
                float dXValue = abs(b.pos().x - p.pos().x)/((p.size().x/2)+b.radius()); 
                float dYValue = abs(b.pos().y - p.pos().y)/((p.size().y/2)+b.radius());
                if (dXValue > dYValue){
                    b.bouncePX();
                    b.move();
                }
                else if (dXValue < dYValue){
                    b.bouncePY();
                    b.move();
                }
                else {
                    b.bouncePX();
                    b.bouncePY();
                    b.move();
                }
            }
        }

        window.clear(sf::Color::Black);
        b.draw(window);
        p.draw(window);
        window.display();
    }

    return 0;
}
