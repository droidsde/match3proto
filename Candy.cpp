#include "Candy.h"

Candy* Candy::createCandyWithFileName(char *fileName)
{
	auto sprite = new Candy;
	if (sprite && sprite->initWithFile(fileName))
	{
		//sprite->setVisible(false);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool		Candy::IsSelected(const Point& p)
{
	if (this->getBoundingBox().containsPoint(p))
	{
		//CCLOG("Candy have touched !!");
		return true;
	}
	return false;
}

void		Candy::DisAppear()
{
	auto action = ScaleBy::create(1.0f, 0.1f);
	auto seq = Sequence::create(action, nullptr);
	this->runAction(seq);
}

void		Candy::Appear()
{
	auto action = FadeIn::create(1.0f);
	this->runAction(action);
	this->stopAction(action);
}