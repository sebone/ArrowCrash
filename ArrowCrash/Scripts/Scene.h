#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>


//�V�[�����ׂ��ŕK�v�ȏ��
struct SharedData {
	int numOfPlayer; //�v���C���[��
	std::vector<int> scores; //�e�v���C���[�̃X�R�A
};


enum class SceneName {
	Title,
	Game,
	Result
};


using MySceneManager = SceneManager<SceneName, SharedData>;
using Scene = MySceneManager::Scene;