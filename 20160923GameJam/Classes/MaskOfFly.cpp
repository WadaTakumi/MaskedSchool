//--�C���N���[�h----------------------------------------------------//
#include "ui/CocosGUI.h"
#include "MaskOfFly.h"
#include "Box2D/Box2D.h"
//#include "DebugDrawNode.h"
//#include "QueryCallback.h"

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
bool MaskOfFly::init()
{

	m_mask = Sprite::create("mask1.png");
	m_mask->setPosition(Vec2(1200,random(300,640)));
	this->addChild(m_mask);

	auto actionMoveBym_bgLeft = MoveTo::create(4, Vec2(0, m_mask->getPosition().y));
	m_mask->runAction(actionMoveBym_bgLeft);

	return true;
}

//**************************************************************************************
//  MaskAction
//**************************************************************************************
//--------------------------------------------------------------------------------------
/*
�y�@�\�z
�}�X�N�̔\�͂��g��(2��W�����v)
�y�����z
����
�y�ߒl�z
����
*/
void MaskOfFly::MaskAction()
{
	// �A�N�V�����i�X�N���[���j
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);

	//this->m_pPlayer->jump();
}