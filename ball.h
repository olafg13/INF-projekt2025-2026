#include <SFML/Graphics.hpp>
#include <iostream>

class Ball{
    private:
        float x=0,y=0;
        float r=0;
        float dx=0,dy=0;
        sf::CircleShape ball;
    public:
        Ball(float x_in, float y_in, float r_in, float dx_in, float dy_in);
        void draw(sf::RenderWindow &window);
        void move();
        void bounceW(float w, float h);
        void bouncePX();
        void bouncePY();
        sf::Vector2f pos() {return ball.getPosition();}
        float radius() {return ball.getRadius();}
};

Ball::Ball(float x_in, float y_in, float r_in, float dx_in, float dy_in){
    x = x_in;
    y = y_in;
    r = r_in;
    dx = dx_in;
    dy = dy_in;
    ball.setRadius(r);
    ball.setOrigin(r, r);
    ball.setPosition(x,y);
    ball.setFillColor(sf::Color(100,100,100));
    ball.setOutlineThickness(2);
    ball.setOutlineColor(sf::Color(100,0,100));
}

void Ball::draw(sf::RenderWindow &window){
    window.draw(ball);
}

void Ball::move(){
    x = x + dx;
    y = y + dy;
    ball.setPosition(x,y);
}

void Ball::bounceW(float w, float h){
    if (x+r >= w || x-r <= 0){
        dx = -dx;
        move();
    }
    
    if (y+r >= h || y-r <= 0){
        dy = -dy;
        move();
    }
}

void Ball::bouncePX(){
    dx = -dx;
}

void Ball::bouncePY(){
    dy = -dy;
}