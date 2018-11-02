#include "Block.h"


//Block

Block::Block(const Point& point_, const Point& stdPos_)
	:destroyed(false),
	stdPos(stdPos_),
	point(point_),
	rect(stdPos.movedBy(Point(point.y, point.x)*blockSize), blockSize),
	settled(false)
{
}

int Block::blockSize = 0;

void Block::setPoint(const Point& point_) {
	point.set(point_);
	rect.setPos(stdPos.movedBy(Point(point.y, point.x)*blockSize));
}

void Block::destroy() {
	const int explosionCellSize = TextureAsset(L"explosion").height;
	ymds::EffectGenerator::addLinkedImage(L"explosion", explosionCellSize, rect.pos, double(blockSize)/explosionCellSize, 0.2);
	destroyed = true;
}


//NormalBlock

NormalBlock::NormalBlock(const Point& point_, const Point& pos, UnitType type_)
	:Block(point_, pos),
	type(type_)
{}

void NormalBlock::draw() const {
	rect(TextureAsset(L"block")(64 * (int)type, 0, 64, 64)).draw();
}

void NormalBlock::draw(const Point& pos, double scale) const {
	rect.scaled(scale).setPos(pos)(TextureAsset(L"block")(64 * (int)type, 0, 64, 64)).draw();
}


//ArrowBlock

ArrowBlock::ArrowBlock(const Point& point_, const Point& pos, ExplosionDirection dir, Explodable& field_)
	:Block(point_, pos),
	direction(dir),
	field(field_)
{}

int ArrowBlock::explode() {
	destroy();
	return field.explode(point, direction) + 1; //自分の分を足している
}

void ArrowBlock::rotate(RotateDirection rot) {
	//矢印の向きを変更
	direction = ExplosionDirection((8 + ((int)direction + (rot == RotateDirection::Right ? 2 : -2))) % 8);
}

void ArrowBlock::draw() const {
	rect(TextureAsset(L"arrow")(50 * (int)direction, 0, 50, 50)).draw();
}

void ArrowBlock::draw(const Point& pos, double scale) const {
	rect.scaled(scale).setPos(pos)(TextureAsset(L"arrow")(50 * (int)direction, 0, 50, 50)).draw();
}



//ItemBlock

ItemBlock::ItemBlock(const Point& point_, const Point& stdPos, const PartPlace Part_)
	:Block(point_, stdPos),
	Part(Part_)
{}

void ItemBlock::draw() const {
	switch (Part) {
	case PartPlace::UpLeft:
	case PartPlace::UpRight:
	case PartPlace::DownLeft:
//	case PartPlace::DownRight: rect(TextureAsset(L"block")).draw(); break;
	case PartPlace::DownRight: rect.draw(Color(135, 206, 250)); break;
	default: break;
	}
}

void ItemBlock::draw(const Point& pos, double scale) const {
	rect.scaled(scale).setPos(pos)(TextureAsset(L"block")).draw();
}


//InvincibleBlock

InvincibleBlock::InvincibleBlock(const Point& point_, const Point& pos)
	:Block(point_, pos)
{
	setSettled(); //もうちょっと良い感じに書けそう
}

void InvincibleBlock::draw() const {}