#pragma once
#include "BlockUnitManager.h"

class Player {
private:
	const int number; //プレイヤー番号
	const GameData& gameData;
	int score;

	// 一括で爆発するためフィールド上の全てのArrowBlockへの参照を持っておく
	std::shared_ptr<std::vector<std::weak_ptr<ArrowBlock>>> arrowBlocks;
	std::shared_ptr<Field> field;
	BlockUnitManager mngr;

public:
	Player(int player_num ,const GameData& gameData);
	~Player() = default;

	void update();
	void draw() const;

	void explode();
	int getScore() const { return score; }
};