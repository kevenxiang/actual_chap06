//
//  TouchPriorityTest.cpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#include "TouchPriorityTest.hpp"
#include "TouchableSpriteWithFixedPriority.hpp"

USING_NS_CC;

Scene *TouchPriorityTest::createScene() {
    auto scene = Scene::create();
    auto layer = TouchPriorityTest::create();
    scene->addChild(layer);
    return scene;
}

bool TouchPriorityTest::init() {
    if (!Layer::init()) {
        return false;
    }
    
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 标题标签
    auto title = Label::createWithSystemFont("单点触摸（固定值优先）测试", "", 20);
    this->setPosition(visibleSize.width/2, visibleSize.height * 0.9);
    this->addChild(title);
    
    // 提示标签
    auto subtitle = Label::createWithSystemFont("请单击滑块", "", 20);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height * 0.75);
    this->addChild(subtitle);
    
    // 使用之前设计的TouchableSpriteWithFixedPriority类创建精灵对象
    auto sprite1 = TouchableSpriteWithFixedPriority::create();
    //设置纹理图片
    sprite1->setTexture("CyanSquare.png");
    //设置优先级别和名称
    sprite1->setPriority(10, "青色滑块");
    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 40));
    this->addChild(sprite1, 10);
    
    // 使用之前设计的TouchableSpriteWithFixedPriority类创建精灵对象
    auto sprite2 = TouchableSpriteWithFixedPriority::create();
    sprite2->setTexture("MagentaSquare.png");
    sprite2->setPriority(20, "酒红色滑块");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite2, 20);
    
    // 使用之前设计的TouchableSpriteWithFixedPriority类创建精灵对象
    auto sprite3 = TouchableSpriteWithFixedPriority::create();
    sprite3->setTexture("YellowSquare.png");
    sprite3->setPriority(30, "黄色滑块");
    sprite3->setPosition(Vec2::ZERO);
    sprite2->addChild(sprite3, 1);
    
    return true;
}



























