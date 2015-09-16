#include "Vila.h"
#include "Batalha.h"
#include "HelloWorldScene.h"

#define JOGANDO 0
#define LOJA 1
#define PAUSADO 2
#define MENU 3

USING_NS_CC;

Scene* Vila::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Vila::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Vila::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(100, 100, 100, 255)))
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
		CC_CALLBACK_1(Vila::menuCloseCallback, this));

	auto listener = EventListenerTouchAllAtOnce::create();
	auto keyboardListener = EventListenerKeyboard::create();

	listener->onTouchesBegan = CC_CALLBACK_2(Vila::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Vila::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Vila::onTouchesEnded, this);

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Vila::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Vila::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	/////////////////////////////
	// 3. add your codes below...

	bgInGame = Sprite::create("bg_inGame.jpg");

	bgInGame->setAnchorPoint(Vec2(.5, .5));
	bgInGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	// add "HelloWorld" splash screen"
	player = Sprite::create("shaman_dude.png");

	// position the sprite on the center of the screen
	player->setPosition(Vec2(visibleSize.width / 2.5 + origin.x, visibleSize.height / 2 + origin.y));

	player->setScale(visibleSize.width*.001, visibleSize.height*.0013);

	// add the sprite as a child to this layer

	this->addChild(bgInGame, 0);
	this->addChild(player, 1);
	this->addChild(closeItem, 3);

	this->scheduleUpdate();

	return true;
}

#pragma mark -
#pragma mark - Update
void Vila::update(float delta){
	if (JOGANDO){
		int count = 0;
	}
}

#pragma mark -
#pragma mark - Events Key/Touch

void Vila::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{

}

void Vila::onTouchesMoved(const std::vector<Touch *> &touches, Event *unused_event)
{
	
}

void Vila::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
	auto touch = touches[0];
	auto start = touch->getLocation();
	auto end = touch->getPreviousLocation();
}

void Vila::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
		break;
	}
}

void Vila::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	/*switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

	player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
	shadow->setPosition(Vec2(shadow->getPositionX() - 2, shadow->getPositionY()));

	break;

	default:
	break;
	}*/
}

#pragma mark -
#pragma mark FINISHING DE APLICATION

void Vila::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}