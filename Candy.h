#pragma once

#include "cocos2d.h"
#include "defined.h"


USING_NS_CC;

class Candy : public cocos2d::Sprite {

public:
	TypeOfCandy		m_type;
	Point2D			m_position;
	static Candy* createCandyWithFileName(char *fileName);

	Candy();
	~Candy();

};

