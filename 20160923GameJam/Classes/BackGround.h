#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"

class BackGround : public cocos2d::Layer
{
private:

	cocos2d::Sprite* Bg;
	cocos2d::Sprite* Bg2;
	cocos2d::Sprite* Bg3;
	cocos2d::Sprite* Bg4;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
	//void update(float dt)override;

	CREATE_FUNC(BackGround);
};

#endif // __HELLOWORLD_SCENE_H__
