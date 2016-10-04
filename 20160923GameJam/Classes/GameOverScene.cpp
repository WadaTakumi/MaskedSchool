#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GLES-Render.h"
//#include "GameOver.h"
#include "cocos2d.h"


USING_NS_CC;
#define PTM_RATIO 32
using namespace experimental;
using namespace cocostudio::timeline;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /*auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);*/


	//画面サイズを取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//マルチレゾリューション
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("GameOver.png");
	//中央に表示されるように座標を設定
	background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//画像を追加　第2引数は表示する順番（背景だから一番下つまり0）
	this->addChild(background, 0);

	

	////イベントリスナーを作成する
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOverScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//タッチを有効にする
	this->setTouchEnabled(true);


	//ボタンを作成
	auto button = MenuItemImage::create(
		"button.png", "buttonPush.png",
		CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
	button->setPosition((960/2)-150, 100);

	auto menu = Menu::create(button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	//ボタンを作成
	auto button2 = MenuItemImage::create(
		"Quit.png", "QuitPush.png",
		CC_CALLBACK_1(GameOverScene::menuCloseCallback2, this));
	button2->setPosition((960 / 2) + 150, 100);

	auto menu2 = Menu::create(button2, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);




	// update関数を１フレームごとに呼び出す
	this->scheduleUpdate();





    return true;
}
void GameOverScene::initPhysics()
{

}
void GameOverScene::update(float dt)
{
	
}

bool GameOverScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void GameOverScene::menuCloseCallback(Ref* pSender)
{

	auto nextScene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainScene::createScene()));

}

void GameOverScene::menuCloseCallback2(Ref* pSender)
{
	auto nextScene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MenuScreen::createScene()));
}