//
//  ActiveGrassLayer.cpp
//  ShaderTools
//
//  Created by Tyrion on 14/11/14.
//
//

#include "ActiveGrassLayer.h"
//--------------------------------------------------------
static const GLchar* szGrassShader =
"																									\n\
#ifdef GL_ES																						\n\
precision mediump float;																		\n\
#endif																								\n\
\n\
varying vec2 v_texCoord;																			\n\
uniform sampler2D u_texture;																		\n\
uniform float u_time;																				\n\
\n\
// 1																								\n\
const float speed = 2.0;																			\n\
const float bendFactor = 0.2;																		\n\
void main()																							\n\
{																									\n\
    // 获得高度，texCoord从下到上为0到1																	\n\
    float height = 1.0 - v_texCoord.y;																	\n\
    // 获得偏移量，一个幂函数，值愈大，导数越大，偏移量愈大													\n\
    float offset = pow(height, 2.5);																	\n\
    // 偏移量随时间变化，并乘以幅度，设置频率																\n\
    offset *= (sin(u_time * speed) * bendFactor);														\n\
    // 使x坐标偏移，fract取区间值（0，1）																	\n\
    vec3 normalColor = texture2D(u_texture, fract(vec2(v_texCoord.x + offset, v_texCoord.y))).rgb;		\n\
    gl_FragColor = vec4(normalColor, 1);																\n\
}";
//--------------------------------------------------------
bool ActiveGrassLayer::init()
{
    do{
        CC_BREAK_IF(!CCLayer::init());
        
        m_fTime = 0.0f;
        
        CCSprite* pSprite = CCSprite::create("Grass.png");
        if( pSprite == NULL )
        {
            break;
        }
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        pSprite->setPosition( ccp(winSize.width / 2, winSize.height / 2) );
        pSprite->setTag( 10001 );
        this->addChild( pSprite );
        
        // 加载顶点着色器和片元着色器
        CCGLProgram* pShader = new  CCGLProgram();
        pShader->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, szGrassShader );
        pSprite->setShaderProgram( pShader );
        pShader->release();
        CHECK_GL_ERROR_DEBUG();
        
        // 启用顶点着色器的attribute变量，坐标、纹理坐标、颜色
        pSprite->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        pSprite->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        // 自定义着色器链接
        pSprite->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        // 设置移动、缩放、旋转矩阵
        pSprite->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
        
        m_nTimeUniformLocation = glGetUniformLocation( pSprite->getShaderProgram()->getProgram(), "u_time" );
        
        pSprite->getShaderProgram()->use();
        
        // 开启帧更新
        this->scheduleUpdate();
        return true;
    }while(0);
    return false;
}
//--------------------------------------------------------
void ActiveGrassLayer::update(float delta)
{
    m_fTime += delta;
    CCSprite* p = (CCSprite*)getChildByTag( 10001 );
    if( p )
    {
        p->getShaderProgram()->use();
    }
    glUniform1f( m_nTimeUniformLocation, m_fTime);
}