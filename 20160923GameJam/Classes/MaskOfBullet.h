#ifndef __MAASK_OF_BULLET_H__
#define __MAASK_OF_BULLET_H__

#include "cocos2d.h"

class MaskOfBullet : public cocos2d::Layer
{
private:

	cocos2d::Sprite* m_mask;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
	//void update(float dt)override;

	CREATE_FUNC(MaskOfBullet);
};

#endif // __HELLOWORLD_SCENE_H__