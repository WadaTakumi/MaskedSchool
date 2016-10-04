#include "Enemy.h"
#include "ui/CocosGUI.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

const int PTM_RATIO = 32;

bool Enemy::init(b2World* world)
{
	m_world = world;

	m_type = static_cast<EnemyData::EnemyType>(RandomHelper::random_int(0, 2));

	//m_enemy = data->getEnemyByType(m_type);

	if (m_type == EnemyData::GROUND)
	{
		// Init GROUND type enemy
		m_enemy = Sprite::create("PixelCar.png");
		m_enemy->setScale(0.9f);
		m_enemy->setPosition(Vec2((960 / 2) + 850, 220));
	}

	else if (m_type == EnemyData::FLYING)
	{
		// init BIRD type enemy
		char str[100];
		// Load chicken animation
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/flying.plist");
		for (int i = 0; i < 3; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "frame-%d.png", i);
			m_birdFlyingFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}


		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/hit.plist");
		for (int i = 0; i < 1; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "frame-%d.png", i);
			m_birdHitFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}


		m_enemy = Sprite::createWithSpriteFrame(m_birdFlyingFrames.front());
		m_enemy->setScale(0.15f);
		m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));
	}
	else if (m_type == EnemyData::JUMPING)
	{
		// Init JUMPING type enemy
		m_enemy = Sprite::create("food.png");
		m_enemy->setPosition(Vec2((960 / 2) + 850, 220));
		//m_enemy->setScale(0.225f);
		m_enemy->setScale(0.125f);
	}

	if (!m_enemy)
		return false;

	// Set enemy physics
	b2BodyDef enemyBodyDef;
	b2FixtureDef enemyFixtureDef;
	b2PolygonShape enemyDynamicBox;
	enemyDynamicBox.SetAsBox(1.0f, 1.0f);

	enemyBodyDef.gravityScale = 3.0f;
	enemyFixtureDef.friction = 0.0f;
	enemyBodyDef.type = b2_dynamicBody;
	enemyBodyDef.position.Set(m_enemy->getPosition().x,
							  m_enemy->getPosition().y);
	m_enemyBody = m_world->CreateBody(&enemyBodyDef);
	//m_enemyBody->SetUserData(this); // TODO: fix invisible sprite

	enemyFixtureDef.shape = &enemyDynamicBox;
	m_enemyBody->CreateFixture(&enemyFixtureDef);

	m_hitOnHead = false;
	m_scheduledForRemoval = false;

	//// Set default enemy actions
	//if (m_type == EnemyData::GROUND)
	//{
	//	// Init movement
	//	auto actionMoveByenemy = MoveBy::create(2, Vec2(-1500, 0));
	//	m_enemy->runAction(actionMoveByenemy);
	//}
	//if (m_type == EnemyData::JUMPING)
	//{
	//	// Init movement
	//	auto actionMoveByenemy = MoveBy::create(3, Vec2(-1500, 0));
	//	m_enemy->runAction(actionMoveByenemy);
	//}
	//else if (m_type == EnemyData::FLYING)
	//{
	//	// Init animation and movement
	//	m_enemy->runAction(RepeatForever::create(m_flyingAnimation));
	//	auto actionMoveByEnemy = MoveBy::create(5.0, Vec2(-1500, 0));
	//	m_enemy->runAction(actionMoveByEnemy);
	//}

	this->addChild(m_enemy);

	scheduleUpdate();

	//if (StartSpawnEnemyFlag != false)
	//{
		this->schedule(schedule_selector(Enemy::SpawnEnemy), 1.0f);
	//}
	//if (StartSpawnEnemyFlag != true)
	//{
	//	this->schedule(schedule_selector(Enemy::SpawnEnemy), 2.0f);
	//}

	return true;
}

void Enemy::update(float dt)
{
	// TODO add enemy colliders
	if (m_type == EnemyData::FLYING && m_hitOnHead)
	{
		// Stop default flying animation
		// and start falling animation
		m_enemy->stopActionByTag(1);
		m_enemy->runAction(this->getActionByTag(2));
	}
	else if (dt >= 3.0f && m_type == EnemyData::JUMPING)
	{
		// Init jumping and movement
		b2Vec2 impulse(0, 8.0f);
		b2Vec2 point = m_enemyBody->GetWorldCenter();
		m_enemyBody->ApplyLinearImpulse(impulse, point, true);
	}
	//If(m_enemy.loc == ruudun ulkopuolella)
	//{
	//	  m_scheduledForRemoval = true;
	//}


}

void Enemy::StartSpawnEnemy(float delta)
{
	//if (StartSpawnEnemyFlag != false)
	//{
	//	this->schedule(schedule_selector(Enemy::SpawnEnemy), 2.0f);
	//}
	//StartSpawnEnemyFlag = false;
}

void Enemy::SpawnEnemy(float delta)
{

	// Set default enemy actions
	if (m_type == EnemyData::GROUND)
	{
		// Init movement
		auto actionMoveByenemy = MoveBy::create(2, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByenemy);
	}
	if (m_type == EnemyData::JUMPING)
	{
		// Init movement
		auto actionMoveByenemy = MoveBy::create(3, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByenemy);
	}
	else if (m_type == EnemyData::FLYING)
	{
		// Default BIRD type enemy animation
		auto animation = Animation::createWithSpriteFrames(m_birdFlyingFrames, 0.07f);
		m_flyingAnimation = Animate::create(animation);
		m_flyingAnimation->setTag(1);
		// Activate this when a BIRD type enemy gets hit
		animation = Animation::createWithSpriteFrames(m_birdHitFrames, 0.07f);
		m_hitAnimation = Animate::create(animation);
		m_hitAnimation->setTag(2);
		// Init animation and movement
		m_enemy->runAction(RepeatForever::create(m_flyingAnimation));
		auto actionMoveByEnemy = MoveBy::create(5.0, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByEnemy);
	}
}

Enemy* Enemy::create(b2World* world)
{
	Enemy* enemy = new(std::nothrow) Enemy();
	if (enemy && enemy->init(world))
	{
		enemy->autorelease();
		return enemy;
	}
	else
	{
		delete enemy;
		enemy = nullptr;
		return nullptr;
	}
}