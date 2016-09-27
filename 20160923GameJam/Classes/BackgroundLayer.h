/*
* 背景レイヤー。
*
* Copyirght (C) 2015 Takao Wada.
*/
#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__

#include "cocos2d.h"

#define CHIP_WIDTH	32
#define CHIP_HEIGHT	32

/*
* 背景レイヤー。
*/
class BackgroundLayer : public cocos2d::Layer
{
private:
	int visiblenum;

	float spd;

	// タイルマップ
	cocos2d::TMXTiledMap* map;

	//敵やマスクなどのものを記憶するノード
	cocos2d::Node* _groupe[5];

	cocos2d::Sprite* createsprite(int num);

	void Shuffle();

public:
	// インスタンスの作成
	CREATE_FUNC(BackgroundLayer);

	// インスタンスの初期化
	virtual bool init();

	void update(float dt);

	void collide(cocos2d::Rect playerRect);
};

#endif // __BACKGROUNDLAYER_H__
