/*
*
*背景レイヤー。
*
*/


#include "BackgroundLayer.h"

USING_NS_CC;

using namespace std;

/**
* 初期化する。
*
* @return 成功したらtrue、失敗ならfalse
*/

bool BackgroundLayer::init()
{
	//////////////////////////////
	// 1.親クラスの初期化
	if (!Layer::init())
	{
		return false;
	}

	//srand((unsigned int)time(NULL));


	m_visiblenum = 0;
	m_spd = 0;
	m_num = 0;
	m_actOfRestoringSpeedFlag = false;

	//画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < 5; i++)
	{
		_groupe[i] = Node::create();
		this->addChild(_groupe[i]);
		_groupe[i]->setPosition(this->getContentSize().width*i, 0);
		if (i >= 2)
		{
			_groupe[i]->setVisible(false);
		}
	}

	//デバッグ
	/////////////////////////////////////
	for (int i = 0; i < 5; i++)
	{
		// マップの表示
		map = TMXTiledMap::create("stage1.tmx");
		map->setAnchorPoint(Vec2::ZERO);
		map->setPosition(Vec2(0, 0));
		_groupe[i]->addChild(map);

		//// オブジェクトを読み出す
		//// オブジェクトグループを読み出す
		//auto group = map->getObjectGroup("objects");
		//// オブジェクトリストを読み出す
		//auto objects = group->getObjects();
		//// オブジェクトを１つずつ取り出す
		//for (auto object : objects)
		//{
		//	// Value型をValueMap型として使う
		//	ValueMap objectInfo = object.asValueMap();

		//	float x = objectInfo.at("x").asFloat();
		//	float y = objectInfo.at("y").asFloat();
		//	int type = objectInfo.at("type").asInt();

		//	
		//	Sprite* sprite = createsprite(type);
		//	sprite->setTag(type);
		//	sprite->setPosition(Vec2(x, y));
		//	_groupe[i]->addChild(sprite);

		//}
	}

	schedule(schedule_selector(BackgroundLayer::update), 0.05f);

	return true;


}


void BackgroundLayer::update(float dt)
{
	m_spd += 15.0f;
	m_num = 15.0f;

	for (int i = 0; i < 5; i++)
	{
		_groupe[i]->setPosition(_groupe[i]->getPosition().x - m_num, 0);
	}

	int num = m_spd / this->getContentSize().width;

	if (m_visiblenum != num)
	{
		for (int i = 0; i < 5; i++)
		{
			if (num == i || num + 1 == i)
			{
				_groupe[i]->setVisible(true);
			}
			else
			{
				_groupe[i]->setVisible(false);
			}
		}

		m_visiblenum = num;

		if (m_visiblenum == 3)
		{
			m_visiblenum = 0;
			m_spd = 0;
			this->Shuffle();
		}
	}

	// もし背景速度上昇マスクを取ったなら、
	// 3秒間背景を加速して、元に戻す
	if (m_actOfRestoringSpeedFlag == true)
	{
		int time = 0;
		time++;
		
		// 3秒
		if (time >= 180)
		{
			m_actOfRestoringSpeedFlag = false;
			m_spd += 13.0f;
			m_num = 13.0f;
		}
	}
}

/**
* プレーヤーとオブジェクトとのあたり判定。
*
* @param playerRect プレーヤーの境界矩形
*/
void BackgroundLayer::collide(Rect playerRect)
{

	Vector<Node*> children = _groupe[0]->getChildren();

	// オブジェクトを１つずつ取り出す
	for (auto sprite : children)
	{
		if (sprite->getTag() == 1)
		{

		}
		else if (sprite->getTag() != 1)
		{
			// オブジェクトの境界矩形
			auto objectBoundingBox = sprite->getBoundingBox();

			// 矩形判定法で当たり判定をする。
			if (objectBoundingBox.intersectsRect(playerRect))
			{
				//ゲームオーバー
			}
		}
	}
}

void BackgroundLayer::Shuffle()
{
	Node* memo = _groupe[0];
	_groupe[0] = _groupe[4];
	_groupe[4] = memo;

	for (int i = 0; i < 10; i++)
	{
		int num = random(2,3);
		memo = _groupe[1];
		_groupe[1] = _groupe[num];
		_groupe[num] = memo;
	}

	for (int i = 0; i < 5; i++)
	{
		_groupe[i]->setPosition(this->getContentSize().width*i, 0);
		if (i >= 2)
		{
			_groupe[i]->setVisible(false);
		}
		else
		{
			_groupe[i]->setVisible(true);
		}
	}
}

// 背景スクロールの速度を速くする
void BackgroundLayer::changeScreenSpeed()
{
	m_spd += 15.0f;
	m_num = 15.0f;
	m_actOfRestoringSpeedFlag = true;
}