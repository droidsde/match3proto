#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Candy : public cocos2d::Sprite {

public:
	static Candy* createCandyWithFileName(char *fileName);
	Candy() {};

};

