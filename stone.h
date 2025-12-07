#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#pragma once

class Stone{
    private:
        int hp;
        bool recentDamageFlag;
        bool isDead;
        float x, y;
        float width, height;
        static const std::array<sf::Color, 4> colorLUT;
        sf::RectangleShape rectangle;
    public:
        Stone(float x_in, float y_in, float width_in, float height_in, int hp_in);
        void draw(sf::RenderWindow &window);
        void updateColor();
        void takeDamage();
        bool collideBall(float bx,float  by,float  radius);
        bool getIsDead();
        int getHp();
        sf::Vector2f pos() {return rectangle.getPosition();}
        sf::Vector2f size() {return rectangle.getSize();}
};

const std::array<sf::Color, 4> Stone::colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
    };

Stone::Stone(float x_in, float y_in, float width_in, float height_in, int hp_in){
    hp = hp_in;
    if (hp > 3){
        hp = 3;
    }
    if (hp < 0){
        hp = 0;
    }
    x = x_in;
    y = y_in;
    height = height_in;
    width = width_in;
    isDead = false;
    rectangle.setSize(sf::Vector2f(width_in,height_in));
    rectangle.setOrigin(width_in/2, height_in/2);
    rectangle.setPosition(x_in,y_in);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(255,255,255));
    updateColor();
    recentDamageFlag = false;
}

void Stone::draw(sf::RenderWindow &window){
    if(isDead == false){
    window.draw(rectangle);
    }
}

void Stone::updateColor(){
    rectangle.setFillColor(colorLUT[hp]);
}

void Stone::takeDamage(){
    if (hp>0) hp = hp -1;
    if (hp==0) {
        isDead = true;
    };
    updateColor();
}

bool Stone::getIsDead(){
    return isDead;
}


bool Stone::collideBall(float bx, float by, float radius) {
        float left = x - width/2;
        float right = x + width/2;
        float top = y - height/2;
        float bottom = y + height/2;

        if (bx + radius >= left && bx - radius <= right &&
            by + radius >= top && by - radius <= bottom && recentDamageFlag == false) {
            takeDamage();
            recentDamageFlag = true;
            return true;
        }
        recentDamageFlag = false;
        return false;
}

int Stone::getHp() {
     return hp;
}

