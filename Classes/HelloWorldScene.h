#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Candy.h"
#include "defined.h"

class Candy;

class HelloWorld : public cocos2d::Layer
{
private:
	int			m_offsetX;
	int			m_offsetY;

	Vec2		m_pointClicked;
	
	int			m_botLeftX;
	int			m_botLeftY;
	
	Candy*		m_firstSelected;
	Candy*		m_secondSelected;
	Candy*		m_candySelect;

	Point2D		m_index1st;
	Point2D		m_index2nd;

	std::vector<Candy**>	m_boardRows;


	void		InitBoard();
	void		ReFilledBoard();
	Candy*		GetCandyIsChoosed();
	bool		IsSelected(Candy *candy);
	void		CheckAllSprite();
	bool		IsSwappable(const Point2D &indexOf1st, const Point2D &indexOf2nd);
	void		Swap(Candy *& candy1, Candy *& candy2);
	void		RemoveMatch3();
	bool		IsMatch3();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void		updateGame(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	bool		onTouchBegan(Touch *touch, Event *event);
	void		onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	void		onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
