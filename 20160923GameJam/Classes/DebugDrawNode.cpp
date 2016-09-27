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

// インスタンス生成
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

// 初期化
bool DebugDrawNode::init(b2World* world)
{
	// 基底クラスの初期化
	if (!Node::init())
	{
		return false;
	}
	// 表示対象の物理ワールド
	m_pWorld = world;

	m_pDraw = new GLESDebugDraw(PTM_RATIO);

	// 全種類表示（全bitマスク）
	uint32 flags = 0xffffffff;
	m_pDraw -> SetFlags(flags);
	
	// 表示用インスタンスをワールドにセット
	m_pWorld->SetDebugDraw(m_pDraw);

	return true;
}

// 表示関数をオーバーロード
void DebugDrawNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	// 物理ワールドをデバッグ表示
	//m_pWorld->DrawDebugData();

	m_Command.init(this->getGlobalZOrder());
	m_Command.func = CC_CALLBACK_0(DebugDrawNode::onDraw, this);

	renderer->addCommand(&m_Command);

}

void DebugDrawNode::onDraw()
{
	// 物理ワールドをデバッグ表示
	//m_pWorld->DrawDebugData();
}
