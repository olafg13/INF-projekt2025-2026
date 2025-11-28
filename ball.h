#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once

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
        void collideWall(float w, float h);
        void bounceX();
        void bounceY();
        void setPos(float x1, float y1);
        sf::Vector2f pos() {return ball.getPosition();}
        float radius() {return ball.getRadius();}
        void collideRectangle(float px,float  py,float  sizeX,float  sizeY);
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

void Ball::collideWall(float w, float h){
    if (x+r >= w || x-r <= 0){
        bounceX();
        while(x+r >= w || x-r <= 0){
        move();
        }
    }
    
    if (y+r >= h || y-r <= 0){
        bounceY();
        while(y+r >= h || y-r <= 0){
        move();
        }
    }
}

void Ball::bounceX(){
    dx = -dx;
}

void Ball::bounceY(){
    dy = -dy;
}

void Ball::setPos(float x1, float y1){
    x = x1;
    y = y1;
}

void Ball::collideRectangle(float px,float  py,float  sizeX,float  sizeY){
    if(pos().y + radius() >= py - (sizeY/2) && 
                    pos().y - radius() <= py + (sizeY/2) && 
                    pos().x + radius() >= px - (sizeX/2) && 
                    pos().x - radius() <= px + (sizeX/2))
                {
                float left = (px - sizeX/2);
                float right = (px + sizeX/2);
                float top = (py + sizeY/2);
                float bot = (py - sizeY/2);
                float overlapLeft = (pos().x + radius())-left;
                float overlapRight = right - (pos().x - radius());
                float overlapTop = top - (pos().y - radius());
                float overlapBot = (pos().y + radius())-bot;
                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBot});
                    if (minOverlap == overlapRight){
                        setPos(px + sizeX/2 + radius(), pos().y);
                        bounceX();
                    }
                    else if(minOverlap == overlapLeft){
                        setPos(px-sizeX/2 - radius(), pos().y);
                        bounceX();
                    }
                    else if (minOverlap == overlapBot){
                        setPos(pos().x ,py - sizeY/2 - radius());
                        bounceY();
                    }
                    else if (minOverlap == overlapTop){
                        setPos(pos().x , py + sizeY/2 + radius());
                        bounceY();
                    }
                /*while(pos().y + radius() >= py - (sizeY/2) && 
                    pos().y - radius() <= py + (sizeY/2) && 
                    pos().x + radius() >= px - (sizeX/2) && 
                    pos().x - radius() <= px + (sizeX/2)){
                    move();
                }*/
            }
    }