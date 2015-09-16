#include "Batalha.h"
#include "HelloWorldScene.h"
#include "Vila.h"

#define JOGANDO 0
#define LOJA 1
#define PAUSADO 2
#define MENU 3

USING_NS_CC;

Scene* Batalha::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Batalha::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Batalha::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
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
		CC_CALLBACK_1(Batalha::menuCloseCallback, this));

	auto listener = EventListenerTouchAllAtOnce::create();
	auto keyboardListener = EventListenerKeyboard::create();

	listener->onTouchesBegan = CC_CALLBACK_2(Batalha::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Batalha::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Batalha::onTouchesEnded, this);

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Batalha::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Batalha::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	configBrush();
    
	auto label = Label::createWithTTF("Shamanizer: O ataque das sombras", "fonts/arial.ttf", 18);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(Color3B(255, 255, 255));

	// add the label as a child to this layer
	//    this->addChild(label, 1);

	bgInGame = Sprite::create("bgToVila.png");

	bgInGame->setAnchorPoint(Vec2(.5, .5));
	bgInGame->setPosition(Vec2(visibleSize.width / visibleSize.width/2, visibleSize.height / 2));

	// add "HelloWorld" splash screen"
	player = Sprite::create("shaman_dude.png");
	shadow = Sprite::create("shadow.png");

	// position the sprite on the center of the screen
	player->setPosition(Vec2(visibleSize.width / 2.5 + origin.x, visibleSize.height / 2 + origin.y));
	shadow->setPosition(Vec2(visibleSize.width / 1.5 + origin.x, visibleSize.height / 2 + origin.y));

	player->setScale(visibleSize.width*.001, visibleSize.height*.0013);
	shadow->setScale(visibleSize.width*.0008, visibleSize.height*.001);

	nodeMagic = DrawNode::create();
	nodeMagic->setName("andrei");

	// add the sprite as a child to this layer

	   this->addChild(bgInGame, 0);
	   this->addChild(player, 1);
	   this->addChild(shadow, 2);
	//   this->addChild(closeItem, 3);
	//this->addChild(nodeMagic, 0);

	this->scheduleUpdate();
    


	return true;
}

void Batalha::configBrush()
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
void Batalha::update(float delta){

	spawnTimer -= delta;

	if (JOGANDO)
	{
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
}

void Batalha::SpawnEnemies(){
	if (spawnTimer <= 0){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		float randY = rand() % 100 + (-100);
		shadows.pushBack(Sprite::create("shadow.png"));

		shadows.at(shadows.size() - 1)->setPosition(Vec2(visibleSize.width / 1.5 + origin.x, visibleSize.height / 2 + randY));
		shadows.at(shadows.size() - 1)->setScale(visibleSize.width*.0008, visibleSize.height*.001);
		this->addChild(shadows.at(shadows.size() - 1), shadows.size() + 3);
		spawnTimer = .1;
	}
}

void Batalha::ChangeScene(int id) {

    if (id == 0) {
        	this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height / 6));
    }
    
    else {
        this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height / 6));
    }
    
}

#pragma mark -
#pragma mark - Events Key/Touch

void Batalha::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{

    if (touches[0]->getLocationInView().x > Director::getInstance()->getVisibleSize().width/2)
        ChangeScene(0);
    
    else
        ChangeScene(1);
}

void Batalha::onTouchesMoved(const std::vector<Touch *> &touches, Event *unused_event)
{
	auto touch = touches[0];
	auto start = touch->getLocation();
	auto end = touch->getPreviousLocation();

	// begin drawing to the render texture
	target->begin();

	// for extra points, we'll draw this smoothly from the last position and vary the sprite's
	// scale/rotation/offset
	float distance = start.getDistance(end);
	if (distance > 1)
	{
		int d = (int)distance;
		brushs.clear();
		for (int i = 0; i < d; ++i)
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
			/*_brush->setColor(Color3B(CCRANDOM_0_1() * 127 + 128, 255, 255));*/
			// Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
			brushs.at(i)->setColor(Color3B(rand() % 127 + 128, 255, 255));
			// Call visit to draw the brush, don't call draw..
			brushs.at(i)->visit();
		}
	}

	// finish drawing and return context back to the screen
	target->end();
}

void Batalha::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
	auto touch = touches[0];
	auto start = touch->getLocation();
	auto end = touch->getPreviousLocation();
}

void Batalha::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		//player->setPosition(Vec2(player->getPositionX() + 2, player->getPositionY()));
		Batalha::ChangeScene(0);
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//player->setPosition(Vec2(player->getPositionX() - 2, player->getPositionY()));
		Batalha::ChangeScene(1);
		break;
	}
}

void Batalha::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
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

void Batalha::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}