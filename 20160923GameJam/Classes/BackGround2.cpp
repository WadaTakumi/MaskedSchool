#include "BackGround2.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool BackGround2::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();


	m_bgLeft = Sprite::create("bg2left.png");
	m_bgLeft->setPosition(Vec2((visibleSize.width / 2 - (visibleSize.width / 2 /2/1.46)),
		(visibleSize.height / 2)));
	this->addChild(m_bgLeft);

	m_bgRight = Sprite::create("bg2Right.png");
	m_bgRight->setPosition(Vec2((visibleSize.width / 2 + (visibleSize.width / 2 /2/1.46)),
		(visibleSize.height / 2)));
	this->addChild(m_bgRight);


	// �A�N�V�����i�X�N���[���j
	auto actionMoveBym_bgLeft = MoveBy::create(70.0, Vec2(-1500, 0));
	m_bgLeft->runAction(actionMoveBym_bgLeft);
	auto actionMoveBym_bgRight = MoveBy::create(70.0, Vec2(-1500, 0));
	m_bgRight->runAction(actionMoveBym_bgRight);

	
	// �摜���J��ւ���
	if (m_bgLeft->getPositionX() < 0)
	{
		log("�C�q�q����");
	}

	scheduleUpdate();


	return true;
}

void BackGround2::update(float dt)
{

}