#pragma once

#include <iostream>
#include "SimpleAudioEngine.h"
#include "defined.h"
#include "Candy.h"

namespace gamemanager {
	// random from 1 - 39
	enum Candy
	{
		CANDY_BEAN_BLUE = 1, // 40%
		CANDY_BEAN_GREEN = 5, // 50%
		CANDY_BEAN_ORANGE = 10, // 30%
		CANDY_BEAN_PINK = 13, // 20%
		CANDY_BEAN_PURPLE = 15, // 20%
		CANDY_BEAN_RED = 17, // 60%
		CANDY_BEAN_WHITE = 23, // 20%
		CANDY_BEAN_YELLOW = 25, // 60%

		CANDY_CANE = 31, // 20%			
		CANDY_CORN = 33, // 40%
		CANDY_HUMBUG = 37, // 30%
	};
};
class GameManager {
public:
	static GameManager* GetInstance();
	void		InitBoard();
	void		ReFilledBoard();
	void		Swap();
			
	void lateInit();
	void playBackgroundMusic();
	void playEffect(const char *nameSound);
	float		GetScaleFactor();
	void		SetScaleFactor(float fac);

private:
	GameManager() {};
	GameManager(GameManager const&) {};
	GameManager& operator=(GameManager const&) {};
	std::vector<Candy**> m_board[BOARD_HEIGHT];
	static GameManager* m_pInstance;
	float	m_scaleFactor;

};

