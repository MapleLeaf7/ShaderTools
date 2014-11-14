//
//  BlurTextureFilter.h
//  ShaderTools
//
//  Created by Tyrion on 14/11/6.
//
//

#ifndef __ShaderTools__BlurTextureFilter__
#define __ShaderTools__BlurTextureFilter__

#include "GameHeader.h"
#include "cocos2d.h"
USING_NS_CC;
#include "Texture2DMutable.h"

class BlurTextureFilter
{
    /**
     @param input: Original texture data
     @param output: Empty (or not) buffer
     @param format: Pixel format of the data
     @param width: Real width (is a power of two)
     @param height: Real height (is a power of two)
     @param position: Top left vertex of the blur effect
     @param size: The size of the blur effect
     @param contentSize:
     @param radios: It's the radius of the blur effect
     */
public:
    BlurTextureFilter() {};
    ~BlurTextureFilter() {};
public:
    void blurInput(void* input, void* output, CCTexture2DPixelFormat format, int width, int height, CCSize contentSize, int radius, CCRect rect);
    CCTexture2DMutable* blur(CCTexture2DMutable* texture, int radius);
    CCTexture2DMutable* blur(CCTexture2DMutable* texture, int radius, CCRect rect);
};

#endif /* defined(__ShaderTools__BlurTextureFilter__) */
