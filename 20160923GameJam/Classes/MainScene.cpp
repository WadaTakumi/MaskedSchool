#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "BackgroundLayer.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"		// サウンド
#include "Box2D/Box2D.h"
#include "DebugDrawNode.h"
#include "QueryCallback.h"
#include "EnemyData.h"


USING_NS_CC;

using namespace CocosDenshion;		// サウンド

const int PTM_RATIO = 32;
const int GRAVITY = -9.8f;
const int GROUND_POSITION_Y = 186;
const int SCREEN_POSITION_X = 640 / 2;

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

	m_getMaskflag = true;
	m_notJampFlag = false;
	//m_canMaskPowerFlag = false;

	//m_pbaseMask = nullptr;

	// リスナー ---------------------------------------------------
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	//listener->onTouchesEnded = CC_CALLBACK_2(PlayerA::onTouchesEnded, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(PlayerA::onTouchesMoved, this);
	// -----------------------------------------------------------
	// イベントリスナーを作成---------------------------------------
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// -----------------------------------------------------------
	

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

	// Enemy initialisation
	m_enemyData = EnemyData::initEnemies();

	m_pEnemy = Enemy::create(m_pWorld, m_enemyData);
	this->addChild(m_pEnemy);

	m_pBackGroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackGroundLayer,-10);

	m_pbaseMask = MaskOfBullet::create();
	m_pbaseMask->m_mask= Sprite::create("mask1.png");
	this->addChild(m_pbaseMask);

	scheduleUpdate();

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


	//---------------------------------------------------------------
	// 物理ワールドの更新
	m_pWorld->Step(1.0f / 60.0f, 8, 3);

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


	//---------------------------------------------------------------
	// マスクとプレイヤーの当たり判定
	Rect rect_player = m_pPlayer->getBoundingBox();
	Rect rect_mask;
	if (m_pbaseMask != nullptr)
	{
		//rect_mask = m_pbaseMask->m_mask->getBoundingBox();
	}
	bool hit = rect_mask.intersectsRect(rect_player);
	if (hit)
	{
		if (m_pbaseMask != nullptr)
		{
			// マスクを消す
			/*m_pbaseMask->removeFromParent();
			m_pbaseMask = nullptr;*/
		
			// フラグを立てる
			m_getMaskflag = true;
		}
	}
}

void MainScene::initPhysics()
{
	//物理ワールド
	b2Vec2 gravity;
	gravity.Set(0.0f, GRAVITY);
	m_pWorld = new b2World(gravity);

	// 表示用のインスタンスを作成
	m_pDraw = new GLESDebugDraw(PTM_RATIO);
	// 全種類表示
	uint32 flags = 0xffffffff;
	m_pDraw->SetFlags(flags);
	// 表示インスタンスをワールドにセット
	m_pWorld->SetDebugDraw(m_pDraw);

	// 壁全体で一つのオブジェクトにする
	b2BodyDef groudBodyDef;
	groudBodyDef.position.Set(0, 0);

	m_groundBody = m_pWorld->CreateBody(&groudBodyDef);


	b2Vec2 leftBottom(0, GROUND_POSITION_Y);
	b2Vec2 rightBottom(960, GROUND_POSITION_Y);

	// ピクセルをメートルに変換
	leftBottom.x /= PTM_RATIO;
	leftBottom.y /= PTM_RATIO;
	rightBottom.x /= PTM_RATIO;
	rightBottom.y /= PTM_RATIO;

	b2EdgeShape groudb2EdgeShape;
	b2FixtureDef groundFixttureDef;

	groundFixttureDef.shape = &groudb2EdgeShape;
	//groundFixttureDef.density = 1.0f;
	groundFixttureDef.friction = 0.0f;
	//groundFixttureDef.restitution = 1.0f;

	// 地面
	groudb2EdgeShape.Set(leftBottom, rightBottom);
	m_groundBody->CreateFixture(&groundFixttureDef);


	m_pWorld->SetContactListener(this);

}

void MainScene::draw(cocos2d::Renderer * renderer,
	const cocos2d::Mat4 & transform, uint32_t flags)
{
	// 物理ワールドをデバッグ表示
	m_pWorld->DrawDebugData();
}

bool MainScene::onTouchBegan(cocos2d::Touch * touch,
	cocos2d::Event * unused_event)
{
	Vec2 touchPoint = touch->getLocation();

	// box座標系に変換--------------------------------------
	m_position.x = touchPoint.x / PTM_RATIO;
	m_position.y = touchPoint.y / PTM_RATIO;
	
	
	// 画面の左側を押してジャンプする
	if (m_position.x < (SCREEN_POSITION_X) / PTM_RATIO)
	{
		this->m_pPlayer->jump(m_notJampFlag);
	}
	

	// マスクを取った後、画面の右側を押してマスクパワーを使う
	if (m_position.x > (SCREEN_POSITION_X) / PTM_RATIO)
	{	
		if (m_getMaskflag||m_pbaseMask!=nullptr)
		{
			// mask power
			m_pbaseMask->MaskAction();
		}
	}

	return false;
}

void MainScene::BeginContact(b2Contact* contact)
{
	void* bodyUserData;

	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	m_bodyA = fixA->GetBody();
	m_bodyB = fixB->GetBody();

	// 地面とプレイヤーの当たり判定
	if (m_bodyA == m_groundBody)
	{	
		m_notJampFlag = true;
	}
	else if (m_bodyB == m_groundBody)
	{
		m_notJampFlag = true;
	}
	

	// マスクとプレイヤーの当たり判定
	//Sprite* sprBodyA = (Sprite*)m_bodyA->GetUserData();
	//Sprite* sprBodyB = (Sprite*)m_bodyB->GetUserData();
	
	//if ()
	//{
	//
	//}
	//else if (m_bodyB == m_pbaseMask)
	//{
		
	//}

	// プレイヤーと敵の当たり判定
}

void MainScene::EndContact(b2Contact * contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	m_bodyA = fixA->GetBody();
	m_bodyB = fixB->GetBody();

	// 地面とプレイヤーの当たり判定
	if (m_bodyA == m_groundBody)
	{
		m_notJampFlag = false;
	}
	else if (m_bodyB == m_groundBody)
	{
		m_notJampFlag = false;
	}
}
