#include "BlockGenerator.h"


BlockGenerator::BlockGenerator(Field& field_, std::vector<std::weak_ptr<ArrowBlock>>& arrowBlocks_)
	:field(field_),
	arrowBlocks(arrowBlocks_)
{}

void BlockGenerator::generate() {
	//arrowBlockを作るときarrowBlocksに追加する
}

void BlockGenerator::update() {

}