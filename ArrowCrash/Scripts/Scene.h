#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>


//�V�[�����ׂ��ŕK�v�ȏ��
struct SharedData {
	//�Q�[���̌��ʂƂ������U���g�Ŏg�������Ƃ��Ƃ�
	int player_num;
	int cellSize = 20; //�Ƃ肠����
};


enum class SceneName {
	Title,
	Game
};


using MySceneManager = SceneManager<SceneName, SharedData>;
using Scene = MySceneManager::Scene;