#pragma once

#include "cocos2d.h"
#include "defined.h"


USING_NS_CC;

class Candy : public cocos2d::Sprite {

public:
	TypeOfCandy		m_type;

	static Candy* createCandyWithFileName(char *fileName);

	Candy() 
	{
		m_type = TypeOfCandy::TYPE_UNKNOW_CANDY;
	};

};

