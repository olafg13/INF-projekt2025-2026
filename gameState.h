#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "stone.h"
#include "paddle.h"
#include "ball.h"
#pragma once

struct BlockData {
	float x, y;
	int hp;
};

class gameState {
private:
	float pPosX, pPosY, bPosX, bPosY, bVelX, bVelY;
	std::vector<Stone> blocks;
	int rows = 7;
	int columns = 6;
	float width = 800;
	float height = 600;
	float blockSizeY = 25;
    float blockSizeX = (width - (columns-1)*2) / columns;
	int points;
public:
	gameState(float px, float py, float bx, float by, float bvx, float bvy, std::vector<Stone> stones, int score);
	bool save(const std::string& filename);
	bool load(const std::string& filename);
	void apply(Paddle &p, Ball &b, std::vector<Stone>& stones, int& score);
};

gameState::gameState(float px, float py, float bx, float by, float bvx, float bvy, std::vector<Stone> stones, int score) {
	pPosX = px;
	pPosY = py;
	bPosX = bx;
	bPosY = by;
	bVelX = bvx;
	bVelY = bvy;
	blocks = stones;
	points = score;
}
//zapis gry
bool gameState::save(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) return false; //detekcja błędu wczytania

	file << "Paddle " << pPosX << " " << pPosY << "\n";

	file << "Ball " << bPosX << " " << bPosY << " "
		<< bVelX << " " << bVelY << "\n";

	file << "Score" << " " << points << "\n";

	file << "Blocks " << blocks.size() << "\n";

	for (int i = 0; i < blocks.size(); i++) {
		file << "Stone " << blocks[i].pos().x << " " << blocks[i].pos().y << " " << blocks[i].getHp() << "\n";
	}
	
	file.close();
	return true;
}
//wczytanie gry
bool gameState::load(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) return false; //detekcja błędu wczytania

	std::string label;

	if (file >> label >> pPosX >> pPosY) {

	}

	if (file >> label >> bPosX >> bPosY >> bVelX >> bVelY) {

	}

	if (file >> label >> points) {

	}

	int blocksCount;
	file >> label >> blocksCount;

	blocks.clear();
	for (int i = 0; i < blocksCount; i++) { //zapis stanu bloków
		float x, y;
		int hp;
		file >> label >> x >> y >> hp;
		blocks.push_back(Stone(x, y, blockSizeX, blockSizeY, hp));
	}
	file.close();
	return true;
}
//zaaplikowanie wczytanego pliku
void gameState::apply(Paddle& p, Ball& b, std::vector<Stone>& stones, int& score) {
	p.setPos(pPosX, pPosY);
	b.setPos(bPosX, bPosY);
	stones = blocks;
	score = points;
}