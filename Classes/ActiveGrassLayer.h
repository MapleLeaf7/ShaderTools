//
//  ActiveGrassLayer.h
//  ShaderTools
//
//  Created by Tyrion on 14/11/14.
//
//

#ifndef __ShaderTools__ActiveGrassLayer__
#define __ShaderTools__ActiveGrassLayer__

//--------------------------------------------------------
#pragma once
//--------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//--------------------------------------------------------
class ActiveGrassLayer : public CCLayer
{
public:
    virtual bool init();
    virtual void update(float delta);
private:
    int		m_nTimeUniformLocation;
    float	m_fTime;
public:
    CREATE_FUNC( ActiveGrassLayer );
};

#endif /* defined(__ShaderTools__ActiveGrassLayer__) */
