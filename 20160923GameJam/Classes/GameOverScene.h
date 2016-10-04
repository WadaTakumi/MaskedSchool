#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "GLES-Render.h"
#include "MainScene.h"
#include "MenuScreenScene.h"
//#include "cocos2d/cocos/ui/UIButton.h"

class GameOverScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void initPhysics();

	void update(float dt);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *unused_event);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCloseCallback2(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

private:
	

};

#endif // __HELLOWORLD_SCENE_H__
