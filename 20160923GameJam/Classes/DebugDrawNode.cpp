#include "DebugDrawNode.h"
#include "GLES-Render.h"

USING_NS_CC;

const int PTM_RATIO = 32;

DebugDrawNode::DebugDrawNode()
{
}


DebugDrawNode::~DebugDrawNode()
{
}

// �C���X�^���X����
DebugDrawNode* DebugDrawNode::create(b2World* world) 
{
	DebugDrawNode* pRet = new(std::nothrow)DebugDrawNode();
	if (pRet && pRet->init(world))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

// ������
bool DebugDrawNode::init(b2World* world)
{
	// ���N���X�̏�����
	if (!Node::init())
	{
		return false;
	}
	// �\���Ώۂ̕������[���h
	m_pWorld = world;

	m_pDraw = new GLESDebugDraw(PTM_RATIO);

	// �S��ޕ\���i�Sbit�}�X�N�j
	uint32 flags = 0xffffffff;
	m_pDraw -> SetFlags(flags);
	
	// �\���p�C���X�^���X�����[���h�ɃZ�b�g
	m_pWorld->SetDebugDraw(m_pDraw);

	return true;
}

// �\���֐����I�[�o�[���[�h
void DebugDrawNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	// �������[���h���f�o�b�O�\��
	//m_pWorld->DrawDebugData();

	m_Command.init(this->getGlobalZOrder());
	m_Command.func = CC_CALLBACK_0(DebugDrawNode::onDraw, this);

	renderer->addCommand(&m_Command);

}

void DebugDrawNode::onDraw()
{
	// �������[���h���f�o�b�O�\��
	//m_pWorld->DrawDebugData();
}
