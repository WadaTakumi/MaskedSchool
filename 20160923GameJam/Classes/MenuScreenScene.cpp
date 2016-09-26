#include "MenuScreenScene.h"
#include "GameScene.h"
#include "enumerations.h"

USING_NS_CC;

MenuScreen::MenuScreen():
m_menuLabel(),
m_startButton(),
m_optionsButton(),
m_quitButton(),
m_touchPosition(0.0f, 0.0f),
m_isTouching(false)
{
}

Scene* MenuScreen::createScene()
{
    auto scene = Scene::create();
    if (scene)
        CCLOG("Scene creation succesful!");
    auto layer = MenuScreen::create();
    if (layer)
        CCLOG("Layer creation succesful!");
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MenuScreen::init()
{
    if (!Layer::init())
    {
        return false;
    }

    m_menuLabel = cocos2d::Label::createWithSystemFont("MAIN MENU", "Arial", 50);
    m_menuLabel->enableBold();
    m_menuLabel->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMaxY() - 100);
    m_menuLabel->setColor(Color3B::GREEN);
    this->addChild(m_menuLabel);

    createMenuButtons();

    return true;
}

void MenuScreen::startGame(Ref* sender, ui::Widget::TouchEventType eventType)
{
	if (eventType != ui::Widget::TouchEventType::ENDED)
		return;
	
	CCLOG("START button touched");
	// Start test
	CCLOG("Starting test scene...");
	GameScene::setGameType(GT_LOCAL);
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MenuScreen::showOptions(Ref* sender, ui::Widget::TouchEventType eventType)
{
	if (eventType != ui::Widget::TouchEventType::ENDED)
		return;

	CCLOG("OPTIONS button touched");
}

void MenuScreen::quitGame(Ref* sender, ui::Widget::TouchEventType eventType)
{
	if (eventType != ui::Widget::TouchEventType::ENDED)
		return;

	CCLOG("QUIT button touched");
	menuCloseCallback(sender);
}


void MenuScreen::createMenuButtons()
{
    // LOCAL GAME
    m_startButton = ui::Button::create();
    m_startButton->loadTextures("images/MenuButtonDefault.png", "images/MenuButtonHighlighted.png");
    m_startButton->setPosition(Point(this->getBoundingBox().getMidX(), 
                                     this->getBoundingBox().getMaxY() * 0.6));
    m_startButton->setTitleText("LOCAL GAME");
    m_startButton->setTitleFontSize(22);
    m_startButton->setTitleColor(Color3B::WHITE);
	m_startButton->setTouchEnabled(true);
	m_startButton->addTouchEventListener(CC_CALLBACK_2(MenuScreen::startGame, this));

    // OPTIONS
    m_optionsButton = ui::Button::create();
    m_optionsButton->loadTextures("images/MenuButtonDefault.png", "images/MenuButtonHighlighted.png");
    m_optionsButton->setPosition(Point(this->getBoundingBox().getMidX(),
                                      this->getBoundingBox().getMaxY() * 0.4));
    m_optionsButton->setTitleText("OPTIONS");
    m_optionsButton->setTitleFontSize(22);
    m_optionsButton->setTitleColor(Color3B::WHITE);
    m_optionsButton->setTouchEnabled(true);
	m_optionsButton->addTouchEventListener(CC_CALLBACK_2(MenuScreen::showOptions, this));


    // QUIT GAME
    m_quitButton = ui::Button::create();
    m_quitButton->loadTextures("images/MenuButtonDefault.png", "images/MenuButtonHighlighted.png");
    m_quitButton->setPosition(Point(this->getBoundingBox().getMidX(), 
                                    this->getBoundingBox().getMaxY() * 0.2));
    m_quitButton->setTitleText("QUIT");
    m_quitButton->setTitleFontSize(22);
    m_quitButton->setTitleColor(Color3B::WHITE);
    m_quitButton->setTouchEnabled(true);
	m_quitButton->addTouchEventListener(CC_CALLBACK_2(MenuScreen::quitGame, this));

    this->addChild(m_startButton, 0);
    this->addChild(m_optionsButton, 0);
    this->addChild(m_quitButton, 0);
}

void MenuScreen::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//bool MenuScreen::touchBeganCallback(Touch* touch, Event* event)
//{
//	m_isTouching = true;
//	m_touchPosition = touch->getLocation();
//	CCLOG("Touch position X: %f", m_touchPosition.x);
//	CCLOG("Touch position Y: %f", m_touchPosition.y);
//	return true;
//}
//
//void MenuScreen::touchMovedCallback(Touch* touch, Event* event)
//{
//
//}
//
//void MenuScreen::touchEndedCallback(Touch* touch, Event* event)
//{
//	m_isTouching = false;
//	//auto target = static_cast<ui::Button*>(event->getCurrentTarget());
//
//	//Get the position of the current point relative to the button
//	//Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//	//Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
//	auto point = event->getCurrentTarget()->getBoundingBox();
//	// TODO: buttonien touchit ei koskaan tule tanne
//	if (m_startButton == event->getCurrentTarget() && point.containsPoint(touch->getLocation()))
//	{
//		// Start test
//		CCLOG("Test scene started");
//		auto scene = GameScene::createScene();
//		Director::getInstance()->replaceScene(scene);
//	}
//}