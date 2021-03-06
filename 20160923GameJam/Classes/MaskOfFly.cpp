//--インクルード----------------------------------------------------//
#include "MaskOfFly.h"
#include "Character.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"

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
【機能】
マスクの能力を使う(2回ジャンプ)
【引数】
無し
【戻値】
無し
*/
void MaskOfFly::MaskAction()
{
	// アクション（スクロール）
	//auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	//m_mask->runAction(actionMoveBym_bgLeft);

	//this->m_pPlayer->jump();

	//b2Vec2 impulse(0, 10.5f);
	//b2Vec2 point = PLAYER->GetWorldCenter();
	//PLAYER->ApplyLinearImpulse(impulse, point, true);
}