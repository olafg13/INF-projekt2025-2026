#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "ball.h"
#include "paddle.h"
#include "stone.h"
#include "menu.h"
#pragma once

class Game{
    private:

        float width, height;
        int columns, rows;
        float blockSizeY, blockSizeX;
        int menu_selected_flag = 0;

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
                Stone((0.5 + j) * (blockSizeX+2), 50 + (i * (blockSizeY+2)), blockSizeX, blockSizeY, hp));
        }
    }
}

void Game::run(){
    Menu menu(window.getSize().x, window.getSize().y);
    sf::Event event;
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
        if (menu_selected_flag == 0)
        {
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Up)
                {
                    myDelay(250);
                    menu.przesunG();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    myDelay(250);
                    menu.przesunD();
                }
            }
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
            {
                std::cout << "Uruchamiam gre..." << std::endl;
                menu_selected_flag = 1;
                width = 800;
                height = 600;
                b = Ball(width/2, height/2, 20, 5, 5);
                p = Paddle(width/2, height - (height/6), 150, 50, 10);
                
                stones.clear();
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        int hp = (i < 1) ? 3 : (i < 3) ? 2 : 1;
                        stones.push_back(
                            Stone((0.5 + j) * (blockSizeX+2), 50 + (i * (blockSizeY+2)), blockSizeX, blockSizeY, hp));
                    }
                }

            }    
            
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
            {
                std::cout << "Zapisuje gre..." << std::endl;
                menu_selected_flag = 0;
                gameState save(p.pos().x, p.pos().y, b.pos().x, b.pos().y, 5, 5, stones);
                save.save("savefile.txt");
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
            {
                std::cout << "Wczytuje gre..." << std::endl;
                gameState load(0,0,0,0,0,0,{});
                load.load("savefile.txt");
                load.apply(p, b, stones);
                menu_selected_flag = 1;
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
            {
                std::cout << "Najlepsze wyniki..." << std::endl;
                menu_selected_flag = 2;
            }
                
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 4)
            {
                std::cout << "Koniec gry..." << std::endl;
                break;
            }
            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
                
        }
				
		if (menu_selected_flag == 1){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                p.moveLeft();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                p.moveRight();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                menu_selected_flag = 0;
            }
            p.block(width);

            b.move();

            if(b.pos().y + b.radius() >= height){
                std::cout << "MISS! KONIEC GRY\n";
                window.close();
                break;
            }

            b.collideWall(width,height);
            b.collideRectangle(p.pos().x, p.pos().y, p.size().x, p.size().y); //paddle
            for (int i = 0; i < stones.size(); i++) {
                if (!stones[i].getIsDead()){
                b.collideRectangle(stones[i].pos().x, stones[i].pos().y, stones[i].size().x, stones[i].size().y);
            }

            }
            for (int i = 0; i < stones.size(); i++) {
                stones[i].collideBall(b.pos().x, b.pos().y, b.radius());
                if (stones[i].getIsDead()) {
                    stones.erase(stones.begin() + i);
                }
            }
            for (int i = 0; i < stones.size(); i++) {
                if (stones[i].getIsDead()) {
                    stones.erase(stones.begin() + i);
                    i--;
                }
            }

            window.clear(sf::Color::Black);
            for (int i = 0; i < stones.size(); i++) {
                stones[i].draw(window);
            }
            b.draw(window);
            p.draw(window);
            window.display();
            /*for (int i = 0; i < stones.size(); i++) {
                std::cout << "Stone " << i 
                << ": x=" << stones[i].pos().x 
                << ", y=" << stones[i].pos().y 
                << ", hp=" << stones[i].getHp() 
                << ", isDead=" << stones[i].getIsDead() 
                << std::endl;
            }*/ //DEBUG STONES
            myDelay(10);
        }
    }
}
