#include "CutInOfStart.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

const int TIME = 60;
const int TIME_COUNT = 6;	//6秒


Scene* CutInOfStart::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CutInOfStart::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool CutInOfStart::init()
{
	m_time = 0;
	m_timeCount = 0;
	m_timeflag = false;
	cutInAction();
	this->scheduleUpdate();
	return true;
}

void CutInOfStart::update(float dt)
{
	// タイム更新
	m_time++;

	if (m_time >= TIME)
	{
		m_time = 0;
		m_timeCount ++;
	}

	// カットシーンフラグを立てる-----------------------------------
	if (m_timeCount >= TIME_COUNT)
	{
		m_timeflag = true;
	}
}

// =================================
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 関数名：カットイン演出
// 引　数：なし
// 戻り値：なし
// 概　要：
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// =================================
void CutInOfStart::cutInAction()
{
	Sprite* playerACutInSprite_3;
	playerACutInSprite_3 = Sprite::create("CutInStart/Three.png");
	playerACutInSprite_3->setPosition(Vec2(960.f / 2, 640.f / 2));
	playerACutInSprite_3->setScale(0);
	this->addChild(playerACutInSprite_3);
	auto playerActionScaleOut3 = ScaleTo::create(0.f, 3.0f);
	auto playerActionScaleIn3 = ScaleTo::create(0.0f, 0.f);
	DelayTime* playerADelay_3_1 = DelayTime::create(2.0f);
	DelayTime* playerADelay_3_2 = DelayTime::create(0.5f);
	Sequence* playerASeq_3 = Sequence::create(playerADelay_3_1,
		playerActionScaleOut3,playerADelay_3_2, playerActionScaleIn3, nullptr);
	playerACutInSprite_3->runAction(playerASeq_3);

	Sprite* playerACutInSprite_2;
	playerACutInSprite_2 = Sprite::create("CutInStart/Two.png");
	playerACutInSprite_2->setPosition(Vec2(960.f / 2, 640.f / 2));
	playerACutInSprite_2->setScale(0);
	this->addChild(playerACutInSprite_2);
	auto playerActionScaleOut2 = ScaleTo::create(0.f, 3.0f);
	auto playerActionScaleIn2 = ScaleTo::create(0.0f, 0.f);
	DelayTime* playerADelay_2_1 = DelayTime::create(3.0f);
	DelayTime* playerADelay_2_2 = DelayTime::create(0.5f);
	Sequence* playerASeq_2 = Sequence::create(playerADelay_2_1, 
		playerActionScaleOut2, playerADelay_2_2, playerActionScaleIn2, nullptr);
	playerACutInSprite_2->runAction(playerASeq_2);

	Sprite* playerACutInSprite_1;
	playerACutInSprite_1 = Sprite::create("CutInStart/One.png");
	playerACutInSprite_1->setPosition(Vec2(960.f / 2, 640.f / 2));
	playerACutInSprite_1->setScale(0);
	this->addChild(playerACutInSprite_1);
	auto playerActionScaleOut1 = ScaleTo::create(0.f, 3.0f);
	auto playerActionScaleIn1 = ScaleTo::create(0.0f, 0.f);
	DelayTime* playerADelay_1_1 = DelayTime::create(4.0f);
	DelayTime* playerADelay_1_2 = DelayTime::create(0.5f);
	Sequence* playerASeq_1 = Sequence::create(playerADelay_1_1, 
		playerActionScaleOut1, playerADelay_1_2, playerActionScaleIn1, nullptr);
	playerACutInSprite_1->runAction(playerASeq_1);

	Sprite* playerACutInSprite_Go;
	playerACutInSprite_Go = Sprite::create("CutInStart/Start.png");
	playerACutInSprite_Go->setPosition(Vec2(960.f / 2, 640.f / 2));
	playerACutInSprite_Go->setScale(0);
	this->addChild(playerACutInSprite_Go);
	auto playerAActionScaleOutGo = ScaleTo::create(0.f, 3.0f);
	auto playerAActionScaleInGo = ScaleTo::create(0.0f, 0.f);
	DelayTime* playerADelay_Go_1 = DelayTime::create(5.0f);
	DelayTime* playerADelay_Go_2 = DelayTime::create(0.5f);
	Sequence* playerASeq_Go = Sequence::create(playerADelay_Go_1, 
		playerAActionScaleOutGo, playerADelay_Go_2, playerAActionScaleInGo, nullptr);
	playerACutInSprite_Go->runAction(playerASeq_Go);
}

void CutInOfStart::setCutInFlag(bool flag)
{
	m_timeflag = flag;
}

bool CutInOfStart::getCutinFlag()
{
	return m_timeflag;
}

CutInOfStart* CutInOfStart::create()
{
	CutInOfStart* ret = new (std::nothrow) CutInOfStart();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		ret = nullptr;
		return nullptr;
	}
}
