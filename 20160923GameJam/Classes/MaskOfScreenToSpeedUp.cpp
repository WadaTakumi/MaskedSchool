//--ƒCƒ“ƒNƒ‹[ƒh----------------------------------------------------//
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "MaskOfScreenToSpeedUp.h"

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
bool MaskOfScreenToSpeedUp::init()
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
y‹@”\z
ƒ}ƒXƒN‚Ì”\—Í‚ðŽg‚¤(2‰ñƒWƒƒƒ“ƒv)
yˆø”z
–³‚µ
y–ß’lz
–³‚µ
*/
void MaskOfScreenToSpeedUp::MaskAction()
{
	// ƒAƒNƒVƒ‡ƒ“iƒXƒNƒ[ƒ‹j
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);

	this->m_pBackgroundLayer->changeScreenSpeed();
}