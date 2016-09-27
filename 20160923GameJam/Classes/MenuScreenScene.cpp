#include "MenuScreenScene.h"
#include "GameScene.h"
#include "enumerations.h"

USING_NS_CC;

MenuScreen::MenuScreen():
m_menuLabel(),
m_startButton(),
m_optionsButton(),
m_quitButton(),
m_yesButton(),
m_noButton(),
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

void MenuScreen::openExitMenu(Ref* sender, ui::Widget::TouchEventType eventType)
{
	if (eventType != ui::Widget::TouchEventType::ENDED)
		return;
	m_yesButton->setVisible(true);
	m_yesButton->setTouchEnabled(true);
	m_noButton->setVisible(true);
	m_noButton->setTouchEnabled(true);
}

void MenuScreen::closeExitMenu()
{
	m_yesButton->setVisible(false);
	m_yesButton->setTouchEnabled(false);
	m_noButton->setVisible(false);
	m_noButton->setTouchEnabled(false);
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
	m_quitButton->addTouchEventListener(CC_CALLBACK_2(MenuScreen::openExitMenu, this));

	// EXIT MENU BUTTONS
	// YES
	m_yesButton = ui::Button::create();
	m_yesButton->loadTextures("images/MenuButtonDefault.png", "images/MenuButtonHighlighted.png");
	m_yesButton->setPosition(Point(this->getBoundingBox().getMidX(),
								   this->getBoundingBox().getMaxY() * 0.6));
	m_yesButton->setTitleText("YES");
	m_yesButton->setTitleFontSize(22);
	m_yesButton->setTitleColor(Color3B::WHITE);
	m_yesButton->setTouchEnabled(false);
	m_yesButton->setVisible(false);
	m_yesButton->addTouchEventListener(CC_CALLBACK_2(MenuScreen::menuCloseCallback, this));

	// NO
	m_noButton = ui::Button::create();
	m_noButton->loadTextures("images/MenuButtonDefault.png", "images/MenuButtonHighlighted.png");
	m_noButton->setPosition(Point(this->getBoundingBox().getMidX(),
								  this->getBoundingBox().getMaxY() * 0.4));
	m_noButton->setTitleText("NO");
	m_noButton->setTitleFontSize(22);
	m_noButton->setTitleColor(Color3B::WHITE);
	m_noButton->setTouchEnabled(false);
	m_noButton->setVisible(false);
	//m_noButton->addTouchEventListener(CC_CALLBACK_2(MenuScreen::closeExitMenu, this));
	m_noButton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType eventType)
	{
		if (eventType != ui::Widget::TouchEventType::ENDED)
			return;
		// Close the quit game popup
		//MenuScreen::closeExitMenu();
		closeExitMenu();
	});

    this->addChild(m_startButton, 0);
    this->addChild(m_optionsButton, 0);
    this->addChild(m_quitButton, 0);
	this->addChild(m_yesButton, 0);
	this->addChild(m_noButton, 0);
}

void MenuScreen::menuCloseCallback(Ref* pSender, ui::Widget::TouchEventType eventType)
{
	if (eventType != ui::Widget::TouchEventType::ENDED)
		return;
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}