#include "MenuSettingsScene.h"

USING_NS_CC;

cocos2d::Scene * MenuSettings::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuSettings::create();

	scene->addChild(layer);

	return scene;
}

bool MenuSettings::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_labelBack = Label::createWithTTF(TEXT_BACK, FONT_LABEL_PATH, FONT_SIZE);
	m_labelBack->setColor(Color3B::ORANGE);
	auto itemBack = MenuItemLabel::create(m_labelBack, CC_CALLBACK_1(MenuSettings::menuBackCallback, this));
	itemBack->setPosition(Vec2(origin.x + m_labelBack->getContentSize().width, origin.y + visibleSize.height - m_labelBack->getContentSize().height));

	m_labelSave = Label::createWithTTF(TEXT_SAVE, FONT_LABEL_PATH, FONT_SIZE);
	m_labelSave->setColor(Color3B::GREEN);
	auto itemSave = MenuItemLabel::create(m_labelSave, CC_CALLBACK_1(MenuSettings::menuSaveCallback, this));
	itemSave->setPosition(Vec2(origin.x + visibleSize.width - m_labelSave->getContentSize().width, origin.y + m_labelSave->getContentSize().height));

	auto menuItem = Menu::create(itemBack, itemSave, NULL);
	menuItem->setPosition(Vec2::ZERO);
	this->addChild(menuItem, 1);

	return true;
}

void MenuSettings::menuBackCallback(cocos2d::Ref * pSender)
{
	// back without save settings
	Director::getInstance()->popScene();
	CCLOG("--- Back !");
}

void MenuSettings::menuSaveCallback(cocos2d::Ref * pSender)
{
	CCLOG("--- Save !");
	// save any setting & back
	Director::getInstance()->popScene();
}

bool MenuSettings::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return false;
}

void MenuSettings::onTouchEnded(cocos2d::Touch *, cocos2d::Event *)
{
}
