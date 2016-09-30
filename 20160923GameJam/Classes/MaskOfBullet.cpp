//--�C���N���[�h----------------------------------------------------//
#include "MaskOfBullet.h"
#include "ui/CocosGUI.h"
#include "BaseMask.h"
#include "Character.h"

USING_NS_CC;

//**************************************************************************************
//  init
//**************************************************************************************
//--------------------------------------------------------------------------------------
/*
�y�@�\�z
������
�y�����z
����
�y�ߒl�z
����
*/
bool MaskOfBullet::init()
{

	m_mask = Sprite::create("mask1.png");
	m_mask->setPosition(Vec2((960 / 2) + 350, (640 / 2) + 200));
	this->addChild(m_mask);


	return true;
}

//**************************************************************************************
//  MaskAction
//**************************************************************************************
//--------------------------------------------------------------------------------------
/*
�y�@�\�z
�}�X�N�̔\�͂��g��(�e��ł�)
�y�����z
����
�y�ߒl�z
����
*/
void MaskOfBullet::MaskAction()
{
	// �A�N�V�����i�X�N���[���j
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);
	
	//this->m_pPlayer->ToShootBullet();
	CCLOG("aaaaaaaaaaaaaa");
	
	Sprite* bullet = Sprite::create();
	bullet->setPosition(Vec2(300,400));
	//bullet->setRotationY(90);
	//bullet->setTag(BULLET);
	this->addChild(bullet);
	auto actionMoveBym_bgLeft = MoveTo::create(1,Vec2(1000, 300));
	bullet->runAction(actionMoveBym_bgLeft);


	//�X�v���C�g�t���[���L���b�V�����쐬����
	auto cacher = SpriteFrameCache::getInstance();

	//�v���Z�b�g��ǂݍ���

	cacher->addSpriteFramesWithFile("bullet.plist");

	//auto spriteMinion = Sprite::create("minion.png");

	//�摜��z��ɓǂݍ���
	Vector<cocos2d::SpriteFrame*> frames;

	for (int i = 0; i < 8; i++)
	{
		std::stringstream ss;
		ss << "bullet000" << i;
		ss << ".png";
		/*std::cout << std::setfill('0');*/

		/*ss << "runner" << i << ".png";*/
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
	}


	//�A�j���[�V�������쐬����
	auto anim = Animation::createWithSpriteFrames(frames, 0.1f);
	//�A�j���[�V�����A�N�V�������쐬����
	auto action = Animate::create(anim);

	//�i�v�ɌJ��Ԃ��A�N�V�������쐬����
	auto anime = RepeatForever::create(action);

	//�A�N�V���������s����
	//bullet->runAction(anime);

	Sequence* allAction = Sequence::create(anime, actionMoveBym_bgLeft,  nullptr);

	bullet->runAction(anime);

}