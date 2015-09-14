#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Vila : public LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a event callback    
	void onTouchesBegan(const std::vector<Touch *> &touches, Event *event);
	void onTouchesMoved(const std::vector<Touch *> &touches, Event *event);
	void onTouchesEnded(const std::vector<Touch *> &touches, Event *event);

	void menuCloseCallback(cocos2d::Ref* pSender);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	void update(float) override;

	// implement the "static create()" method manually
	CREATE_FUNC(Vila);

private:
	const static int MAX_TOUCHES = 5;
	void CreateNewScene(int id);

protected:
	Label* labelTouchLocations[MAX_TOUCHES];

	Sprite *player;
	Sprite *bgInGame;

	Vector<Sprite*> shadows;

	int pontoAtual = 0;
};

