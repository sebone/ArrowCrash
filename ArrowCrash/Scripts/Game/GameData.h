#pragma once
#include <Siv3d.hpp>

struct GameData {
	std::vector<Point> stdPositions; //�e�v���C���[�̃t�B�[���h�̊�_
	std::vector<std::vector<Point>> nextUnitFramePos;
	std::vector<Point> stockFramePos;
};