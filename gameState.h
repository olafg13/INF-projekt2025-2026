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
public:
	gameState(float px, float py, float bx, float by, float bvx, float bvy, std::vector<Stone> stones);
	bool save(const std::string& filename);
	bool load(const std::string& filename);
	void apply(Paddle &p, Ball &b, std::vector<Stone>& stones);
};

gameState::gameState(float px, float py, float bx, float by, float bvx, float bvy, std::vector<Stone> stones) {
	pPosX = px;
	pPosY = py;
	bPosX = bx;
	bPosY = by;
	bVelX = bvx;
	bVelY = bvy;
	blocks = stones;
}

bool gameState::save(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) return false;

	file << "Paddle " << pPosX << " " << pPosY << "\n";

	file << "Ball " << bPosX << " " << bPosY << " "
		<< bVelX << " " << bVelY << "\n";

	file << "Blocks " << blocks.size() << "\n";

	for (int i = 0; i < blocks.size(); i++) {
		file << "Stone " << blocks[i].pos().x << " " << blocks[i].pos().y << " " << blocks[i].getHp() << "\n";
	}
	
	file.close();
	return true;
}

bool gameState::load(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	std::string label;

	if (file >> label >> pPosX >> pPosY) {

	}

	if (file >> label >> bPosX >> bPosY >> bVelX >> bVelY) {

	}

	int blocksCount;
	file >> label >> blocksCount;

	blocks.clear();
	for (int i = 0; i < blocksCount; i++) {
		float x, y;
		int hp;
		file >> label >> x >> y >> hp;
		blocks.push_back(Stone(x, y, blockSizeX, blockSizeY, hp));
	}
	file.close();
	return true;
}

void gameState::apply(Paddle& p, Ball& b, std::vector<Stone>& stones) {
	p.setPos(pPosX, pPosY);
	b.setPos(bPosX, bPosY);
	stones = blocks;
}