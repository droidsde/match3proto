#pragma once

#include "cocos2d.h"
#include <iostream>
#include "defined.h"


USING_NS_CC;

class Candy : public cocos2d::Sprite {

public:
	int			m_value;
	Position	m_pos;


	static Candy* createCandyWithFileName(char *fileName);
	void		DisAppear();
	void		Appear();
	bool		IsSelected(const Point& p);
	Candy() {};
	~Candy() {};
};

