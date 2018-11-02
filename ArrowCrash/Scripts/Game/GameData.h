#pragma once
#include <Siv3d.hpp>

struct GameData {
	std::vector<Point> stdPositions; //�e�v���C���[�̃t�B�[���h�̊�_
	std::vector<std::vector<Rect>>* nextUnitFrames;
	std::vector<Rect>* stockFrames;
};