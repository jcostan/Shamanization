#include "HelloWorldScene.h"

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
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    player = Sprite::create("shaman_dude.png");
    shadow = Sprite::create("shadow.png");

    // position the sprite on the center of the screen
    player->setPosition(Vec2(visibleSize.width/2.5 + origin.x, visibleSize.height/2 + origin.y));
    shadow->setPosition(Vec2(visibleSize.width/1.5 + origin.x, visibleSize.height/2 + origin.y));
    
    player->setScale(.5);
    shadow->setScale(.3);

    // add the sprite as a child to this layer
    this->addChild(player, 0);
    this->addChild(shadow, 1);

    return true;
}

#pragma mark -
#pragma mark - Events Key/Touch

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
    shadow->setPosition(Vec2(shadow->getPositionX() + 2, shadow->getPositionY()));
}

void HelloWorld::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
    shadow->setPosition(Vec2(shadow->getPositionX() - 2, shadow->getPositionY()));
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            
            player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
            shadow->setPosition(Vec2(shadow->getPositionX() + 2, shadow->getPositionY()));
            
            break;
            
        default:
            break;
    }
    
    player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
    shadow->setPosition(Vec2(shadow->getPositionX() + 2, shadow->getPositionY()));
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
    shadow->setPosition(Vec2(shadow->getPositionX() - 2, shadow->getPositionY()));
}
