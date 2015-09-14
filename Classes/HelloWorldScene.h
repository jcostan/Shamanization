#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public LayerColor
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
	void ChangeScene(int id);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    const static int MAX_TOUCHES = 5;

	Scene *VilaScene;
	Scene *BatalhaScene;
protected:
    Label* labelTouchLocations[MAX_TOUCHES];

    Sprite *bgInGame;
    
    int pontoAtual = 0;
};

#endif // __HELLOWORLD_SCENE_H__
