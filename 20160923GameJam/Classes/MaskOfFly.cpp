//--ƒCƒ“ƒNƒ‹[ƒh----------------------------------------------------//
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
y‹@”\z
‰Šú‰»
yˆø”z
–³‚µ
y–ß’lz
–³‚µ
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
y‹@”\z
ƒ}ƒXƒN‚Ì”\—Í‚ğg‚¤(2‰ñƒWƒƒƒ“ƒv)
yˆø”z
–³‚µ
y–ß’lz
–³‚µ
*/
void MaskOfFly::MaskAction()
{
	// ƒAƒNƒVƒ‡ƒ“iƒXƒNƒ[ƒ‹j
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);

	//this->m_pPlayer->jump();
}