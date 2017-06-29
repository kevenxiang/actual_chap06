//
//  TouchOneByOneTest.hpp
//  actual_chap06
//
//  Created by xiang on 2017/6/27.
//
//

#ifndef TouchOneByOneTest_hpp
#define TouchOneByOneTest_hpp

#include <stdio.h>
#include "cocos2d.h"

class TouchOneByOneTest : public cocos2d::Layer {
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    // 选择器回调函数
    void menuCloseCallback(cocos2d::Ref *pSender);
    
    CREATE_FUNC(TouchOneByOneTest);
};

#endif /* TouchOneByOneTest_hpp */
