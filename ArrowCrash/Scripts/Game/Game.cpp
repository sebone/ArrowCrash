#include "Game.h"


void Game::init() {
	
	initGameData();
	initUIComponents();

	pause = false;

	for (int i = 0; i < m_data->numOfPlayer; i++) {
		players.emplace_back(i, gameData);
	}
}

void Game::update() {

	if (pause) {
		if (Input::KeyP.clicked) pause = false;
		else if (Input::KeyR.clicked) changeScene(SceneName::Title);
		return;
	}

	if (Input::KeyP.clicked) pause = true;
	if (Input::KeyEnter.clicked) changeScene(SceneName::Result);
	for (auto& player : players) {
		player.update();
	}
}

void Game::draw() const {

	for (auto& player : players) {
		player.draw();
	}

	uiComp.draw();

	static const Texture white(Image(Window::Size(), Color(Palette::White, 150)));
	if (pause) {
		white.draw();
		PutText(L"press R to return Title").at(Window::Center());
	}
}




void Game::initGameData() {

	auto&& window = Window::Size();
	uiInfo.topUIHeight = window.y / 10;

	const int numOfPlayer = m_data->numOfPlayer;

	//�e�v���C���[�G���A�̃T�C�Y
	uiInfo.playerRegion = Size(Window::Width() / numOfPlayer, Window::Height() - uiInfo.topUIHeight);
	
	//�t�B�[���h��
	int fieldWidth = 0;
	switch (m_data->numOfPlayer)
	{
	case 2: fieldWidth = uiInfo.playerRegion.x * 2 / 5; break;
	case 3:	fieldWidth = uiInfo.playerRegion.x / 2; break;
	case 4:	fieldWidth = uiInfo.playerRegion.x * 3 / 5;	break;
	default: break;
	}

	//�u���b�N�̃T�C�Y
	gameData.blockSize = fieldWidth / constants::col_len;
	//���j�b�g�t���[��(�X�g�b�N�A���u���b�N�g)�̃T�C�Y
	uiInfo.unitFrameSize = gameData.blockSize * 4;
	//�t�B�[���h�̃T�C�Y
	uiInfo.fieldSize.x = fieldWidth;
	uiInfo.fieldSize.y = gameData.blockSize * constants::row_len;
	//�t�B�[���h�����̃}�[�W��
	uiInfo.fieldLeftMargin = (uiInfo.playerRegion.x - uiInfo.fieldSize.x) / 2;
	//�t�B�[���h�㑤�̃}�[�W��
	uiInfo.fieldTopMargin =
		numOfPlayer == 2 ?
		(uiInfo.playerRegion.y - uiInfo.fieldSize.y) / 3 :
		(uiInfo.playerRegion.y - uiInfo.fieldSize.y) / 2;

	for (int i = 0; i < numOfPlayer; i++) {
		//�e�v���C���[�t�B�[���h�̊�_
		gameData.stdPositions.emplace_back(uiInfo.playerRegion.x*i + uiInfo.fieldLeftMargin, uiInfo.topUIHeight + uiInfo.fieldTopMargin);
	}

}

void Game::initUIComponents() {

	auto&& window = Window::Size();
	uiComp.topUIBorder.set({ 0, uiInfo.topUIHeight }, { window.x, uiInfo.topUIHeight });
	
	for (int i = 1; i < m_data->numOfPlayer; i++) {
		uiComp.playerBorders.emplace_back(
			i*uiInfo.playerRegion.x, uiInfo.topUIHeight,
			i*uiInfo.playerRegion.x, window.y
		);
	}
	
	switch (int numOfPlayer = m_data->numOfPlayer)
	{
	case 2:
		for (int i = 0; i < numOfPlayer; i++) {
			//���j�b�g�t���[���̊Ԋu
			const int unitFrameInterval = gameData.blockSize / 2;
			//�X�g�b�N�g
			uiComp.stockFrames.emplace_back(
				uiInfo.playerRegion.x * i + uiInfo.fieldLeftMargin - uiInfo.unitFrameSize - unitFrameInterval,
				uiInfo.topUIHeight + uiInfo.fieldTopMargin,
				uiInfo.unitFrameSize,
				uiInfo.unitFrameSize
				);
			//�����j�b�g�g(���Ԃ͓K��)
			uiComp.nextUnitFrames.emplace_back();
			for (int j = 0; j < constants::numOfNextBlocks; j++) {
				uiComp.nextUnitFrames.at(i).emplace_back(
					uiInfo.playerRegion.x * i + uiInfo.fieldLeftMargin + uiInfo.fieldSize.x + unitFrameInterval,
					uiInfo.topUIHeight + uiInfo.fieldTopMargin + uiInfo.unitFrameSize * j,
					uiInfo.unitFrameSize,
					uiInfo.unitFrameSize
				);
			}
		}
		break;
	case 3:
	case 4:
		for (int i = 0; i < numOfPlayer; i++) {
			//���j�b�g�t���[���̊Ԋu
			const int unitFrameInterval = gameData.blockSize * 2;
			//�X�g�b�N�g
			uiComp.stockFrames.emplace_back(
				uiInfo.playerRegion.x * i + uiInfo.fieldLeftMargin,
				uiInfo.topUIHeight + uiInfo.fieldTopMargin - uiInfo.unitFrameSize - unitFrameInterval,
				uiInfo.unitFrameSize,
				uiInfo.unitFrameSize
			);
			//�����j�b�g�g(���Ԃ͓K��)
			uiComp.nextUnitFrames.emplace_back();
			for (int j = 0; j < constants::numOfNextBlocks; j++) {
				uiComp.nextUnitFrames.at(i).emplace_back(
					uiInfo.playerRegion.x * i + uiInfo.fieldLeftMargin + uiInfo.fieldSize.x - uiInfo.unitFrameSize,
					uiInfo.topUIHeight + uiInfo.fieldTopMargin - uiInfo.unitFrameSize * (j+1) - unitFrameInterval,
					uiInfo.unitFrameSize,
					uiInfo.unitFrameSize
				);
			}
		}
		break;
	default:
		break;
	}
}


void Game::UIComponents::draw() const {

	topUIBorder.draw();
	
	for (const auto& line : playerBorders) {
		line.draw();
	}
	
	for (const auto& stockFrame : stockFrames) {
		stockFrame.drawFrame();
	}
	
	for (const auto& arr : nextUnitFrames) {
		for (const auto& nextUnitFrame : arr) {
			nextUnitFrame.drawFrame();
		}
	}
}