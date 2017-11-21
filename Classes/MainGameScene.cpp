#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene* MainGame::createScene()
{
	auto scene = Scene::create();

	auto layer = MainGame::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGame::menuCloseCallback, this));

	closeItem->setPosition(Vec2(m_origin.x + m_visibleSize.width - closeItem->getContentSize().width / 2,
		m_origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	auto _listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(MainGame::onTouchEnded, this);
	_listener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	m_gameMgr = GameMgr::GetInstance();
	m_gameMgr->SetupLabel(this);
#if MANUAL_SETUP
	m_gameMgr->ClearBoardType();
	m_gameMgr->SetUpBoardType("../board2.txt");
	m_gameMgr->SetUpBoardManual(this, "");
#else
	m_gameMgr->SetUpBoard(this);
#endif
	
	schedule(CC_SCHEDULE_SELECTOR(MainGame::UpdateGame));
	return true;
}

void		MainGame::UpdateGame(float dt)
{
	m_gameMgr->Update(dt);
}

void		MainGame::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

bool		MainGame::onTouchBegan(Touch *touch, Event *event)
{
	if (m_gameMgr->m_isSwaping)
	{
		CCLOG("--- giap: Touch is Disable ----");
		return false;
	}
	m_gameMgr->CheckAllSprite(touch->getLocation());

	return true;
}

void		MainGame::onTouchEnded(Touch *touch, Event *event)
{

}

void		MainGame::onTouchMoved(Touch *touch, Event *event)
{

}
