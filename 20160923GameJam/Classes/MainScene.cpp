#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"		// �T�E���h
#include "Box2D/Box2D.h"
#include "DebugDrawNode.h"
#include "QueryCallback.h"


USING_NS_CC;

using namespace CocosDenshion;		// �T�E���h

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

	// ���X�i�[ ---------------------------------------------------
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	//listener->onTouchesEnded = CC_CALLBACK_2(PlayerA::onTouchesEnded, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(PlayerA::onTouchesMoved, this);
	// -----------------------------------------------------------
	// �C�x���g���X�i�[���쐬---------------------------------------
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
	
	//�ꎞ�I�ȃR�����g�A�E�g 9/27
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


	// �������[���h�̍X�V
	m_pWorld->Step(1.0f / 60.0f, 8, 3);

	//---------------------------------------------------------------
	// �������[���h���S�Ẵ{�f�B�ɂ��ď���
	for (b2Body* body = m_pWorld->GetBodyList();
	body != nullptr;
		body = body->GetNext())
	{
		// UserData�ɂ��܂��Ă�����Sprite���擾
		Sprite* spr = (Sprite*)body->GetUserData();
		// ���炩����Sprite�����܂��Ă���ꍇ�̂�
		if (spr != nullptr)
		{
			// �������[���h���̍��̂̍��W���擾���āA
			// �����ʒu��Sprite���ړ�
			b2Vec2 pos = body->GetPosition();
			spr->setPosition(pos.x*PTM_RATIO, pos.y*PTM_RATIO);
		}
	}
}

void MainScene::initPhysics()
{
	//�������[���h
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_pWorld = new b2World(gravity);

	// �\���p�̃C���X�^���X���쐬
	m_pDraw = new GLESDebugDraw(PTM_RATIO);
	// �S��ޕ\��
	uint32 flags = 0xffffffff;
	m_pDraw->SetFlags(flags);
	// �\���C���X�^���X�����[���h�ɃZ�b�g
	m_pWorld->SetDebugDraw(m_pDraw);
}

void MainScene::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	// �������[���h���f�o�b�O�\��
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
