#pragma once

#include "cocos2d.h"
#include <iostream>
#include "defined.h"


USING_NS_CC;

class Candy : public cocos2d::Sprite {
private:

public:
	int			m_type;
	int			m_score;
	Coord		m_coord;	// tọa độ theo trục x và y
	
	/// set this flag to true if obj have been done FadeIn action, other wise set to false.
	bool		m_isAppear;
	bool		m_isFallDown;
	bool		m_isMoving;

	static Candy* createCandyWithFileName(char *fileName);
	void		Init(Coord coord, int type);
	static Candy*		InitWithType(int);
	void		DisAppear();
	void		Appear();
	void		FallDown(cocos2d::Vec2& p);
	bool		IsSelected(const Point& p);
	void		SelectAnimation();

	Candy();
	~Candy() {};
};

