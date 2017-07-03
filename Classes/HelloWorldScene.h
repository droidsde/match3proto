#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Candy.h"
#include "defined.h"

class Candy;

class HelloWorld : public cocos2d::Layer
{
private:
	float		m_scaleFactor;
	int			m_offsetX;
	int			m_offsetY;
	std::vector<Candy**>	m_boardRows;


	void		InitBoard();
	void		ReFilledBoard();
	Candy*		GetCandyIsChoosed();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void		updateGame(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
