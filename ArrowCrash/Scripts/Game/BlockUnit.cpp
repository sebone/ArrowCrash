#include "BlockUnit.h"

BlockUnit::BlockUnit(const Point& point_, const Point& stdPos_, std::vector<std::weak_ptr<ArrowBlock>>& arrowBlocks_, Field& field_)
	:field(field_),
	point(point_),
	predictedPoint(point_),
	settled(false),
	timer(true),
	stdPos(stdPos_),
	arrowBlocks(arrowBlocks_),
	type(static_cast<UnitType>(Random<int>(0, 6)))
{
	auto& pattern = unitPatterns[(int)type];
	
	//ArrowBlock生成(分かり辛くてごめんやで)
	int arrowOrder;
	arrowOrder = Random() < arrowProbability ? Random<int>(0, countNumOfBlock(pattern) - 1) : -1; //-1は無効値

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pattern[i][j]) {
				if (arrowOrder-- == 0) {
					auto ptr = std::make_shared<ArrowBlock>(point.movedBy(i, j), stdPos, (ExplosionDirection)Random<int>(0, 7), field);
					geometry[i][j] = ptr;
					arrowBlocks.emplace_back(ptr);
				}
				else
					geometry[i][j] = std::make_shared<NormalBlock>(point.movedBy(i, j), stdPos, type);
			}
			else {
				geometry[i][j] = nullptr;
			}
		}
	}
}

const double BlockUnit::arrowProbability = 0.80;


bool BlockUnit::checkCollision(const Point& point_) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (field.getAt(point_.movedBy(i, j)) && geometry[i][j])
				return true;
		}
	}
	return false;
}

void BlockUnit::settle() {

	for (auto&& arr : geometry) {
		for (auto&& block : arr) {
			if (block) {
				block->setSettled();
				field.setBlockAt(std::move(block), block->getPoint());
			}
		}
	}
	settled = true;
}

int BlockUnit::countNumOfBlock(const bool pattern[4][4]) const {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pattern[i][j]) count++;
		}
	}
	return count;
}


void BlockUnit::update() {

	if (timer.ms() > 1500)
		move(MoveDirection::Down);
}

void BlockUnit::draw() const {

	const Point predictedPos(stdPos.movedBy(predictedPoint.y * Block::blockSize, predictedPoint.x * Block::blockSize));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (geometry[i][j]) {
				geometry[i][j]->draw();
				Rect(predictedPos.movedBy(j*Block::blockSize, i*Block::blockSize), Block::blockSize).drawFrame(Block::blockSize / 10, 0.0);
			}
		}
	}

}

void BlockUnit::draw(const Point& pos, double scale) const {
	
	const int scaledSize = Block::blockSize * scale;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (geometry[i][j]) {
				geometry[i][j]->draw(pos.movedBy(scaledSize*Point(j,i)), scale);
			}
		}
	}
}

void BlockUnit::fallImmediately() {
	point.set(predictedPoint);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (geometry[i][j])
				geometry[i][j]->setPoint(point.movedBy(i, j));
		}
	}
	settle();
}

void BlockUnit::move(MoveDirection mov) {
	
	if (mov == MoveDirection::Down) {
		if (checkCollision(point.movedBy(1, 0))) {
			settle();
			return;
		}
		point.moveBy(1, 0);
		timer.restart();
	}
	else {
		int direction = mov == MoveDirection::Left ? -1 : 1;
		if (checkCollision(point.movedBy(0, direction))) return;
		point.moveBy(0, direction);
		predict();
	}
	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (geometry[i][j])
				geometry[i][j]->setPoint(point.movedBy(i, j));
		}
	}

}

void BlockUnit::rotate(RotateDirection rot) {

	auto prev = geometry;
	
	if (rot == RotateDirection::Right) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				geometry[j][3 - i] = prev[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				geometry[3 - j][i] = prev[i][j];
			}
		}
	}

	if (checkCollision(point)) {
		geometry = prev;
		return;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (geometry[i][j]) {
				geometry[i][j]->setPoint(point.movedBy(i, j));
				geometry[i][j]->rotate(rot);
			}
		}
	}
	predict();

}

void BlockUnit::predict() {
	predictedPoint.set(point);
	while (!checkCollision(predictedPoint)) {
		predictedPoint.moveBy(1, 0);
	}
	predictedPoint.moveBy(-1, 0); //ここダサい
}

void BlockUnit::resetPoint() {
	point.set(0, constants::col_len / 2 - 2);
}

bool BlockUnit::cannotSettle() {
	Point point_(point.movedBy(-4, 0));
	while (!checkCollision(point_)) {
		point_.moveBy(1, 0);
	}
	point_.moveBy(-1, 0); //ここダサい

	if (point_.x < 0) return true;
	return false;
}
