//
//  MainLayer.h
//  ShaderTools
//
//  Created by Tyrion on 14/11/6.
//
//

#ifndef __ShaderTools__MainLayer__
#define __ShaderTools__MainLayer__

#include "GameHeader.h"
#include "cocos2d.h"
USING_NS_CC;

class MainLayer : public CCLayerColor{

public:
    CREATE_FUNC(MainLayer);
    virtual bool init();
    
    void blurFullLayer();
    void blurPartialLayer();
    CCSprite* blurSprite(CCSprite* originalSprite);
private:
    MainLayer();
    ~MainLayer();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    
};

#endif /* defined(__ShaderTools__MainLayer__) */
