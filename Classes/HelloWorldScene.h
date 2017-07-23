#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Candy.h"
#include "defined.h"
#include <iostream>
#include "Chain.h"
#include "GameMgr.h"


class Candy;
class Chain;


class HelloWorld : public cocos2d::Layer
{
private:
	/// member
	GameMgr*	m_gameMgr;
	Vec2		m_pointClicked;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void	menuCloseCallback(cocos2d::Ref* pSender);

	bool		onTouchBegan(Touch *touch, Event *event);
	void		onTouchEnded(Touch*, Event*);
	void		onTouchMoved(Touch*, Event*);

	void		GameUpdate(float dt);
	Candy*		cd_pink;
	Candy*		cd_red;

	bool		m_pinkSelected, m_redSelected;
	Vec2		m_posPink, m_posRed;
	void		TestUpdate(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
