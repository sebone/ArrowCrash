#pragma once
#include "BlockUnitManager.h"

class Player {
private:
	const int number; //�v���C���[�ԍ�
	const GameData& gameData;
	int counter;

	// �ꊇ�Ŕ������邽�߃t�B�[���h��̑S�Ă�ArrowBlock�ւ̎Q�Ƃ������Ă���
	std::vector<std::weak_ptr<ArrowBlock>> arrowBlocks;
	std::shared_ptr<Field> field;
	BlockUnitManager mngr;

public:
	Player(int player_num ,const GameData& gameData);
	~Player() = default;

	void update();
	void draw() const;

	void explode();
};