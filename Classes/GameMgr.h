#pragma once
#include "Chain.h"
#include "Candy.h"
#include <vector>

class Chain;
class Candy;

class GameMgr {
public:
	static GameMgr* GetInstance();

	void	InitBoard(cocos2d::Layer *layer);

	void	PrintBoard();
	void	CheckMatchVertical(Candy* currCandy, bool isAfterSwap = false);
	void	CheckMatchHorizontal(Candy* currCandy, bool isAfterSwap = false);
	void	CheckAllMatch3();
	void	CheckMatch3AfterSwap();

	/// for manual init
	void	InitBoardManual(const char* fileName);
	void	PrintBoard(int width, int height);
	void	CheckMatchVertical(Candy* currCandy, int width, int height);
	void	CheckMatchHorizontal(Candy* currCandy, int width, int height);
	void	CheckAllMatch3(int width, int height);

	void	CheckAllSprite(Vec2 &p);
	bool	IsSwappable();
	void	Swap();
	void	UndoSwap();
	void	ResetAfterSwap();
	void	ClearChainAfterSwap();
	void	PrintAllMatch3();

	void	RemoveAllMatch3(cocos2d::Layer *layer);
	void	ReFillBoard(cocos2d::Layer *layer);
	void	TestReFillBoard(cocos2d::Layer *layer);
	void	RemoveAllChain();
	void	UpScore();

	bool	IsPossibleSwap();
	/// get & set
	int		GetWidth();
	int		GetHeight();

	int		GetOffsetX();
	int		GetOffsetY();

	void	SetOffsetX(int offset);
	void	SetOffsetY(int offset);

	int		GetNumOfAllChains();
	int		GetNumOfChainAfterSwap();
	/// member

	Candy*			m_firstObj;
	Candy*			m_secondObj;

	Position		m_index1stOld;
	Position		m_index2ndOld;
	Vec2			m_oldPos1, m_oldPos2;
private:
	Candy***		m_board;
	std::vector<Chain*>		m_allChains;
	std::vector<Chain*>		m_chainAfterSwap;
	int		m_width, m_height;
	int		m_offsetX, m_offsetY;

	static GameMgr* m_pInstance;
	GameMgr()
	{
		m_firstObj = nullptr;
		m_secondObj = nullptr;
	};
	GameMgr(const GameMgr&) {};
	GameMgr& operator=(const GameMgr&) {};
};
