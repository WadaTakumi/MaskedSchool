/*
*
*�w�i���C���[�B
*
*/


#include "BackgroundLayer.h"

USING_NS_CC;

using namespace std;

/**
* ����������B
*
* @return ����������true�A���s�Ȃ�false
*/

bool BackgroundLayer::init()
{
	//////////////////////////////
	// 1.�e�N���X�̏�����
	if (!Layer::init())
	{
		return false;
	}

	//srand((unsigned int)time(NULL));


	m_visiblenum = 0;
	m_spd = 0;
	m_num = 0;
	m_actOfRestoringSpeedFlag = false;

	//��ʃT�C�Y�̎擾
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

	//�f�o�b�O
	/////////////////////////////////////
	for (int i = 0; i < 5; i++)
	{
		// �}�b�v�̕\��
		map = TMXTiledMap::create("stage1.tmx");
		map->setAnchorPoint(Vec2::ZERO);
		map->setPosition(Vec2(0, 0));
		_groupe[i]->addChild(map);

		//// �I�u�W�F�N�g��ǂݏo��
		//// �I�u�W�F�N�g�O���[�v��ǂݏo��
		//auto group = map->getObjectGroup("objects");
		//// �I�u�W�F�N�g���X�g��ǂݏo��
		//auto objects = group->getObjects();
		//// �I�u�W�F�N�g���P�����o��
		//for (auto object : objects)
		//{
		//	// Value�^��ValueMap�^�Ƃ��Ďg��
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

	// �����w�i���x�㏸�}�X�N��������Ȃ�A
	// 3�b�Ԕw�i���������āA���ɖ߂�
	if (m_actOfRestoringSpeedFlag == true)
	{
		int time = 0;
		time++;
		
		// 3�b
		if (time >= 180)
		{
			m_actOfRestoringSpeedFlag = false;
			m_spd += 13.0f;
			m_num = 13.0f;
		}
	}
}

/**
* �v���[���[�ƃI�u�W�F�N�g�Ƃ̂����蔻��B
*
* @param playerRect �v���[���[�̋��E��`
*/
void BackgroundLayer::collide(Rect playerRect)
{

	Vector<Node*> children = _groupe[0]->getChildren();

	// �I�u�W�F�N�g���P�����o��
	for (auto sprite : children)
	{
		if (sprite->getTag() == 1)
		{

		}
		else if (sprite->getTag() != 1)
		{
			// �I�u�W�F�N�g�̋��E��`
			auto objectBoundingBox = sprite->getBoundingBox();

			// ��`����@�œ����蔻�������B
			if (objectBoundingBox.intersectsRect(playerRect))
			{
				//�Q�[���I�[�o�[
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

// �w�i�X�N���[���̑��x�𑬂�����
void BackgroundLayer::changeScreenSpeed()
{
	m_spd += 15.0f;
	m_num = 15.0f;
	m_actOfRestoringSpeedFlag = true;
}