#include "HelloWorldScene.h"
#include "Vila.h"
#include "Batalha.h"

#define JOGANDO 0
#define LOJA 1
#define PAUSADO 2
#define MENU 3

USING_NS_CC;

#pragma mark -
#pragma mark - Create/Init

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
    this->addChild(player, 1);
    this->addChild(shadow, 2);
    this->addChild(closeItem, 3);
    
    this ->addChild(nodeMagic, 4);
    
    this->scheduleUpdate();

    return true;
}

#pragma mark -
#pragma mark - George W. Brush

void HelloWorld::configBrush()
{
    target = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height, Texture2D::PixelFormat::RGBA8888);
    target->retain();
    target->setPosition(Director::getInstance()->getVisibleSize() / 2);
    
    this->addChild(target);
    
    brush = Sprite::create("largeBrush.png");
    brush->setColor(Color3B::BLACK);
    brush->retain();
    
    target->beginWithClear(1, 1, 1, 1);
    target->end();
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
    /*if (timedOut) {
        detector->reset();
        
        if (enableDraw) {
            detector->removeAllPoints();
        }
    }*/
    
    auto touch = touches[0];
    auto point = touch->getLocation();
    //detector->addPoint(point);
    
    //if (!enableDraw) return
    
    //path->moveToPoint(point);
}

void HelloWorld::onTouchesMoved(const std::vector<Touch *> &touches, Event *unused_event)
{
    auto touch = touches[0];
    auto point = touch->getLocation();
    
    //detector->addPoint(point);
    
    //if (!enableDraw) return;
    
    //path->addLineToPoint(point);
    
    
    //auto start = touch->getLocation();
    //auto end = touch->getPreviousLocation();
    
    /*
    // begin drawing to the render texture
    target->begin();
    
    // for extra points, we'll draw this smoothly from the last position and vary the sprite's
    // scale/rotation/offset
    float distance = start.getDistance(end);
    if (distance > 1)
    {
        int d = (int)distance;
        brushs.clear();
        for(int i = 0; i < d; ++i)
        {
            Sprite * sprite = Sprite::create("largeBrush.png");
            sprite->setColor(Color3B::RED);
            sprite->setOpacity(20);
            brushs.pushBack(sprite);
        }
        for (int i = 0; i < d; i++)
        {
            float difx = end.x - start.x;
            float dify = end.y - start.y;
            float delta = (float)i / distance;
            brushs.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
            brushs.at(i)->setRotation(rand() % 360);
            float r = (float)(rand() % 50 / 50.f) + 0.25f;
            brushs.at(i)->setScale(r);
            /*_brush->setColor(Color3B(CCRANDOM_0_1() * 127 + 128, 255, 255));
            // Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
            brushs.at(i)->setColor(Color3B(rand() % 127 + 128, 255, 255));
            // Call visit to draw the brush, don't call draw..
            brushs.at(i)->visit();
        }
    }
    
    // finish drawing and return context back to the screen
    target->end();*/
}

void HelloWorld::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    auto touch = touches[0];
    auto point = touch->getLocation();
    
    //detector->addPoint(point);
    //detector->detect();
    
    //auto start = touch->getLocation();
    //auto end = touch->getPreviousLocation();
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