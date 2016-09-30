#ifndef __ENEMY_DATA_H__
#define __ENEMY_DATA_H__

#include "cocos2d.h"
#include "cocos2d\cocos\2d\CCSpriteFrame.h"
#include "Enemy.h"

USING_NS_CC;

struct EnemyData
{
	enum EnemyType
	{
		GROUND = 0,		// Fast mover
		FLYING = 1,		// Flying
		JUMPING = 2,		// Jumping (TBD)
	};

	static EnemyData* initEnemies()
	{
		auto data = new EnemyData();
		// Init GROUND type enemy
		data->m_ground = Sprite::create("PixelCar.png");
		data->m_ground->setScale(1.2f);
		data->m_ground->setPosition(Vec2((960 / 2) + 850, (640 / 2)));

		////////////////////////////////////////////////////////////
		// init BIRD type enemy
		char str[100];
		// Load chicken animation
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/flying.plist");
		for (int i = 0; i < 3; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "frame-%d.png", i);
			data->m_birdFlyingFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		// Default BIRD type enemy animation
		auto animation = Animation::createWithSpriteFrames(data->m_birdFlyingFrames, 0.07f);
		data->m_flyingAnimation = Animate::create(animation);
		data->m_flyingAnimation->setTag(1);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/hit.plist");
		for (int i = 0; i < 1; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "frame-%d.png", i);
			data->m_birdHitFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		// Activate this when a BIRD type enemy gets hit
		animation = Animation::createWithSpriteFrames(data->m_birdHitFrames, 0.07f);
		data->m_hitAnimation = Animate::create(animation);
		data->m_hitAnimation->setTag(2);

		data->m_flying = Sprite::createWithSpriteFrame(data->m_birdFlyingFrames.front());
		data->m_flying->setScale(0.15f);
		data->m_flying->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));

		////////////////////////////////////////////////////////////////////////
		// Init JUMPING type enemy
		data->m_jumping = Sprite::create("food.png");
		data->m_jumping->setPosition(Vec2((960 / 2) + 850, (640 / 2)));
		data->m_jumping->setScale(0.15f);

		return data;
	}

	Sprite* getGroundEnemy() { return m_ground; }
	Sprite* getFlyingEnemy() { return m_flying; }
	Sprite* getJumpingEnemy() { return m_jumping; }
	Sprite* getRandomEnemy(int type)
	{
		if (type == GROUND)
			return m_ground;
		else if (type == FLYING)
			return m_flying;
		else if (type == JUMPING)
			return m_jumping;
		else
			return nullptr;
	}
	Animate* getFlyingAnimation() { return m_flyingAnimation; }
	Animate* getHitAnimation() { return m_hitAnimation; }

	Sprite* m_ground;
	Sprite* m_flying;
	Sprite* m_jumping;
	Animate* m_flyingAnimation;
	Animate* m_hitAnimation;
	Vector<SpriteFrame*> m_birdFlyingFrames;
	Vector<SpriteFrame*> m_birdHitFrames;
};

#endif