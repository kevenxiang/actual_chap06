//
//  CustomTest.hpp
//  actual_chap06
//
//  Created by xiang on 2017/6/29.
//
//

#ifndef CustomTest_hpp
#define CustomTest_hpp

#include <stdio.h>
#include "cocos2d.h"

class CustomTest : public cocos2d::Layer {
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    // 选择器回调函数
    void menuCloseCallback(cocos2d::Ref *pSender);
    
    CREATE_FUNC(CustomTest);
};


#endif /* CustomTest_hpp */
