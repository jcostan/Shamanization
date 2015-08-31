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
    this->addChild(label, 1);
    
    bgInGame = Sprite::create("bg_inGame.jpg");
    
    bgInGame->setAnchorPoint(Vec2(.5, .5));
    bgInGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    // add "HelloWorld" splash screen"
    player = Sprite::create("shaman_dude.png");
    shadow = Sprite::create("shadow.png");
    
    // position the sprite on the center of the screen
    player->setPosition(Vec2(visibleSize.width/2.5 + origin.x, visibleSize.height/2 + origin.y));
    shadow->setPosition(Vec2(visibleSize.width/1.5 + origin.x, visibleSize.height/2 + origin.y));
    
    player->setScale(visibleSize.width*.001, visibleSize.height*.0013);
    shadow->setScale(visibleSize.width*.0008, visibleSize.height*.001);
    
    // add the sprite as a child to this layer

    this->addChild(bgInGame, 0);
    this->addChild(player, 1);
    this->addChild(shadow, 2);
    this->addChild(closeItem, 3);

	this->scheduleUpdate();
    return true;
}

void HelloWorld::update(float delta){
	spawnTimer -= delta;
    
	SpawnEnemies();
    
	int count = 0;
    
    for (int i = 0; i < shadows.size(); i++) {
		auto position = shadows.at(i)->getPosition();
        
		if (position.x < 0 - (shadows.at(i)->getBoundingBox().size.width / 2)) {
			//Ele saiu da tela, deve ir pra outra(e dominar uma casinha)
			//A linha abaixo faz ele aparecer na direita da tela
			position.x = this->getBoundingBox().getMaxX() + shadows.at(i)->getBoundingBox().size.width / 2;
		}
//		else {//Ainda esta na tela, ir pra esquerda
//			position.x -= 50 * delta;
//			shadows.at(i)->setPosition(position);
//		}

		count++;
	}
}

void HelloWorld::SpawnEnemies(){
	if (spawnTimer <= 0){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		float randY = rand() % 100 + (-100);
		shadows.pushBack(Sprite::create("shadow.png"));

		shadows.at(shadows.size()-1)->setPosition(Vec2(visibleSize.width / 1.5 + origin.x, visibleSize.height / 2 + randY));
		shadows.at(shadows.size()-1)->setScale(visibleSize.width*.0008, visibleSize.height*.001);
		this->addChild(shadows.at(shadows.size() - 1), shadows.size()+3);
		spawnTimer = .1;
	}
}

#pragma mark -
#pragma mark - Events Key/Touch

void HelloWorld::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{
	if (touches[0]->getLocation().x > Director::getInstance()->getVisibleSize().width / 2)
		player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
	else
		player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));

    /*player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
    shadow->setPosition(Vec2(shadow->getPositionX() + 2, shadow->getPositionY()));*/
}

void HelloWorld::onTouchesMoved(const std::vector<Touch *> &touches, Event *unused_event)
{
    
}

void HelloWorld::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    //player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
    //shadow->setPosition(Vec2(shadow->getPositionX() - 2, shadow->getPositionY()));
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            
            player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
            break;
            
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            
            player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
            break;
            
        default:
            break;
    }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
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

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
