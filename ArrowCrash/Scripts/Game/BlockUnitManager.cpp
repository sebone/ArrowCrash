#include "BlockUnitManager.h"


BlockUnitManager::BlockUnitManager(Field& field_, std::vector<std::weak_ptr<ArrowBlock>>& arrowBlocks_, const GameData& gameData, int player_num)
	:field(field_),
	arrowBlocks(arrowBlocks_),
	stdPos(gameData.stdPositions.at(player_num)),
	blockSize(gameData.blockSize),
	hasExchanged(false),
	nextUnitFramePos(gameData.nextUnitFramePos.at(player_num)),
	stockFramePos(gameData.stockFramePos.at(player_num)),
	currentUnit(new BlockUnit(Point(0, constants::col_len / 2 - 2), stdPos, blockSize, arrowBlocks, field)),
	stock(nullptr)
{
	for (int i = 0; i < 2; i++) {
		generate();
	}
}

void BlockUnitManager::generate() {
	nextUnits.emplace_back(new BlockUnit(Point(0, constants::col_len / 2 - 2), stdPos, blockSize, arrowBlocks, field));
}

void BlockUnitManager::update() {
	currentUnit->update();
	if (Item != nullptr) Item->update();
	if (currentUnit->isSettled()) {

		if (ItemBlock::CheckItem() == ItemCondition::NotExist) {
			Item = std::shared_ptr<Unit>(new ItemUnit(Point(0, Random<int>(0, constants::col_len - 4)), stdPos, blockSize, field));
			currentUnit = Item;
			ItemBlock::Generate();
		}
		else {
			currentUnit = nextUnits.front();
			nextUnits.pop_front();
			generate();
			currentUnit->predict();
		}
		hasExchanged = false;
	}
}

void BlockUnitManager::draw() const {
	currentUnit->draw();
	if (Item != nullptr) Item->draw();
	int counter = 0; //vector(nextUnitsFrameInfo)�p
	for (auto&& unit : nextUnits) {
		unit->draw(nextUnitFramePos.at(counter++), 1.0);
	}
	if (stock) stock->draw(stockFramePos, 1.0);
}

void BlockUnitManager::exchangeStock() {

	if (hasExchanged) return;
	
	hasExchanged = true;

	if (stock) {
		currentUnit.swap(stock);
		currentUnit->resetPoint();
		currentUnit->predict();
	}
	else {
		stock = std::move(currentUnit);
		currentUnit = nextUnits.front();
		nextUnits.pop_front();

		generate();
		currentUnit->predict();
	}
}