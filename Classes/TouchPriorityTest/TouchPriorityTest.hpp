//
//  TouchPriorityTest.hpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#ifndef TouchPriorityTest_hpp
#define TouchPriorityTest_hpp

#include <stdio.h>
#include "cocos2d.h"

class TouchPriorityTest : public cocos2d::Layer {
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(TouchPriorityTest);

};

#endif /* TouchPriorityTest_hpp */
