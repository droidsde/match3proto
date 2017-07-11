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

Candy::Candy()
{
	m_type = TypeOfCandy::TYPE_UNKNOW_CANDY;
}

Candy::~Candy()
{

}
