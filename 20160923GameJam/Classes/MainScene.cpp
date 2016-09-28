#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"		// サウンド
#include "Box2D/Box2D.h"
#include "DebugDrawNode.h"
#include "QueryCallback.h"


USING_NS_CC;

using namespace CocosDenshion;		// サウンド

const int PTM_RATIO = 32;


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

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
	delete m_pDraw;
	delete m_pWorld;
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

	// リスナー ---------------------------------------------------
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	//listener->onTouchesEnded = CC_CALLBACK_2(PlayerA::onTouchesEnded, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(PlayerA::onTouchesMoved, this);
	// -----------------------------------------------------------
	// イベントリスナーを作成---------------------------------------
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// -----------------------------------------------------------
	
	//Sprite* bg = Sprite::create("bg.png");
	//bg->setPosition(Vec2((860 / 2) , (960 / 2) ));
	//bg->setScale(6);
	//this->addChild(bg,-2);
	
	//m_pBackGround3 = BackGround3::create();
	//this->addChild(m_pBackGround3, -3);
	//
	//m_pBackGround2 = BackGround2::create();
	//this->addChild(m_pBackGround2,-2);
	//
	//m_pBackGround = BackGround::create();
	//this->addChild(m_pBackGround,-1);

	initPhysics();

	m_pPlayer = Player::create(m_pWorld);
	this->addChild(m_pPlayer);

	m_pEnemy = Enemy::create();
	this->addChild(m_pEnemy);

	//m_pbaseMask = BaseMask::create();
	//this->addChild(m_pbaseMask);
	
	//一時的なコメントアウト 9/27
	//m_pMaskOfBullet = MaskOfBullet::create();
	//this->addChild(m_pMaskOfBullet);

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


	// 物理ワールドの更新
	m_pWorld->Step(1.0f / 60.0f, 8, 3);

	//---------------------------------------------------------------
	// 物理ワールド内全てのボディについて処理
	for (b2Body* body = m_pWorld->GetBodyList();
	body != nullptr;
		body = body->GetNext())
	{
		// UserDataにしまっておいたSpriteを取得
		Sprite* spr = (Sprite*)body->GetUserData();
		// あらかじめSpriteがしまってある場合のみ
		if (spr != nullptr)
		{
			// 物理ワールド中の剛体の座標を取得して、
			// 同じ位置にSpriteを移動
			b2Vec2 pos = body->GetPosition();
			spr->setPosition(pos.x*PTM_RATIO, pos.y*PTM_RATIO);
		}
	}
}

void MainScene::initPhysics()
{
	//物理ワールド
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_pWorld = new b2World(gravity);

	// 表示用のインスタンスを作成
	m_pDraw = new GLESDebugDraw(PTM_RATIO);
	// 全種類表示
	uint32 flags = 0xffffffff;
	m_pDraw->SetFlags(flags);
	// 表示インスタンスをワールドにセット
	m_pWorld->SetDebugDraw(m_pDraw);
}

void MainScene::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	// 物理ワールドをデバッグ表示
	m_pWorld->DrawDebugData();
}

bool MainScene::onTouchBegan(cocos2d::Touch * touch,
	cocos2d::Event * unused_event)
{
	//Rect rect_player = m_pPlayer->getBoundingBox();
	////Rect rect_mask = m_pMaskOfBullet->getBoundingBox();
	//bool hit= rect_player.intersectsRect(rect_mask);
	Vec2 touchPoint = touch->getLocation();
	m_position.x = touchPoint.x / PTM_RATIO;
	m_position.y = touchPoint.y / PTM_RATIO;


	if (touchPoint.x < 640 / 2 / PTM_RATIO)
	{
		this->m_pPlayer->jump();
	}

	if (touchPoint.x > 640 / 2 / PTM_RATIO)
	{
		this->m_pbaseMask->MaskAction();
	}


	return true;
}
