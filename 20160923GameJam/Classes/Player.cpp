#include "Player.h"
#include "MainScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"		// サウンド

USING_NS_CC;

using namespace CocosDenshion;		// サウンド


bool Player::init()
{
	//srand((unsigned int)time(NULL));

	//scheduleUpdate();

//	// リスナー ---------------------------------------------------
//	auto listener = EventListenerTouchOneByOne::create();
//	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
//	//listener->onTouchesEnded = CC_CALLBACK_2(PlayerA::onTouchesEnded, this);
//	//listener->onTouchesMoved = CC_CALLBACK_2(PlayerA::onTouchesMoved, this);
//	// -----------------------------------------------------------
//	// イベントリスナーを作成---------------------------------------
//	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//	// -----------------------------------------------------------
	
// カウンター
	m_touchCount = 0;

	// フラグ
	//m_jumpFlag = false;
	m_getMaskflag = false;
	m_putOutMaskPowerButtonFlag = false;

	// プレイヤー
	m_pPlayer = Sprite::create("PlayerAMonster1.png");
	m_pPlayer->setScale(0.1);
	m_pPlayer->setPosition(Vec2((840/2)-280,(960/2)-100));
	this->addChild(m_pPlayer);


	//m_pIconOfNotGetMaskPower = Sprite::create("NotGetMaskPowerButton.png");
	//m_pIconOfNotGetMaskPower->setPosition(Vec2((960 / 2) + 340, 100));
	//m_pIconOfNotGetMaskPower->setScale(2);
	//this->addChild(m_pIconOfNotGetMaskPower);


//s	m_main = MainScene::create();
//s	//m_main->getGetMaskflag(false);
//s	this->addChild(m_main);



	// ジャンプボタン
	auto jumpButtonMenuItemImage = MenuItemImage::create(
		"jumpButton.png",
		"jumpButtonPush.png",
		CC_CALLBACK_1(Player::jump, this));
	jumpButtonMenuItemImage->setScale(2);
	//jumpButtonMenuItemImage->setRotation(180);
	jumpButtonMenuItemImage->setPosition(Vec2((960 / 2) - 340, 100));
	auto jumpButtonMenu = Menu::create(jumpButtonMenuItemImage, NULL);
	jumpButtonMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpButtonMenu, 1);

	//--
	putOutToMaskPowerButton();
	//--

	return true;
}

void Player::update(float dt)
{
	m_time++;
	if (m_time == 60)
	{
		m_timeCount++;
		m_time = 0;
	}
	if (m_timeCount == 1)
	{
		log("time %d",m_timeCount);
	}

	

	//if (m_main -> getGetMaskflag() != false)
	//{
	//	m_pIconOfNotGetMaskPower->setVisible(false);
	//	
	//	if (m_putOutMaskPowerButtonFlag != true)
	//	{
		//	putOutToMaskPowerButton();
	//	}
	//}
}

//bool Player::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
//{
//	return true;
//}

void Player::jump(cocos2d::Ref * pSende)
{
	auto actionJumpBy = JumpBy::create(1.f, Vec2(0, 0), 100, 1);
	m_pPlayer->runAction(actionJumpBy);

	m_touchCount++;
	//m_jumpFlag = true;
	log("touch &d 回", m_touchCount);
}

void Player::putOutToMaskPowerButton()
{
	m_putOutMaskPowerButtonFlag = true;

	// bi-mu
	auto jumpButtonMenuItemImage = MenuItemImage::create(
		"maskPowerButton.png",
		"maskPowerButtonPush.png",
		CC_CALLBACK_1(Player::useMaskPower, this));
	jumpButtonMenuItemImage->setScale(2);
	//jumpButtonMenuItemImage->setRotation(180);
	jumpButtonMenuItemImage->setPosition(Vec2((960 / 2) + 340, 100));
	auto jumpButtonMenu = Menu::create(jumpButtonMenuItemImage, NULL);
	jumpButtonMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpButtonMenu, 1);
}

void Player::useMaskPower(cocos2d::Ref * pSende)
{
	m_pBullet = MaskPower::create();
	m_pBullet -> setPosition(m_pPlayer->getPosition());
	this->addChild(m_pBullet);
}

