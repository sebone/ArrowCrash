#pragma once
#include <Siv3d.hpp>

//Game����e�N���X�ɓn�����
struct GameData {
	std::vector<Point> stdPositions; //�e�v���C���[�̃t�B�[���h�̊�_
	std::vector<std::vector<Rect>> nextUnitFrames;
	std::vector<Rect> stockFrames;
	Size playerRegion;
	Size fieldSize;
};