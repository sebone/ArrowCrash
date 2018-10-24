#pragma once
#include "BlockUnit.h"
#include <queue>

class BlockUnitManager {
private:
	//�`�����邽�߂ɕێ����Ă��邪���̃N���X�ł͎g��Ȃ�
	Field& field;
	std::vector<std::weak_ptr<ArrowBlock>>& arrowBlocks;
	const Point stdPos;
	const int blockSize;

	//�`��p
	std::vector<Point> nextUnitFramePos;
	Point stockFramePos;

	std::list<std::shared_ptr<BlockUnit>> nextUnits; //queue
	std::shared_ptr<BlockUnit> currentUnit;
	std::shared_ptr<BlockUnit> stock;
	
	void generate();

public:
	BlockUnitManager(Field& field_, std::vector<std::weak_ptr<ArrowBlock>>& arrowBlocks_, const GameData& gameData, int player_num);
	~BlockUnitManager() = default;
	void update();
	void draw() const;
	BlockUnit& getCurrentUnit() { return *currentUnit; }
	void exchangeStock();
};