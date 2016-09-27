/*
* �w�i���C���[�B
*
* Copyirght (C) 2015 Takao Wada.
*/
#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__

#include "cocos2d.h"

#define CHIP_WIDTH	32
#define CHIP_HEIGHT	32

/*
* �w�i���C���[�B
*/
class BackgroundLayer : public cocos2d::Layer
{
private:
	int visiblenum;

	float spd;

	// �^�C���}�b�v
	cocos2d::TMXTiledMap* map;

	//�G��}�X�N�Ȃǂ̂��̂��L������m�[�h
	cocos2d::Node* _groupe[5];

	cocos2d::Sprite* createsprite(int num);

	void Shuffle();

public:
	// �C���X�^���X�̍쐬
	CREATE_FUNC(BackgroundLayer);

	// �C���X�^���X�̏�����
	virtual bool init();

	void update(float dt);

	void collide(cocos2d::Rect playerRect);
};

#endif // __BACKGROUNDLAYER_H__
