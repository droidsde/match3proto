#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "defined.h"
#include "GameManager.h"
#include "Candy.h"


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(800, 480);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1280, 720);


void HelloWorld::ReFilledBoard()
{

}


void HelloWorld::InitBoard()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::srand(seed);
	int random = 0;
	int topLeftX = 150;
	int topLeftY = 600;
	CCLOG("m_offsetX = %d, m_offsetY = %d", m_offsetX, m_offsetY);
	// init container
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		Candy** row = new Candy*[BOARD_WIDTH];
		m_boardRows.push_back(row);
	}
	for (int i = 0; i < BOARD_HEIGHT; i++) // 8
	{
		for (int j = 0; j < BOARD_WIDTH; j++) // 5
		{
			//CCLOG("i = %d, j = %d", i, j);

			random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
			if (random <= 4)	//bean blue
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_blue.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 9) //bean green
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_green.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 12) //bean orange
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_orange.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 14) //bean pink
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_pink.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 16) //bean purple
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_purple.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 22) //bean red
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_red.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 24) //bean white
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_white.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 30) //bean yellow
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_yellow.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 32) //candy cane
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/candycane.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 36) //candy corn
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/candycorn.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else  //candy humbug
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/candyhumbug.png");
				m_boardRows[i][j]->setPosition(Point(topLeftX + j*m_offsetX, topLeftY - i*m_offsetY));
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
		}
	}

}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto director = Director::getInstance();
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
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    auto background = Sprite::create("background.png");

    // position the sprite on the center of the screen
	background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	auto glview = director->getOpenGLView();
	auto frameSize = glview->getFrameSize();
	
	// if the frame's height is larger than the height of medium size.
	if (frameSize.height > mediumResolutionSize.height)
	{
		director->setContentScaleFactor(largeResolutionSize.height / designResolutionSize.height);
		m_scaleFactor = largeResolutionSize.height / designResolutionSize.height;
	}
	// if the frame's height is larger than the height of small size.
	else if (frameSize.height > smallResolutionSize.height)
	{
		director->setContentScaleFactor(mediumResolutionSize.height / designResolutionSize.height);
		m_scaleFactor = mediumResolutionSize.height / designResolutionSize.height;
	}
	// if the frame's height is smaller than the height of medium size.
	else
	{
		director->setContentScaleFactor(smallResolutionSize.height / designResolutionSize.height);
		m_scaleFactor = smallResolutionSize.height / designResolutionSize.height;
	}
    // add the sprite as a child to this layer
    //this->addChild(background, Z_INDEX_BG);
	CCLOG("scale factor: %f", m_scaleFactor);
	auto cd_blue = Candy::createCandyWithFileName("candy/bean_blue.png");
	m_offsetX = (int)cd_blue->getBoundingBox().size.width + 15;
	m_offsetY = (int)cd_blue->getBoundingBox().size.height + 15;
	
	// init board
	InitBoard();
	

    return true;
}


void HelloWorld::updateGame(float dt)
{
	CCLOG("delta time: %f", dt);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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
