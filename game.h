#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "ball.h"
#include "paddle.h"
#include "stone.h"
#include "menu.h"
#include "scores.h"
#pragma once

class Game{
    private:

        float width, height;
        int columns, rows;
        float blockSizeY, blockSizeX;
        int menu_selected_flag = 0;
        int gameStateFlag = 0;
        int score;

        sf::Font font;
        sf::Text scoreText;
        Ball b;
        Paddle p;
        Scores s;
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
p(width/2, height - (height/6), 150, 50, 10),
s()

{
    columns = 6;
    rows = 7;
    blockSizeY = 25;
    blockSizeX = (width - (columns-1)*2) / columns;
    
    
    if (!font.loadFromFile("LiberationSans-Regular.ttf")) {
        std::cout << "Nie mozna zaladowac czcionki!\n" << std::endl;
        return;
    }
    scoreText.setFont(font);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(width*0.005, height*0.9375);

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
    window.setKeyRepeatEnabled(true);
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) // zamykanie okna
                window.close();
            if (menu_selected_flag == 0) // logika menu
                {
                    if (event.type == sf::Event::KeyPressed){
                        if (event.key.code == sf::Keyboard::Escape && gameStateFlag ==1)
                        {
                            myDelay(250);
                            menu_selected_flag=1;
                        }
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
                        if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
                        {
                            std::cout << "Uruchamiam gre..." << std::endl;
                            menu_selected_flag = 1;
                            gameStateFlag = 1; //Flaga trwania gry
                            score = 0;
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
                        
                        else if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
                        {
                            std::cout << "Zapisuje gre..." << std::endl;
                            menu_selected_flag = 0;
                            gameState save(p.pos().x, p.pos().y, b.pos().x, b.pos().y, 5, 5, stones, score);
                            if(gameStateFlag==1) save.save("savefile.txt");
                            else std::cout << "Brak rozpoczetej gry do zapisania" << std::endl;
                        }

                        else if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
                        {
                            std::cout << "Wczytuje gre..." << std::endl;
                            gameState load(0,0,0,0,0,0,{},0);
                            if(!load.load("savefile.txt")){
                                std::cout << "Nie udalo sie wczytac" << std::endl;
                                break;
                            }
                            gameStateFlag = 1; //Flaga trwania gry
                            load.apply(p, b, stones, score);
                            menu_selected_flag = 1;
                        }

                        else if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
                        {
                            std::cout << "Najlepsze wyniki..." << std::endl;
                            menu_selected_flag = 2;
                        }
                            
                        else if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 4)
                        {
                            std::cout << "Koniec gry..." << std::endl;
                            window.close();
                        }
                    }
                }
        }
		
        if (menu_selected_flag == 0) // rysowanie menu
        {
            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
        }

		if (menu_selected_flag == 1){ // logika gry
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                p.moveLeft();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                p.moveRight();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                menu_selected_flag = 0;
            }
            p.block(width);

            b.move();

            if(b.pos().y + b.radius() >= height){
                std::cout << "MISS! KONIEC GRY\n";

                window.clear(sf::Color::Black);
                sf::Text koniec;
                sf::Font font;
                if (!font.loadFromFile("LiberationSans-Regular.ttf"))
                    {
                        return;
                    }
                koniec.setFont(font);
                koniec.setString("Koniec gry!");
                koniec.setCharacterSize(40);
                koniec.setFillColor(sf::Color::Red);
                sf::FloatRect bounds = koniec.getLocalBounds();
                koniec.setOrigin(bounds.width / 2, bounds.height / 2);
                koniec.setPosition(width/2,height/2);
                window.draw(koniec);
                window.display();

                s.save("Scores.txt", score);
                myDelay(3000);
                menu_selected_flag = 0;
                gameStateFlag = 2; //Flaga przegranej gry

            }

            b.collideWall(width,height);
            b.collideRectangle(p.pos().x, p.pos().y, p.size().x, p.size().y); //odbicie od paddle
            for (int i = 0; i < stones.size(); i++) //odbicie od stones
            {
                if (!stones[i].getIsDead()){
                b.collideRectangle(stones[i].pos().x, stones[i].pos().y, stones[i].size().x, stones[i].size().y);
            }

            }
            for (int i = 0; i < stones.size(); i++) //sprawdzanie i aktualizacja hp stones + score
            {
                if(stones[i].collideBall(b.pos().x, b.pos().y, b.radius())){
                    score = score+10;
                }
                if (stones[i].getIsDead()) {
                    stones.erase(stones.begin() + i);
                    score = score+50;
                }
            }
            
            scoreText.setString("Wynik: "+std::to_string(score));

            window.clear(sf::Color::Black);
            for (int i = 0; i < stones.size(); i++) {
                stones[i].draw(window);
            }
            b.draw(window);
            p.draw(window);
            window.draw(scoreText);
            window.display();
            myDelay(10);
        }
        
        if (menu_selected_flag == 2){
            std::ifstream file("Scores.txt");
            if(!file.is_open()){
                menu_selected_flag = 0;
                std::cout << "Nie udalo sie wczytac Scores.txt" << std::endl;
            }
            else{
                ScoreMenu sMenu(width,height,"Scores.txt");
                window.clear(sf::Color::Black);
                sMenu.draw(window);
                window.display();
                if (event.type == sf::Event::KeyPressed){
                    menu_selected_flag = 0;
                }
            }
        }
    }
}
