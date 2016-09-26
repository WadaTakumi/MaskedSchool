#ifndef __MENUSCREEN_SCENE_H__
#define __MENUSCREEN_SCENE_H__

#include "cocos2d.h"
#include "cocos2d/cocos/ui/UIButton.h"

class MenuScreen : public cocos2d::Layer
{
public:
    MenuScreen();

    static cocos2d::Scene* createScene();

	virtual bool init();
	void startGame(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);
	void showOptions(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);
	void quitGame(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);

    void createMenuButtons();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(MenuScreen);

private:
    cocos2d::Label* m_menuLabel;

    cocos2d::ui::Button* m_startButton;
    cocos2d::ui::Button* m_optionsButton;
    cocos2d::ui::Button* m_quitButton;

	cocos2d::Point m_touchPosition;

	bool m_isTouching;
};

#endif // __MENUSCREEN_SCENE_H__