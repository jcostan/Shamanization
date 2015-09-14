#include "HelloWorldScene.h"
#include "Vila.h"
#include "Batalha.h"

#define JOGANDO 0
#define LOJA 1
#define PAUSADO 2
#define MENU 3

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(100,100,100,255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    auto listener = EventListenerTouchAllAtOnce::create();
    auto keyboardListener = EventListenerKeyboard::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    
    keyboardListener->onKeyPressed  = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Shamanizer: O ataque das sombras", "fonts/arial.ttf", 18);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    label->setColor(Color3B(255,255,255));
    
    // add the label as a child to this layer
//    this->addChild(label, 1);
    
    bgInGame = Sprite::create("bg_inGame.jpg");
    
    bgInGame->setAnchorPoint(Vec2(.5, .5));
    bgInGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    // add the sprite as a child to this layer
    
    this->addChild(bgInGame, 0);
	this->addChild(closeItem, 3);
    
    this->scheduleUpdate();

    return true;
}

void HelloWorld::ChangeScene(int id){
	if (id == 0)
		VilaScene = Vila::createScene();
	else if (id == 1)
		BatalhaScene = Batalha::createScene();
	Director::getInstance()->replaceScene(id == 0? BatalhaScene : VilaScene);
}

#pragma mark -
#pragma mark - Update
void HelloWorld::update(float delta){
    
    if (JOGANDO)
    {
    }
}

#pragma mark -
#pragma mark - Events Key/Touch

void HelloWorld::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{

}

void HelloWorld::onTouchesMoved(const std::vector<Touch *> &touches, Event *unused_event)
{
    auto touch = touches[0];
    auto start = touch->getLocation();
    auto end = touch->getPreviousLocation();
}

void HelloWorld::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    auto touch = touches[0];
    auto start = touch->getLocation();
    auto end = touch->getPreviousLocation();
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		ChangeScene(0);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		ChangeScene(1);
		break;
    }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{

}

#pragma mark -
#pragma mark FINISHING DE APLICATION

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	auto scene = Vila::createScene();

	// run
	Director::getInstance()->replaceScene(scene);
    //Director::getInstance()->end();
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}