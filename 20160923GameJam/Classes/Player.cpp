#include "Player.h"
#include "MainScene.h"
#include "Character.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "DebugDrawNode.h"
#include "QueryCallback.h"
#include "SimpleAudioEngine.h"		// サウンド


USING_NS_CC;

using namespace CocosDenshion;		// サウンド

const int PTM_RATIO = 32;


Player::Player()
{
}

Player::~Player()
{
}

bool Player::init(b2World* world)
{
	//srand((unsigned int)time(NULL));

	scheduleUpdate();

	// リスナー ---------------------------------------------------
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);*/
	//listener->onTouchesEnded = CC_CALLBACK_2(PlayerA::onTouchesEnded, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(PlayerA::onTouchesMoved, this);
	// -----------------------------------------------------------
	// イベントリスナーを作成---------------------------------------
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// -----------------------------------------------------------
	
	m_pWorld = world;
	
	
	// プレイヤー
	m_pPlayerSpr = Sprite::create();
	m_pPlayerSpr->setScale(0.2);
	m_pPlayerSpr->setTag(PLAYER);
	m_pPlayerSpr->setPosition(Vec2((840/2)-280,(960/2)-100));
	this->addChild(m_pPlayerSpr);
	
	b2BodyDef playerBodyDef;
	b2FixtureDef playerFixtureDef;
	b2PolygonShape playerDynamicBox;
	playerDynamicBox.SetAsBox(64.0f / 2 / PTM_RATIO, 124.f / 2 / PTM_RATIO);

	playerBodyDef.gravityScale = 3.0f;
	playerFixtureDef.friction = 0.0f;

	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.userData = m_pPlayerSpr;
	playerBodyDef.position.Set(((640 / 2) - 180) / PTM_RATIO, ( (960 / 2) - 100) / PTM_RATIO);
	m_pbPlayer = m_pWorld->CreateBody(&playerBodyDef);
	
	playerFixtureDef.shape = &playerDynamicBox;
	m_pbPlayer->CreateFixture(&playerFixtureDef);

	// カウンター
	m_touchCount = 0;

	m_touchFlag = false;

	m_time = 0;

	m_timeCount = 0;


	//スプライトフレームキャッシュを作成する
	auto cacher = SpriteFrameCache::getInstance();

	//プリセットを読み込む

	cacher->addSpriteFramesWithFile("run.plist");

	//auto spriteMinion = Sprite::create("minion.png");

	//画像を配列に読み込む
	Vector<cocos2d::SpriteFrame*> frames;

	for (int i = 1; i < 6; i++)
	{
		std::stringstream ss;
		ss << "run000" << i;
		ss << ".png";
		/*std::cout << std::setfill('0');*/

		/*ss << "runner" << i << ".png";*/
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
	}


	//アニメーションを作成する
	auto anim = Animation::createWithSpriteFrames(frames, 0.1f);
	//アニメーションアクションを作成する
	auto action = Animate::create(anim);

	//永久に繰り返すアクションを作成する
	auto anime = RepeatForever::create(action);

	//アクションを実行する
	m_pPlayerSpr->runAction(anime);




	// フラグ
	//m_jumpFlag = false;
	//m_getMaskflag = false;
	//m_putOutMaskPowerButtonFlag = false;



	//m_pIconOfNotGetMaskPower = Sprite::create("NotGetMaskPowerButton.png");
	//m_pIconOfNotGetMaskPower->setPosition(Vec2((960 / 2) + 340, 100));
	//m_pIconOfNotGetMaskPower->setScale(2);
	//this->addChild(m_pIconOfNotGetMaskPower);


//s	m_main = MainScene::create();
//s	//m_main->getGetMaskflag(false);
//s	this->addChild(m_main);



	//// ジャンプボタン
	//auto jumpButtonMenuItemImage = MenuItemImage::create(
	//	"jumpButton.png",
	//	"jumpButtonPush.png",
	//	CC_CALLBACK_1(Player::jump, this));
	//jumpButtonMenuItemImage->setScale(2);
	////jumpButtonMenuItemImage->setRotation(180);
	//jumpButtonMenuItemImage->setPosition(Vec2((960 / 2) - 340, 100));
	//auto jumpButtonMenu = Menu::create(jumpButtonMenuItemImage, NULL);
	//jumpButtonMenu->setPosition(Vec2::ZERO);
	//this->addChild(jumpButtonMenu, 1);
	//
	////--
	//putOutToMaskPowerButton();
	////--

	return true;
}

void Player::update(float dt)
{
	if (m_touchFlag)
	{
		m_time++;
		
		if (m_time == 60)
		{
			m_timeCount++;
			m_time = 0;
		}
		if (m_timeCount == 1)
		{
			m_touchFlag = false;
			log("time %d",m_timeCount);
			m_timeCount == 0;
		}
	}
//
//	
//
//	//if (m_main -> getGetMaskflag() != false)
	//{
	//	m_pIconOfNotGetMaskPower->setVisible(false);
	//	
	//	if (m_putOutMaskPowerButtonFlag != true)
	//	{
		//	putOutToMaskPowerButton();
	//	}
	//}
}


//void Player::jump(cocos2d::Ref * pSende)
//{
//	auto actionJumpBy = JumpBy::create(1.f, Vec2(0, 0), 100, 1);
//	m_pPlayerSpr->runAction(actionJumpBy);
//
//	m_touchCount++;
//	//m_jumpFlag = true;
//	log("touch &d 回", m_touchCount);
//}

//void Player::putOutToMaskPowerButton()
//{
//	m_putOutMaskPowerButtonFlag = true;
//
//	// bi-mu
//	auto jumpButtonMenuItemImage = MenuItemImage::create(
//		"maskPowerButton.png",
//		"maskPowerButtonPush.png",
//		CC_CALLBACK_1(Player::useMaskPower, this));
//	jumpButtonMenuItemImage->setScale(2);
//	//jumpButtonMenuItemImage->setRotation(180);
//	jumpButtonMenuItemImage->setPosition(Vec2((960 / 2) + 340, 100));
//	auto jumpButtonMenu = Menu::create(jumpButtonMenuItemImage, NULL);
//	jumpButtonMenu->setPosition(Vec2::ZERO);
//	this->addChild(jumpButtonMenu, 1);
//}

//void Player::useMaskPower(cocos2d::Ref * pSende)
//{
//	m_pBullet = MaskPower::create();
//	m_pBullet -> setPosition(m_pPlayerSpr->getPosition());
//	this->addChild(m_pBullet);
//}

void Player::jump(bool flag)
{
	if (flag == true)
	{
		//b2Vec2 impulse(0, 10.5f);
		//b2Vec2 point = m_pbPlayer->GetWorldCenter();
		//m_pbPlayer->ApplyLinearImpulse(impulse, point, true);

		b2Vec2 vel = m_pbPlayer->GetLinearVelocity();
		float m = m_pbPlayer->GetMass();// the mass of the body
		b2Vec2 desiredVel = b2Vec2(0, 28);// the vector speed you set
		b2Vec2 velChange = desiredVel - vel;
		b2Vec2 impluse = m * velChange; //impluse = mv
		m_pbPlayer->ApplyLinearImpulse(impluse, m_pbPlayer->GetWorldCenter(),true);
	}
}

void Player::twoJump()
{
	m_jumpCount += 1;

	if (m_jumpCount < 2)
	{
		b2Vec2 vel = m_pbPlayer->GetLinearVelocity();
		float m = m_pbPlayer->GetMass();// the mass of the body
		b2Vec2 desiredVel = b2Vec2(0, 20);// the vector speed you set
		b2Vec2 velChange = desiredVel - vel;
		b2Vec2 impluse = m * velChange; //impluse = mv
		m_pbPlayer->ApplyLinearImpulse(impluse, m_pbPlayer->GetWorldCenter(), true);
	}
	if (m_jumpCount == 2)
	{
		m_jumpCount = 0;
	}
}

Player * Player::create(b2World* world)
{
	Player* ret = new (std::nothrow) Player();
	if (ret && ret->init(world))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		ret = nullptr;
		return nullptr;
	}
}
