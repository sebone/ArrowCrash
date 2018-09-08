#pragma once
#include "Field.h"
#include "BlockGenerator.h"

class Player {
private:
	const int number; //�v���C���[�ԍ�
	const GameData& gameData;

	Field field;
	BlockGenerator generator;

public:
	Player(int player_num ,const GameData& gameData);
	Player() = default;

	void update();
	void draw() const;
};