#ifndef __BACKGROUND3_H__
#define __BACKGROUND3_H__

#include "cocos2d.h"

class BackGround3 : public cocos2d::Layer
{
private:

	cocos2d::Sprite* Bg;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
	//void update(float dt)override;

	CREATE_FUNC(BackGround3);
};

#endif // __HELLOWORLD_SCENE_H__
