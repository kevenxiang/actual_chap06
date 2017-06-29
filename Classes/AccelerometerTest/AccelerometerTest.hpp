//
//  AccelerometerTest.hpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#ifndef AccelerometerTest_hpp
#define AccelerometerTest_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class AccelerometerTest : public Layer {
private:
    // 目标精灵（球）
    Sprite *_ball;
public:
    
    static Scene *createScene();
    
    virtual bool init();
    
    // 加速度计响应函数
    void onAcceleration(Acceleration *acc, Event *event);
    
    CREATE_FUNC(AccelerometerTest);
};

#endif /* AccelerometerTest_hpp */
