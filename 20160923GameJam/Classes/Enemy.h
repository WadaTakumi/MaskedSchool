#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "cocos2d\cocos\2d\CCSpriteFrame.h"

enum EnemyType
{
	CAR = 0,		// Fast mover
	BIRD = 1,		// Flying
	TEMP = 2,		// Jumping (TBD)
};
class Enemy : public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_enemy;
	EnemyType m_type;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_flyingFrames;
	//cocos2d::Sprite* m_bgRight;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt)override;

	CREATE_FUNC(Enemy);
};

#endif // __HELLOWORLD_SCENE_H__
