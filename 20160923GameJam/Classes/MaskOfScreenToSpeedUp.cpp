//--インクルード----------------------------------------------------//
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
【機能】
初期化
【引数】
無し
【戻値】
無し
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
【機能】
マスクの能力を使う(2回ジャンプ)
【引数】
無し
【戻値】
無し
*/
void MaskOfScreenToSpeedUp::MaskAction()
{
	// アクション（スクロール）
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);

	this->m_pBackgroundLayer->changeScreenSpeed();
}