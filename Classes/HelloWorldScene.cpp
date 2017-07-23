#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();

	auto layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	cd_pink = Candy::createCandyWithFileName("candy/swirl_pink.png");
	int offsetX = (int)cd_pink->getBoundingBox().size.width + 15;
	int offsetY = (int)cd_pink->getBoundingBox().size.height + 15;
	/// test

	cd_pink->setPosition(Vec2(visibleSize.width *2/ 5, visibleSize.height / 2));
	cd_pink->m_value = 5;
	cd_pink->m_pos = Position(1, 1);
	this->addChild(cd_pink);

	cd_red = Candy::createCandyWithFileName("candy/jelly_purple.png");
	cd_red->setPosition(Vec2(visibleSize.width * 3 / 5, visibleSize.height / 2));
	cd_red->m_value = 3;
	cd_red->m_pos = Position(2, 2);
	this->addChild(cd_red, Z_INDEX_CANDY);

	m_posPink = cd_pink->getPosition();
	m_posRed = cd_red->getPosition();

	/// end - test
	m_gameMgr = GameMgr::GetInstance();
	m_gameMgr->SetOffsetX(offsetX);
	m_gameMgr->SetOffsetY(offsetY);

	/////////////////////////////
	// 3. add your codes below...
	//m_gameMgr->InitBoard(this);

	auto _listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	//schedule(schedule_selector(HelloWorld::GameUpdate));
	schedule(schedule_selector(HelloWorld::TestUpdate));
	return true;
}

void		HelloWorld::GameUpdate(float dt)
{
	//m_gameMgr->CheckAllMatch3();
	if (m_gameMgr->IsPossibleSwap())
	{
		if (m_gameMgr->IsSwappable())
		{
			CCLOG("Swapped !");
			m_gameMgr->Swap();
			m_gameMgr->CheckMatch3AfterSwap();
			CCLOG("NumOfChainAfterSwap = %d", m_gameMgr->GetNumOfChainAfterSwap());
			if (m_gameMgr->GetNumOfChainAfterSwap() == 0)
			{
				m_gameMgr->UndoSwap();
				CCLOG("Undo Swappp !!!");
			}
			else
			{
				m_gameMgr->ClearChainAfterSwap();
			}
		}
		else
		{
			CCLOG("Cannot Swapppppp !!!");
		}
		m_gameMgr->ResetAfterSwap();
		//int currChain = m_gameMgr->GetNumOfChains();
		//m_gameMgr->CheckMatch3AfterSwap();
		//CCLOG("num of chain: %d", currChain);
		//	if (m_gameMgr->GetNumOfChains() == currChain)
		{
			//CCLOG("Undo Swap !");
			//m_gameMgr->UndoSwap();
		}
	}


	//m_gameMgr->CheckAllMatch3();

	//m_gameMgr->RemoveAllMatch3(this);

	//m_gameMgr->UpScore();

	//m_gameMgr->ReFillBoard(this);
	//m_gameMgr->TestReFillBoard(this);

	//m_gameMgr->RemoveAllChain();
	///// reset 
	//m_gameMgr->ResetAfterSwap();
}


void HelloWorld::TestUpdate(float dt)
{
	
	if (m_pinkSelected && m_redSelected)
	{
		CCLOG("---------------------------");
		CCLOG("before pos Pink: %f, %f", cd_red->getPositionX(), cd_red->getPositionY());
		CCLOG("before pos Red: %f, %f", cd_pink->getPositionX(), cd_pink->getPositionY());
		

		
		auto actionPink = MoveTo::create(0.4f, m_posRed);
		auto actionRed = MoveTo::create(0.4f, m_posPink);

		cd_pink->runAction(actionPink);
		cd_pink->runAction(actionPink);
		//cd_pink->stopAction(actionPink);

		cd_red->runAction(actionRed);
		cd_red->runAction(actionRed);
		//cd_red->stopAction(actionRed);
		/// swap pointer
		auto tempPtr1 = cd_pink;
		cd_pink = cd_red;
		cd_red = tempPtr1;

		CCLOG("after pos Pink: %f, %f", cd_red->getPositionX(), cd_red->getPositionY());
		CCLOG("after pos Red: %f, %f", cd_pink->getPositionX(), cd_pink->getPositionY());

		CCLOG("---------------------------\n");
		CCLOG("-------------Undo Swap --------\n");
		auto action1 = MoveTo::create(0.4f, cd_pink->getPosition());
		auto action2 = MoveTo::create(0.4f, cd_red->getPosition());

		cd_pink->runAction(action2);
		cd_red->runAction(action1);

		/// swap pointer
		auto tempPtr2 = cd_pink;
		cd_pink = cd_red;
		cd_red = tempPtr2;

		CCLOG("after pos Pink: %f, %f", cd_red->getPositionX(), cd_red->getPositionY());
		CCLOG("after pos Red: %f, %f", cd_pink->getPositionX(), cd_pink->getPositionY());

		m_pinkSelected = false;
		m_redSelected = false;

		CCLOG("---------------------------\n");

		
	}

}

void		HelloWorld::menuCloseCallback(Ref* pSender)
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

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	/// tesst
	if (cd_pink->getBoundingBox().containsPoint(touch->getLocation()))
	{
		m_pinkSelected = true;
		return true;
	}
	else
		m_pinkSelected = false;
	if (cd_red->getBoundingBox().containsPoint(touch->getLocation()))
	{
		m_redSelected = true;
		return true;
	}
	else
		m_redSelected = false;

	/// end-test
	//m_pointClicked = touch->getLocation();
	//m_gameMgr->CheckAllSprite(m_pointClicked);
	return true;


}

void HelloWorld::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
	m_pointClicked = Vec2(0, 0);
	//CCLOG("Touch End !");
}

void HelloWorld::onTouchMoved(cocos2d::Touch*, cocos2d::Event*)
{
	//CCLOG("Touch Moved !");
}
