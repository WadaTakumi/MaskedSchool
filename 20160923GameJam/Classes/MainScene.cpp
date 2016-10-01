#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "BackgroundLayer.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"		// sound
#include "Box2D/Box2D.h"
#include "DebugDrawNode.h"
#include "QueryCallback.h"
#include "EnemyData.h"



USING_NS_CC;

using namespace CocosDenshion;		// sound

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

	m_pbaseMask = nullptr;

	m_time = 0;
	m_timeCount = 0;

	// ���X�i�[ ---------------------------------------------------
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	//listener->onTouchesEnded = CC_CALLBACK_2(PlayerA::onTouchesEnded, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(PlayerA::onTouchesMoved, this);
	// -----------------------------------------------------------
	// �C�x���g���X�i�[���쐬---------------------------------------
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// -----------------------------------------------------------
	// ���y��ǂݍ���==============================================
	// �{�����[��
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	// ������
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm_maoudamashii_cyber01.mp3");
	// ���y���Đ�����֐��֐�
	BackgroundMusic();
	// ============================================================
	// ���ʉ���ǂݍ���==============================================
	// �{�����[��
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->preloadEffect("BlockBreak.mp3");
	// ============================================================
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

	m_maskBody = nullptr;

	SpawnMask();
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
	if (m_timeCount == 2 && m_maskBody != nullptr)
	{
		RemoveMask();
		
		SpawnMask();

		log("time %d", m_timeCount);
		m_timeCount = 0;
	}
	//if ()
	//{
	//}
	


	//---------------------------------------------------------------
	// �������[���h�̍X�V
	m_pWorld->Step(1.0f / 60.0f, 8, 3);

	
	///////////////////////////
	if(m_pbaseMask != nullptr)
		m_pbaseMask->GetPos(m_pPlayer->m_pPlayerSpr->getPosition());

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


	Rect rect_player = m_pPlayer->m_pPlayerSpr->getBoundingBox();
	Rect rect_mask;


	//---------------------------------------------------------------
	// �}�X�N�ƃv���C���[�̓����蔻��
	if (m_pbaseMask != nullptr && m_pbaseMask->m_mask != nullptr)
	{
		
		rect_mask = m_pbaseMask->m_mask->getBoundingBox();
		//if (rect_mask.intersectsRect(rect_player))[
	
		if(rect_mask.intersectsRect(rect_player))
		{
			// �}�X�N������
			/*m_pbaseMask->removeFromParent();
			m_pbaseMask = nullptr;*/

			// �t���O�𗧂Ă�
			m_getMaskflag = true;
			CCLOG("HIT");
		}
	}
}

void MainScene::initPhysics()
{
	//�������[���h
	b2Vec2 gravity;
	gravity.Set(0.0f, GRAVITY);
	m_pWorld = new b2World(gravity);

	// �\���p�̃C���X�^���X���쐬
	m_pDraw = new GLESDebugDraw(PTM_RATIO);
	// �S��ޕ\��
	uint32 flags = 0xffffffff;
	m_pDraw->SetFlags(flags);
	// �\���C���X�^���X�����[���h�ɃZ�b�g
	m_pWorld->SetDebugDraw(m_pDraw);

	// �ǑS�̂ň�̃I�u�W�F�N�g�ɂ���
	b2BodyDef groudBodyDef;
	groudBodyDef.position.Set(0, 0);

	m_groundBody = m_pWorld->CreateBody(&groudBodyDef);


	b2Vec2 leftBottom(0, GROUND_POSITION_Y);
	b2Vec2 rightBottom(960, GROUND_POSITION_Y);

	// �s�N�Z�������[�g���ɕϊ�
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

	// �n��
	groudb2EdgeShape.Set(leftBottom, rightBottom);
	m_groundBody->CreateFixture(&groundFixttureDef);


	m_pWorld->SetContactListener(this);

}

void MainScene::draw(cocos2d::Renderer * renderer,
	const cocos2d::Mat4 & transform, uint32_t flags)
{
	// �������[���h���f�o�b�O�\��
	m_pWorld->DrawDebugData();
}

bool MainScene::onTouchBegan(cocos2d::Touch * touch,
	cocos2d::Event * unused_event)
{
	Vec2 touchPoint = touch->getLocation();

	// box���W�n�ɕϊ�--------------------------------------
	m_position.x = touchPoint.x / PTM_RATIO;
	m_position.y = touchPoint.y / PTM_RATIO;
	
	
	// ��ʂ̍����������ăW�����v����
	if (m_position.x < (SCREEN_POSITION_X) / PTM_RATIO)
	{
		this->m_pPlayer->jump(m_notJampFlag);
	}
	

	// �}�X�N���������A��ʂ̉E���������ă}�X�N�p���[���g��
	if (m_position.x > (SCREEN_POSITION_X) / PTM_RATIO)
	{	
		if (m_getMaskflag && m_pbaseMask!=nullptr)
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

	// �n�ʂƃv���C���[�̓����蔻��
	if (m_bodyA == m_groundBody)
	{	
		m_notJampFlag = true;
	}
	else if (m_bodyB == m_groundBody)
	{
		m_notJampFlag = true;
	}
	
	if (m_bodyA == m_maskBody)
	{
		log("m_maskBody");
	}
	else if (m_bodyB == m_maskBody)
	{
		log("m_maskBody");
	}


	// �}�X�N�ƃv���C���[�̓����蔻��
	//Sprite* sprBodyA = (Sprite*)m_bodyA->GetUserData();
	//Sprite* sprBodyB = (Sprite*)m_bodyB->GetUserData();
	
	//if ()
	//{
	//
	//}
	//else if (m_bodyB == m_pbaseMask)
	//{
		
	//}

	// �v���C���[�ƓG�̓����蔻��
}

void MainScene::EndContact(b2Contact * contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	m_bodyA = fixA->GetBody();
	m_bodyB = fixB->GetBody();

	// �n�ʂƃv���C���[�̓����蔻��
	if (m_bodyA == m_groundBody)
	{
		m_notJampFlag = false;
	}
	else if (m_bodyB == m_groundBody)
	{
		m_notJampFlag = false;
	}
}

void MainScene::BackgroundMusic()
{
	// true �Ń��[�v�\
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound||se_maoudamashii_system48.mp3",true);
}

void MainScene::SpawnMask()
{
	m_pbaseMask = MaskOfBullet::create();
	m_pbaseMask->m_mask = Sprite::create("mask1.png");
	//m_pbaseMask->GetPos(m_pPlayer->m_pPlayerSpr->getPosition());
	this->addChild(m_pbaseMask);

	b2BodyDef BodyDef;
	b2FixtureDef FixtureDef;
	b2PolygonShape dynamicBox;

	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = m_pbaseMask;
	BodyDef.position.Set(m_pbaseMask->m_mask->getPosition().x,
		m_pbaseMask->m_mask->getPosition().y);
	m_maskBody = m_pWorld->CreateBody(&BodyDef);
	FixtureDef.shape = &dynamicBox;
	m_maskBody->CreateFixture(&FixtureDef);

	m_maskBody->SetGravityScale(0.f);


	
	auto  goJump = JumpTo::create(2.0f, Vec2(-20, random(300, 600)), random(100, 300), random(3, 5));
	auto  goJump2 = MoveTo::create(2.0f, Vec2(0,300));
	auto  goJump3 = JumpTo::create(2.0f, Vec2(-20, random(300, 600)), random(100, 300), random(3, 5));

	switch (1)
	{
	case 0:
		m_pbaseMask->m_mask->runAction(goJump);
		break;
	case 1:
		m_pbaseMask->m_mask->runAction(goJump2);
		break;
	case 2:
		m_pbaseMask->m_mask->runAction(goJump3);
		break;
	}

	// ���ʉ���炷=======================================================
	int soundID;
	soundID = SimpleAudioEngine::sharedEngine()->playEffect("sound||se_maoudamashii_system48.mp3");
	//=======================================================================
}

void MainScene::RemoveMask()
{
	//Vec2 pos = m_pbaseMask->m_mask->getPosition();
	m_pWorld->DestroyBody(m_maskBody);
	m_maskBody = nullptr;

	m_pbaseMask->removeFromParent();
	m_pbaseMask = nullptr;
}


