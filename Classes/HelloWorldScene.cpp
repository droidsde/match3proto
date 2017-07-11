#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "defined.h"
#include "Candy.h"


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(800, 480);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1280, 720);


void HelloWorld::ReFilledBoard()
{

}


Candy* HelloWorld::GetCandyIsChoosed()
{
	return m_firstSelected;
}


bool HelloWorld::IsSelected(Candy *candy)
{
	if (candy->getBoundingBox().containsPoint(m_pointClicked))
	{
		//CCLOG("Candy have touched !!");
		return true;
	}
	return false;
}


void HelloWorld::CheckAllSprite()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (IsSelected(m_boardRows[i][j]))
			{
				CCLOG("Candy: i = %d, j = %d ", i + 1, j + 1);
				if (m_firstSelected == nullptr)
				{
					m_firstSelected = m_boardRows[i][j];
					m_index1st = Point2D(i, j);
				}
				else
				{
					m_secondSelected = m_boardRows[i][j];
					m_index2nd = Point2D(i, j);
				}
				break;
			}
		}
	}
}


bool HelloWorld::IsSwappable(const Point2D &indexOf1st, const Point2D &indexOf2nd)
{
	/// same x
	if (indexOf1st.m_x == indexOf2nd.m_x)
	{
		if (indexOf1st.m_y == (indexOf2nd.m_y + 1) || (indexOf1st.m_y + 1) == indexOf2nd.m_y)
		{
			return true;
		}
	}

	/// same y
	if (indexOf1st.m_y == indexOf2nd.m_y)
	{
		if (indexOf1st.m_x == (indexOf2nd.m_x + 1) || (indexOf1st.m_x + 1) == indexOf2nd.m_x)
		{
			return true;
		}
	}
	return false;
}


void HelloWorld::Swap(Candy* candy1, Candy* candy2)
{
	/// swap position
	auto pos1st = candy1->getPosition();
	auto pos2nd = candy2->getPosition();

	auto actionMove = MoveTo::create(0.3f, pos2nd);
	candy1->runAction(actionMove);

	actionMove = MoveTo::create(0.3f, pos1st);
	candy2->runAction(actionMove);

	auto temp = candy1;
	candy1 = candy2;
	candy2 = temp;

	/// swap pointer in board
	m_boardRows[m_index1st.m_x][m_index1st.m_y] = candy1;
	m_boardRows[m_index2nd.m_x][m_index2nd.m_y] = candy2;

}

//////////////////////////////////////////////////////////////////////////
/// check 3 candy after swap.
/// return number of match 3 in board.
int HelloWorld::GetCountIsMatch3()
{
	int countVertical = 1;
	int countHorizon = 1;

	Point2D		p1 = m_index2nd;
	Point2D		p2 = m_index2nd;
	TypeOfCandy type = m_candySelect->m_type;
	/// phai check ca 2 candy, moi candy
	/// check for vertical-up
	int y = 1;
	//while (m_boardRows[p1.m_x][p1.m_y + y]->m_type == type)
	{
		countVertical += 1;
		y += 1;
		if (y == BOARD_HEIGHT)
		{
			//break;
		}
	}
	/// check for vertical-down
	y = 1;
	//while (m_boardRows[p2.m_x][p2.m_y - y]->m_type == type)
	{
		countVertical += 1;
		y += 1;
		if (y < 0)
		{
			//break;
		}
	}

	return false;
}


void HelloWorld::printAllPos()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			CCLOG("i = %d, j = %d", i, j);
			CCLOG("%d - %d ", m_boardRows[i][j]->m_position.m_x, m_boardRows[i][j]->m_position.m_y);
			CCLOG("------------");
		}
	}
}

void HelloWorld::InitBoard()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::srand(seed);
	int random = 0;
	
	CCLOG("m_offsetX = %d, m_offsetY = %d", m_offsetX, m_offsetY);
	/// init container
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		Candy** row = new Candy*[BOARD_WIDTH];
		m_boardRows.push_back(row);
	}

	for (int i = 0; i < BOARD_HEIGHT; i++) // 5
	{
		for (int j = 0; j < BOARD_WIDTH; j++) // 8
		{
			//CCLOG("i = %d, j = %d", i, j);
			random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
			if (random <= 4)	//bean blue
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_blue.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_BLUE;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 9) //bean green
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_green.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_GREEN;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 12) //bean orange
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_orange.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_ORANGE;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 14) //bean pink
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_pink.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_PINK;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 16) //bean purple
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_purple.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_PURPLE;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 22) //bean red
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_red.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_RED;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 24) //bean white
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_white.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_WHITE;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 30) //bean yellow
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/bean_yellow.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_BEAN_YELLOW;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 32) //candy cane
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/candycane.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_CANE_CANE;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else if (random <= 36) //candy corn
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/candycorn.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_CANE_CORN;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			else  //candy humbug
			{
				m_boardRows[i][j] = Candy::createCandyWithFileName("candy/candyhumbug.png");
				m_boardRows[i][j]->setPosition(Point(m_botLeftX + j*m_offsetX, m_botLeftY + i*m_offsetY));
				m_boardRows[i][j]->m_type = TypeOfCandy::TYPE_CANE_HUMBUG;
				this->addChild(m_boardRows[i][j], Z_INDEX_CANDY);
			}
			m_boardRows[i][j]->m_position = Point2D(i, j);
		}
	}

}


bool HelloWorld::CheckMatchThree()
{
	CheckMatchHorizontal(m_firstSelected);
	CheckMatchVertical(m_firstSelected);

	CheckMatchHorizontal(m_secondSelected);
	CheckMatchVertical(m_secondSelected);

	auto numOfChain = m_allChains.size();
	CCLOG("num of chain: %d", numOfChain);
	if (numOfChain >= 1)
	{
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
/// Hàm ktra trong 1 cột thứ col, có match-3 với candy ko?
/// hàm trả về vị trí đầu tiên + vị trí cuối cùng của chuỗi match với candy
/// hoặc nếu ko tìm đc chuỗi thì vị trí cuối cùng của chuỗi là 0.
int		HelloWorld::CheckMatchVertical(Candy* candy)
{
	if (candy == nullptr)
	{
		CCLOG("NULL Ptr");
		return -1;
	}

	/// ktra nếu ptu đang xét đã thuộc 1 chain nào đó rồi thì bỏ qua.
	Point2D		posOfCandy = candy->m_position;
	for (auto it = m_allChains.begin(); it != m_allChains.end(); it++)
	{
		if ((*it)->CheckIfInChain(posOfCandy))
		{
			return -1;
		}
	}

	TypeOfCandy typeOfCandy;
	Chain*	chain = new Chain;
	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	chain->m_first = posOfCandy;
	chain->m_last = posOfCandy;
	chain->m_isVertical = true;
	chain->m_length = 1;
	chain->m_chainOfType = candy->m_type;

	const int column = posOfCandy.m_y;
	const int row = posOfCandy.m_x;
	int i = row + 1;
	/// duyệt từ ptu == candy lên phía trên.
	for (; i < BOARD_HEIGHT; i++)
	{
		typeOfCandy = m_boardRows[i][column]->m_type;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Point2D(i, column));
		}
		else
		{
			break;
		}
	}

	/// duyệt từ ptu == candy xuống phía dưới.
	i = row - 1;
	for (; i >= 0; i--)
	{
		typeOfCandy = m_boardRows[i][column]->m_type;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Point2D(i, column));
		}
		else
		{
			break;
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain->m_length >= 3)
	{
		m_allChains.push_back(chain);
		CCLOG("posCandy: %d - %d", posOfCandy.m_x, posOfCandy.m_y);
		CCLOG("1st: %d - %d | 2nd: %d - %d", chain->m_first.m_x, chain->m_first.m_y, chain->m_last.m_x, chain->m_last.m_y);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
/// Hàm ktra trong 1 hàng thứ row, có match-3 với candy ko ?
/// hàm trả về vị trí đầu tiên + vị trí cuối cùng của chuỗi match với candy1st
/// hoặc nếu ko có chuỗi nào thì vị trí cuối cùng là 0.
int HelloWorld::CheckMatchHorizontal(Candy* candy)
{
	if (candy == nullptr)
	{
		CCLOG("NULL Ptr");
		return -1;
	}

	/// ktra nếu ptu đang xét đã thuộc 1 chain nào đó rồi thì bỏ qua.
	Point2D		posOfCandy = candy->m_position;
	for (auto it = m_allChains.begin(); it != m_allChains.end(); it++)
	{
		if ((*it)->CheckIfInChain(posOfCandy))
		{
			return -1;
		}
	}
	TypeOfCandy typeOfCandy;
	Chain*	chain = new Chain;
	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	chain->m_first = posOfCandy;
	chain->m_last = posOfCandy;
	chain->m_isVertical = false;
	chain->m_length = 1;
	chain->m_chainOfType = candy->m_type;

	const int column = posOfCandy.m_y;
	const int row = posOfCandy.m_x;
	int i = column + 1;
	/// duyệt từ ptu == candy sang bên phải
	for (; i < BOARD_WIDTH; i++)
	{
		typeOfCandy = m_boardRows[row][i]->m_type;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Point2D(row, i));
		}
		else
		{
			break;
		}
	}

	/// duyệt từ ptu == candy sang bên trái
	i = column - 1;
	for (; i >= 0; i--)
	{
		typeOfCandy = m_boardRows[row][i]->m_type;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Point2D(row, i));
		}
		else
		{
			break;
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain->m_length >= 3)
	{
		m_allChains.push_back(chain);
		CCLOG("posCandy: %d - %d", posOfCandy.m_x, posOfCandy.m_y);
		CCLOG("1st: %d - %d | 2nd: %d - %d", chain->m_first.m_x, chain->m_first.m_y, chain->m_last.m_x, chain->m_last.m_y);
	}
	return 0;
}


void HelloWorld::CheckMatch3All()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			CheckMatchHorizontal(m_boardRows[i][j]);
			CheckMatchVertical(m_boardRows[i][j]);
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
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
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

    // add the sprite as a child to this layer
    //this->addChild(background, Z_INDEX_BG);
	auto cd_blue = Candy::createCandyWithFileName("candy/bean_blue.png");
	m_offsetX = (int)cd_blue->getBoundingBox().size.width + 15;
	m_offsetY = (int)cd_blue->getBoundingBox().size.height + 15;
	
	/// set bottom-left is root of board.
	m_botLeftX = visibleSize.width / 5;
	m_botLeftY = visibleSize.height / 5;
	/// init board
	InitBoard();
	m_firstSelected = nullptr;
	m_secondSelected = nullptr;


	auto _listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	//printAllPos();
	CheckMatch3All();
	CCLOG("number of chain: %d", m_allChains.size());
	// check all sprites.
	//schedule(schedule_selector(HelloWorld::updateGame));
	

    return true;
}


void HelloWorld::updateGame(float dt)
{
	//CCLOG("delta time: %f", dt);
	if (m_firstSelected && m_secondSelected)
	{
		if (IsSwappable(m_index1st, m_index2nd))
		{
			CCLOG("Swapped !");
			/*CCLOG("1st TYPE: %d ---", m_boardRows[m_index1st.m_x][m_index1st.m_y]->m_type);
			CCLOG("2nd TYPE: %d ---", m_boardRows[m_index2nd.m_x][m_index2nd.m_y]->m_type);*/
			Swap(m_firstSelected, m_secondSelected);
			/*CCLOG("1st TYPE: %d ---", m_boardRows[m_index1st.m_x][m_index1st.m_y]->m_type);
			CCLOG("2nd TYPE: %d ---", m_boardRows[m_index2nd.m_x][m_index2nd.m_y]->m_type);*/

			//if (CheckMatchThree())
			{
				//CCLOG("Match 3 !");
			}
			//else
			{
				//CCLOG("Not Match 3 !!");
			}
		}
		else
		{
			CCLOG("Cannot Swapped !");
		}
		/// check match 3 sau khi swap
		//if (CheckMatchThree())
		{
			//CCLOG("Match 3 !");
		}
		//else
		{
			/// swap nguoc tro lai
			//CCLOG("Ko Match 3 !");

		}
		/// update score

		/// reset 
		m_index1st = Point2D(0, 0);
		m_firstSelected = nullptr;
		m_index2nd = Point2D(0, 0);
		m_secondSelected = nullptr;
	}

	CheckMatch3All();
	CCLOG("num of chain: %d", m_allChains.size());
	/// remove all chains.
	m_allChains.clear();
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

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	//CCLOG("Clicked! x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	m_pointClicked = touch->getLocation();
	
	CheckAllSprite();
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
	m_pointClicked = Vec2(0, 0);
	CCLOG("Touch End !");
}

void HelloWorld::onTouchMoved(cocos2d::Touch*, cocos2d::Event*)
{
	//CCLOG("Touch Moved !");
}
