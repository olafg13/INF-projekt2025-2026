#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once

class Paddle{
    private:
        float x=0,y=0;
        float width=0, height=0;
        float speed=0;
        sf::RectangleShape rectangle;
    public:
        Paddle(float x_in, float y_in, float width_in, float height_in, float speed_in);
        void draw(sf::RenderWindow &window);
        void moveRight();
        void moveLeft();
        void block(float w);
        sf::Vector2f pos() {return rectangle.getPosition();}
        sf::Vector2f size() {return rectangle.getSize();}
};

Paddle::Paddle(float x_in, float y_in, float width_in, float height_in, float speed_in){
    x = x_in;
    y = y_in;
    speed = speed_in;
    width = width_in;
    height = height_in;
    rectangle.setSize(sf::Vector2f(width,height));
    rectangle.setOrigin(width/2, height/2);
    rectangle.setPosition(x,y);
    rectangle.setFillColor(sf::Color(100,100,100));
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(100,0,100));
}

void Paddle::draw(sf::RenderWindow &window){
    window.draw(rectangle);
}

void Paddle::moveRight(){
    x = x + speed;
    rectangle.setPosition(x,y);
}

void Paddle::moveLeft(){
    x = x - speed;
    rectangle.setPosition(x,y);
}

void Paddle::block(float w){
    if (x+(width/2) >= w){
        x = x - speed;
    }
    if (x-(width/2) <= 0){
        x = x + speed;
    }
}