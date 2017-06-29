//
//  CustomTest.cpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#include "CustomTest.hpp"

USING_NS_CC;

Scene *CustomTest::createScene() {
    auto scene = Scene::create();
    auto layer = CustomTest::create();
    scene->addChild(layer);
    return scene;
}

bool CustomTest::init() {
    if (!Layer::init()) {
        return false;
    }
    
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 关闭菜单
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(CustomTest::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
    
    // ①创建一个标签，用来显示用户自定义事件内容
    auto statusLabel = Label::createWithSystemFont("没有收到自定义事件", "", 17);
    statusLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.6));
    this->addChild(statusLabel);
    
    // ②创建一个自定义事件监听器，第一个参数是自定义事件的名称，第二个参数是自定义事件的响应函数
    auto listener = EventListenerCustom::create("game_custom_event", [=](EventCustom *event){
        // 更新显示自定义事件标签内容
        statusLabel->setString(StringUtils::format("收到自定义事件[ %s ]次", event->getUserData()));
    });
    
    // ③添加自定义事件监听器
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    static int count = 0;
    // ④创建发送自定义事件标签
    auto sendItem = MenuItemFont::create("单击发送自定义事件", [=](Ref *sender){
        ++count;
        char *buf = new char[10];
        sprintf(buf, "%d", count);
        // 定义了一个自定义事件
        EventCustom event("game_custom_event");
        // 设置自定义事件的UserData数据
        event.setUserData(buf);
        // 将此事件分发出去，从而触发之前所实现的逻辑
        _eventDispatcher->dispatchEvent(&event);
        // 释放数据占用的内存
        CC_SAFE_DELETE_ARRAY(buf);
    });
    
    sendItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.4));
    
    // 创建菜单并显示
    auto menu = Menu::create(sendItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, -1);
    
    
    return true;
}

void CustomTest::menuCloseCallback(Ref* pSender)
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




















