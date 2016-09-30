//--インクルード----------------------------------------------------//
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
【機能】
初期化
【引数】
無し
【戻値】
無し
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
【機能】
マスクの能力を使う(弾を打つ)
【引数】
無し
【戻値】
無し
*/
void MaskOfBullet::MaskAction()
{
	// アクション（スクロール）
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


	//スプライトフレームキャッシュを作成する
	auto cacher = SpriteFrameCache::getInstance();

	//プリセットを読み込む

	cacher->addSpriteFramesWithFile("bullet.plist");

	//auto spriteMinion = Sprite::create("minion.png");

	//画像を配列に読み込む
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


	//アニメーションを作成する
	auto anim = Animation::createWithSpriteFrames(frames, 0.1f);
	//アニメーションアクションを作成する
	auto action = Animate::create(anim);

	//永久に繰り返すアクションを作成する
	auto anime = RepeatForever::create(action);

	//アクションを実行する
	//bullet->runAction(anime);

	Sequence* allAction = Sequence::create(anime, actionMoveBym_bgLeft,  nullptr);

	bullet->runAction(anime);

}