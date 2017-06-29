//
//  AccelerometerTest.cpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#include "AccelerometerTest.hpp"

//宏定义
#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)  \
_pos = _min;  \
else if (_pos > _max)  \
_pos = _max;   \

Scene *AccelerometerTest::createScene() {
    auto scene = Scene::create();
    auto layer = AccelerometerTest::create();
    scene->addChild(layer);
    return scene;
}

bool AccelerometerTest::init() {
    if (!Layer::init()) {
        return false;
    }
    
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //标题标签
    auto label = Label::createWithSystemFont("加速度计测试", "Arial", 17);
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
    this->addChild(label, 1);
    
    // 创建一个精灵（球）
    _ball = Sprite::create("basketball.png");
    _ball->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(_ball);
    
    // ①启用设备的加速计
    Device::setAccelerometerEnabled(true);
    // ②创建加速度计监听器
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(AccelerometerTest::onAcceleration, this));
    // ③添加加速度计事件监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// 加速度计响应函数实现
void AccelerometerTest::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获得导演对象
    auto pDir = Director::getInstance();
    
    // 如果精灵（球）== NULL则退出
    if (_ball == NULL) {
        return;
    }
    
    // 获得精灵（球）的大小
    auto ballSize = _ball->getContentSize();
    // ④获得精灵（球）的位置
    auto ptNow = _ball->getPosition();
    // ⑤将精灵（球）的位置转换为屏幕坐标系
    auto ptTemp = pDir->convertToUI(ptNow);
    
    // ⑥用x轴和y轴的以重力加速度为单位的加速度值，分别乘以9.81后获得响应的加速度
    ptTemp.x += acc->x * 9.81f;
    ptTemp.y -= acc->y * 9.81f;
    
    // ⑦将屏幕坐标转换为OpenGL坐标
    auto ptNext = pDir->convertToGL(ptTemp);
    
    // ⑧边界检查，防止精灵（球）显示在屏幕之外
    FIX_POS(ptNext.x, ballSize.width/2.0, (visibleSize.width - ballSize.width/2.0));
    FIX_POS(ptNext.y, ballSize.height/2.0, (visibleSize.height - ballSize.height / 2.0));
    
     // ⑨重新设置精灵（球）在屏幕的位置
    _ball->setPosition(ptNext);
    
}


























