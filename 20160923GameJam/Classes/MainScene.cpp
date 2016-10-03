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
const int GRAVITY = -18.0f;
const int GROUND_POSITION_Y = 186;
const int SCREEN_POSITION_X = 640 / 2;

int MainScene::exp_num = 0;

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

	m_getMaskflag = false;
	m_notJampFlag = false;
	//m_canMaskPowerFlag = false;

	//m_pbaseMask = nullptr;

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

	//Enemy initialisation
	//m_enemyData = EnemyData::initEnemies();


	m_pBackGroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackGroundLayer,-10);


	//Enemy initialisation
	//m_enemyData = EnemyData::initEnemies();

	m_pEnemy = Enemy::create(m_pWorld, m_enemyData);
	this->addChild(m_pEnemy);


	m_gameStart = CutInOfStart::create();
	m_gameStart->setCutInFlag(false);
	this->addChild(m_gameStart,1);


	getMaskIcon = Sprite::create("mask1.png");
	getMaskIcon->setPosition(Vec2(100,100));
	getMaskIcon->setScale(1.2);
	getMaskIcon->setVisible(false);
	this->addChild(getMaskIcon);
	


	expgejiback = Sprite::create("MenuButtonDefault.png");
	expgejiback->setPosition(Vec2(500,50));
	this->addChild(expgejiback);
	expgeji = Sprite::create("MenuButtonDefault.png");
	expgeji->setPosition(Vec2(500, 50));
	this->addChild(expgeji);
	exp = Sprite::create("MenuButtonHighlighted.png");



	// �Q�[�W
	//�Q�[�W�̐ݒ�
	geji = ProgressTimer::create(exp);
	geji->setPosition(500.0f, 50.0f);
	this->addChild(geji);
	geji->setType(ProgressTimer::Type::BAR);
	geji->setPercentage(exp_num);
	geji->setMidpoint(ccp(0, 0.5f));
	geji->setBarChangeRate(ccp(1, 0));



	m_maskBody = nullptr;

	SpawnMask();
	scheduleUpdate();
	this->schedule(schedule_selector(MainScene::RoopToMaskMove), 10.0f);


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

	//---------------------------------------------------------------
	// StateCutIn
	if (m_gameStart->getCutinFlag() == true)
	{
		m_gameStart->setCutInFlag(false);
	}
	else
	{
		m_gameStart->setCutInFlag(false);
	}	
	
	//---------------------------------------------------------------
	// ���b�����Ƀ}�X�N���o��������
	//if (m_timeCount == 2 /*&& m_maskBody != nullptr*/)
	//{
	//	RemoveMask();
	//	SpawnMask();
	//
	//	log("m_timeCount_time %d", m_timeCount);
	//	m_timeCount = 0;
	//}

	//---------------------------------------------------------------
	// �}�X�N�ƃv���C���[�̓����蔻��
	
	Rect rect_player;
	Rect rect_mask_bullet;
	//Rect rect_mask_fly;

	//if (maskOfBulletSprite != nullptr && m_pPlayer->m_pPlayerSpr != nullptr)
	//{
		rect_player = m_pPlayer->m_pPlayerSpr->getBoundingBox();
		rect_mask_bullet = maskOfBulletSprite->getBoundingBox();
//		rect_mask_fly = maskOfFlySprite->getBoundingBox();

		bool hit = rect_player.intersectsRect(rect_mask_bullet);
	//	bool hit2 = rect_player.intersectsRect(rect_mask_fly);

		if (hit)
		{
			m_getMaskflag = true;
			m_getMaskOfBulletFlag = true;
			m_getMaskOfFlyFlag = false;
			exp_num = 100;	// �e�̐����Z�b�g
			geji->setPercentage(exp_num);
			log("hithit");
		}
		//if (hit2)
		//{
		//	m_getMaskflag = true;
		//	m_getMaskOfBulletFlag = false;
		//	m_getMaskOfFlyFlag = true;
		//	log("hit2hit2");
		//}
	//}
		//
	//if (m_pbaseMask != nullptr && m_pbaseMask->m_mask != nullptr)
	//{
		//
		//rect_mask = m_pbaseMask->m_mask->getBoundingBox();
		//if (rect_mask.intersectsRect(rect_player))[
		//if(rect_mask.intersectsRect(rect_player))
		//{
		//	// �}�X�N������
		//	/*m_pbaseMask->removeFromParent();
		//	m_pbaseMask = nullptr;*/
		//	// �t���O�𗧂Ă�
		//	m_getMaskflag = true;
		//	CCLOG("HIT");
		//}
	//}


	//---------------------------------------------------------------
	// �v���C���[�ƓG�̓����蔻��
		Rect rect_enemy;
		rect_enemy= m_pEnemy->m_enemy->getBoundingBox();

		bool hit2 = rect_player.intersectsRect(rect_enemy);
		if (hit2)
		{
			if (m_getMaskOfBulletFlag != true)
			{
				//�Q�[���I�[�o�[
				menuMoveCallback();
			}
			if (m_getMaskOfBulletFlag == true)
			{
				m_getMaskOfBulletFlag == false;
				getMaskIcon->setVisible(false);
			}
		}

	//---------------------------------------------------------------
	// �}�X�N�̃|�W�V�������Z�b�g
		if (maskOfBulletSprite->getPositionX() <= -100)// ||
			//maskOfFlySprite->getPositionX() <= -100)
		{
			maskOfBulletSprite->setPositionX(1100);
//			maskOfFlySprite->setPositionX(1100);
		}

	

	//---------------------------------------------------------------
	// �}�X�N�o���b�g�̃Q�[�W
		// ���݂̒e�����擾
		exp_num = geji->getPercentage();
		// �Q�[�W�ɐݒ肵�Ă�
		geji->setPercentage(exp_num);


	//---------------------------------------------------------------
	// �}�X�N���擾�����Ƃ��A�A�C�R�����ڂ���
		if (m_getMaskOfBulletFlag == true)
		{
//			// �}�X�N���c���Ă���΃}�X�N�A�C�R�����폜
//			if (getMaskIcon)
//			{
//				getMaskIcon->removeFromParent();
//			}
			// �}�X�N���c���Ă��Ȃ���΃}�X�N�A�C�R����z�u
			//if (getMaskIcon == nullptr)
			//{
				getMaskIcon->setVisible(true);
			//}
		}
		if (exp_num <= 0)
		{
			getMaskIcon->setVisible(false);
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


		if (m_getMaskOfBulletFlag /*&& m_pbaseMask != nullptr*/
			&& exp_num > 0)
		{
			// mask power
			/*m_pbaseMask->*/MaskActionBullet();


			//�e�𔭎˂�����Q�[�W�����炷
			exp_num = exp_num += -10;
			geji->setPercentage(exp_num);

		}
		//if (m_getMaskOfFlyFlag)
		//{
		//	MaskActionFly();
		//}
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
	//m_pbaseMask = MaskOfBullet::create();
	//m_pbaseMask->m_mask = Sprite::create("mask1.png");
	//m_pbaseMask->getPosition();
	//m_pbaseMask->GetPos(m_pPlayer->m_pPlayerSpr->getPosition());
	//this->addChild(m_pbaseMask);
	//
	////test1 = Sprite::create("emeny.png");
	////this->addChild(test1);
	//
	//b2BodyDef BodyDef;
	//b2FixtureDef FixtureDef;
	//b2PolygonShape dynamicBox;
	//
	//BodyDef.type = b2_dynamicBody;
	//BodyDef.userData = m_pbaseMask->m_mask;
	//BodyDef.position.Set(m_pbaseMask->m_mask->getPosition().x,
	//	m_pbaseMask->m_mask->getPosition().y);
	//m_maskBody = m_pWorld->CreateBody(&BodyDef);
	//FixtureDef.shape = &dynamicBox;
	//m_maskBody->CreateFixture(&FixtureDef);
	//
	//m_maskBody->SetGravityScale(0.f);
	//
	//
	//b2Vec2 impulse(-5, -0.5f);
	//b2Vec2 point = m_maskBody->GetWorldCenter();
	//m_maskBody->ApplyLinearImpulse(impulse, point, true);
	//
	//
//	//switch (1)
//	//{
//	//case 0:
//	//	m_pbaseMask->m_mask->runAction(goJump);
//	//	break;
//	//case 1:
//	//	m_pbaseMask->m_mask->runAction(goJump2);
//	//	break;
//	//case 2:
//	//	m_pbaseMask->m_mask->runAction(goJump3);
//	//	break;
//	//}
	//
	//
	//// ���ʉ���炷=======================================================
	//int soundID;
	//soundID = SimpleAudioEngine::sharedEngine()->playEffect("sound||se_maoudamashii_system48.mp3");
	////=======================================================================

//	m_maskSprites->MaskOfBulletSprite();
	ChoiceToMaskOfBulletSprite();

}

void MainScene::RemoveMask()
{
	//]://Vec2 pos = m_pbaseMask->m_mask->getPosition();
	//]:m_pWorld->DestroyBody(m_maskBody);
	//]:m_maskBody = nullptr;
	//]:
	//]:m_pbaseMask->removeFromParent();
	//]:m_pbaseMask = nullptr;
}

void MainScene::ChoiceToMaskOfBulletSprite()
{
	CCLOG("MaskSprites::MaskOfBulletSprite()");

	maskOfBulletSprite = Sprite::create("mask1.png");
	maskOfBulletSprite->setPosition(1100, 400);
	maskOfBulletSprite->setScale(0.8);
	this->addChild(maskOfBulletSprite);

	//maskOfFlySprite = Sprite::create("mask1.png");
	//maskOfFlySprite->setPosition(400, 400);
	//this->addChild(maskOfFlySprite);
}

void MainScene::RoopToMaskMove(float dt)
{
	auto actionMoveTo = MoveTo::create(5.0f, Vec2(-100, 400));
//	auto actionJumpBy = JumpBy::create(5,Vec2(-1500,50),0,50);

//	srand((unsigned int)time(NULL));
//	int actionRandNum = rand() % 3;


	// Action
	switch (0)
	{
	case 0:
		maskOfBulletSprite-> runAction(actionMoveTo);
		break;
	case 1:
		maskOfFlySprite->runAction(actionMoveTo);
		break;
	case 2:
		break;
	}
}

void MainScene::MaskActionBullet()
{
	// �A�N�V�����i�X�N���[���j
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);

	//this->m_pPlayer->ToShootBullet();
	CCLOG("aaaaaaaaaaaaaa");

	Sprite* bullet = Sprite::create();
	bullet->setPosition(m_pPlayer->m_pPlayerSpr->getPosition()/*.x/PTM_RATIO,getPosition().y/PTM_RATIO*/);
	//bullet->setRotationY(90);
	//bullet->setTag(BULLET);
	this->addChild(bullet);
	auto actionMoveBym_bgLeft = MoveBy::create(1, Vec2(1000, 0));
	bullet->runAction(actionMoveBym_bgLeft);


	//�X�v���C�g�t���[���L���b�V�����쐬����
	auto cacher = SpriteFrameCache::getInstance();

	//�v���Z�b�g��ǂݍ���

	cacher->addSpriteFramesWithFile("bullet.plist");

	//auto spriteMinion = Sprite::create("minion.png");

	//�摜��z��ɓǂݍ���
	Vector<cocos2d::SpriteFrame*> frames;

	for (int i = 0; i < 8; i++)
	{
		std::stringstream ss;
		ss << "bullet000" << i;
		ss << ".png";
		/*std::cout << std::setfill('0');*/

		/*ss << "runner" << i << ".png";*/
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
	}


	//�A�j���[�V�������쐬����
	auto anim = Animation::createWithSpriteFrames(frames, 0.1f);
	//�A�j���[�V�����A�N�V�������쐬����
	auto action = Animate::create(anim);

	//�i�v�ɌJ��Ԃ��A�N�V�������쐬����
	auto anime = RepeatForever::create(action);

	//�A�N�V���������s����
	//bullet->runAction(anime);

	Sequence* allAction = Sequence::create(anime, actionMoveBym_bgLeft, nullptr);

	bullet->runAction(anime);
}

void MainScene::MaskActionFly()
{
	m_pPlayer->twoJump();
}

void MainScene::menuMoveCallback()
{
	// ���ʉ���炷=======================================================
	int soundID;
	soundID = SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system47.mp3");
	//=======================================================================

	auto nextScene = GameOverScene::createScene();
	auto transition = TransitionFade::create(1.5f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//Director::getInstance()->replaceScene(MainScene::createScene());
}
