//
//  TouchableSpriteWithFixedPriority.hpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#ifndef TouchableSpriteWithFixedPriority_hpp
#define TouchableSpriteWithFixedPriority_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class TouchableSpriteWithFixedPriority : public Sprite {
private:
    // 事件监听器
    EventListener *_listener;
    // 优先级
    int _fixedPriority;
    // 用于保存精灵的图片名称，便于观察结果
    const char *_name;
    
public:
    // ①设置优先级和名称的函数
    void setPriority(int fixedPriority, const char *name) {
        _fixedPriority = fixedPriority;
        _name = name;
    };
    
    void onEnter() override {
        Sprite::onEnter();
        // 创建一个单点触摸
        auto listener = EventListenerTouchOneByOne::create();
        // 设置事件是否可以向下传递
        listener->setSwallowTouches(true);
        
        // 通过 lambda 表达式 直接实现触摸事件的回调方法
        listener->onTouchBegan = [=](Touch *touch, Event *event) {
            //获得当前的触摸点
            Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
            //获得触摸对象的ContentSize
            Size s = this->getContentSize();
            //获得位置矩形
            Rect rect = Rect(0, 0, s.width, s.height);
            // 判断位置矩形包含触摸点
            if (rect.containsPoint(locationInNode)) {
                // 输出响应的精灵的图片名称和优先级
                log("onTouchBegan...响应事件的是%s, 优先级=%d, x = %f, y = %f", _name,_fixedPriority,locationInNode.x, locationInNode.y);
                return false;
            }
            
            return false;
        };
        
        listener->onTouchMoved = [=](Touch *touch, Event *event) {
            log("onTouchMoved...");
            //移动精灵
            this->setPosition(this->getPosition() + touch->getDelta());
        };
        
        listener->onTouchEnded = [=](Touch *touch, Event *event) {
            log("onTouchEnded...");
        };
        
        // ②激活touch事件。优先级值小的精灵将优先接受触摸事件
        _eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
        _listener = listener;
    }
    
    void onExit() override {
        log("onExit...");
        // ③删除事件监听器
        _eventDispatcher->removeEventListener(_listener);
        Sprite::onExit();
    }
    
    CREATE_FUNC(TouchableSpriteWithFixedPriority);
};

#endif /* TouchableSpriteWithFixedPriority_hpp */
























