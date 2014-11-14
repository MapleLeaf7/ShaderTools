//
//  BlurTools.h
//  ShaderTools
//
//  Created by Tyrion on 14/11/8.
//
//

#ifndef __ShaderTools__BlurTools__
#define __ShaderTools__BlurTools__

#include "cocos2d.h"
USING_NS_CC;
#include "BlurTextureFilter.h"

class BlurTools
{
public:
    BlurTools(){};
    ~BlurTools(){};
public:
    CCTexture2D* blurWithTexture(CCTexture2D* originalTexture, int radius, CCRect rect);
    CCTexture2D* blurWithFile(const char* fileName, int radius, CCRect rect);
    CCSprite* blurWithSprite(CCSprite* originalSprite, int radius, CCRect rect);
};

#endif /* defined(__ShaderTools__BlurTools__) */
