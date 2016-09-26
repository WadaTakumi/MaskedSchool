#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"		// サウンド

USING_NS_CC;

using namespace CocosDenshion;		// サウンド

Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	scheduleUpdate();

	bool m_getMaskflag=false;

	//Sprite* bg = Sprite::create("bg.png");
	//bg->setPosition(Vec2((860 / 2) , (960 / 2) ));
	//bg->setScale(6);
	//this->addChild(bg,-2);
	
	m_pBackGround3 = BackGround3::create();
	this->addChild(m_pBackGround3, -3);

	m_pBackGround2 = BackGround2::create();
	this->addChild(m_pBackGround2,-2);

	m_pBackGround = BackGround::create();
	this->addChild(m_pBackGround,-1);

	m_pPlayer = Player::create();
	this->addChild(m_pPlayer);

	m_pEnemy = Enemy::create();
	this->addChild(m_pEnemy);

	m_pMaskOfBullet = MaskOfBullet::create();
	this->addChild(m_pMaskOfBullet);

	return true;
}

void MainScene::update(float dt)
{	
	m_time++;

	if (m_time == 60)
	{
		m_timeCount++;
		m_time = 0;
	}
	if (m_timeCount == 1)
	{
		log("time %d", m_timeCount);
	}

	collisionDetection();
	
	getGetMaskflag();
}

void MainScene::collisionDetection()
{
	Rect rect_player = m_pPlayer->getBoundingBox();
	Rect rect_mask = m_pMaskOfBullet->getBoundingBox();
	bool hit= rect_player.intersectsRect(rect_mask);

	if (hit)
	{
		//m_pMaskOfBullet->setVisible(false);
		m_getMaskflag = true;
	}
}

bool MainScene::getGetMaskflag()
{
	return m_getMaskflag;
}
