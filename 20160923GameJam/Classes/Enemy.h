#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_enemy;
	//cocos2d::Sprite* m_bgRight;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt)override;

	CREATE_FUNC(Enemy);
};

#endif // __HELLOWORLD_SCENE_H__
