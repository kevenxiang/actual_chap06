//
//  TouchOneByOneTest.cpp
//  actual_chap06
//
//  Created by xiang on 2017/6/27.
//
//

#include "TouchOneByOneTest.hpp"
USING_NS_CC;

Scene *TouchOneByOneTest::createScene() {
    auto scene = Scene::create();
    auto layer = TouchOneByOneTest::create();
    scene->addChild(layer);
    return scene;
}

bool TouchOneByOneTest::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //关闭菜单
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(TouchOneByOneTest::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
    
    // 删除触摸监听器
    auto removeAllTouchItem = MenuItemFont::create("删除所有的触摸监听器", [this](Ref *sender){
        auto senderItem = static_cast<MenuItemFont *>(sender);
        senderItem->setString("触摸监听器删除成功");
        
        _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
    });
    removeAllTouchItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.2));
    // 创建菜单
    auto menu = Menu::create(removeAllTouchItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    // 标题标签
    auto title = Label::createWithSystemFont("单点触摸（场景优先）测试", "", 15);
    title->setPosition(visibleSize.width/2, visibleSize.height * 0.9);
    this->addChild(title);
    
    // 提示标签
    auto subtitle = Label::createWithSystemFont("请单击或拖动滑块", "", 15);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height * 0.8);
    this->addChild(subtitle);
    
    // 创建三个精灵对象
    auto sprite1 = Sprite::create("CyanSquare.png");
    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 80));
    addChild(sprite1, 10);
    
    auto sprite2 = Sprite::create("MagentaSquare.png");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = Sprite::create("YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, 1);
    
    // ①创建一个单点触摸事件监听器，处理触摸事件逻辑
    auto listener1 = EventListenerTouchOneByOne::create();
    // 设置是否向下传递触摸
    listener1->setSwallowTouches(true);
    // 通过 lambda 表达式 直接实现触摸事件的响应函数
    listener1->onTouchBegan = [](Touch *touch, Event *event){
        // 获得当前事件触摸的目标对象
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        // 获得当前的触摸点
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        // 获得触摸对象的ContentSize
        Size s = target->getContentSize();
        // 获得位置矩形
        Rect rect = Rect(0, 0, s.width, s.height);
        // 如果位置矩形包含触摸点
        if (rect.containsPoint(locationInNode)) {
            log("onTouchBegan... x = %f, y = %f", locationInNode.x, locationInNode.y);
            //设置透明度
            target->setOpacity(180);
            // 表明用户触摸事件已经被处理，后续的onTouchMoved、onTouchEnded和onTouchCancelled会接着响应，其他事件监听器则不会再去进行监听本次触摸事件。
            return true;
        }
        
        return false;
    };
    
    
    listener1->onTouchMoved = [](Touch *touch, Event *event){
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        // 移动触摸的精灵
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener1->onTouchEnded = [=](Touch *touch, Event *event){
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        // 设置透明度
        target->setOpacity(255);
        std::string name;
        if (target == sprite2) {
            name = "MagentaSquare.png";
            sprite1->setZOrder(100);
            subtitle->setString("响应事件的是酒红色滑块，青色滑块的ZOrder值修改为100");
        } else if (target == sprite1) {
            name = "CyanSquare.png";
            sprite1->setZOrder(0);
            subtitle->setString("响应事件的是青色滑块，青色滑块的ZOrder值修改为0");
        } else {
            name = "YellowSquare.png";
        }
        
        log("onTouchEnded.. 您触摸的是%s",name.c_str());
    };
    
    // 添加场景优先事件监听器。
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    // ④注意：在使用addEventListenerWithSceneGraphPriority或者addEventListenerWithFixedPriority函数时，	会对当前使用的事件监听器添加一个已注册的标记，这使得它不能够被添加多次。所以当我们再次使用listener1的时候，需要使用clone()函数创建一个新的克隆。
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    
    return true;
}

void TouchOneByOneTest::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





























