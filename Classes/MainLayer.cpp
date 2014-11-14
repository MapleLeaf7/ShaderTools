//
//  MainLayer.cpp
//  ShaderTools
//
//  Created by Tyrion on 14/11/6.
//
//

#include "MainLayer.h"
#include "BlurTextureFilter.h"
enum{
    tag_mapTest,
};

MainLayer::MainLayer(){
    
}

MainLayer::~MainLayer(){
    
}

bool MainLayer::init(){
    if (CCLayerColor::initWithColor(ccc4(40, 40, 40, 255))) {

//        blurFullLayer();
        blurPartialLayer();
        
//        CCSprite* mapTest = CCSprite::create("HelloWorld.png");
//        mapTest->setAnchorPoint(ccp(0.5,0.5));
//        mapTest->setPosition(ccp(winSize.width/2, winSize.height/2));
//        this->addChild(mapTest, 0, tag_mapTest);
        
        return true;
    }
    return false;
}

void MainLayer::blurFullLayer(){
    // 必须使用RGBA8888格式的图片
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
    
    // 创建 Mutable 纹理
    CCTexture2DMutable* pMutableTex = new CCTexture2DMutable();
    CCImage* pImage = new CCImage();

    if(pImage && pImage->initWithImageFile("HelloWorld.png"))
    {
        pImage->autorelease();
    }
    if( pMutableTex && pMutableTex->initWithData(pImage->getData(),
                                                 kCCTexture2DPixelFormat_RGBA8888,
                                                 pImage->getWidth(),
                                                 pImage->getHeight(),
                                                 CCSizeMake(pImage->getWidth(), pImage->getHeight())))
    {
        pMutableTex->autorelease();
    }
    else
    {
        return;
    }
    
    // 创建 NoMutable 纹理
    CCTexture2D* pNoMutableTex = pMutableTex->copyMutable(false);
    pNoMutableTex->autorelease();
    
    // 给 Mutable 纹理混合模糊
    BlurTextureFilter Filter;
    Filter.blur(pMutableTex, 55);
    
    // 显示 Mutable 纹理
    
    CCSprite* pNoBlurSprite = CCSprite::createWithTexture( pNoMutableTex );
    pNoBlurSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    CCSprite* pBlurSprite = CCSprite::createWithTexture( pMutableTex );
    pBlurSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    pBlurSprite->setScaleX(1.04);
    pBlurSprite->setScaleY(1.15);
    pBlurSprite->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5), NULL)));
    this->addChild(pBlurSprite);
    this->addChild(pNoBlurSprite);
}

void MainLayer::blurPartialLayer(){
    // 必须使用RGBA8888格式的图片
    CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA8888 );
    
    // 创建 Mutable 纹理
    CCTexture2DMutable* pMutableTex = new CCTexture2DMutable();
    CCImage* pImage = new CCImage();
    if( pImage && pImage->initWithImageFile("HelloWorld.png"))
    {
        pImage->autorelease();
    }
    if( pMutableTex && pMutableTex->initWithData( pImage->getData(),
                                                 kCCTexture2DPixelFormat_RGBA8888, pImage->getWidth(), pImage->getHeight(),
                                                 CCSizeMake(pImage->getWidth(), pImage->getHeight() ) ) )
    {
        pMutableTex->autorelease();
    }
    else
    {
        return;
    }

    // 创建 NoMutable 纹理
    CCTexture2D* pNoMutableTex = pMutableTex->copyMutable(false);
    pNoMutableTex->autorelease();
    
    CCSprite* pSprite = CCSprite::createWithTexture(pNoMutableTex);
    
    // 开始部分模糊
    BlurTextureFilter Filter;
    Filter.blur(pMutableTex, 50, CCRectMake(0, 0, pSprite->getContentSize().width/2, pSprite->getContentSize().height));
    
    // 显示 Mutable 纹理
    CCSprite* pBlurSprite = CCSprite::createWithTexture(pMutableTex);
    pBlurSprite->setPosition(winCenter);
    this->addChild( pBlurSprite );
}

CCSprite* MainLayer::blurSprite(CCSprite* originalSprite){

    CCSprite* tempSprite = CCSprite::createWithTexture(originalSprite->getTexture());
    tempSprite->setPosition(CCPointZero);
    tempSprite->setAnchorPoint(ccp(0,0));
    
    CCSize __size = tempSprite->getContentSize();
    
    CCRenderTexture* __canva = CCRenderTexture::create(__size.width, __size.height);
    __canva->begin();
    tempSprite->visit();
    __canva->end();
    
    CCTexture2D* __tex2 = new CCTexture2D();
    __tex2->initWithImage(__canva->newCCImage(true));
    __tex2->autorelease();
    
    
    
    
    // 必须使用RGBA8888格式的图片
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
    
    // 创建 Mutable 纹理
    CCTexture2DMutable* pMutableTex = new CCTexture2DMutable();
    CCImage* pImage = __canva->newCCImage(true);
    
    if( pMutableTex && pMutableTex->initWithData(pImage->getData(),
                                                 kCCTexture2DPixelFormat_RGBA8888,
                                                 pImage->getWidth(),
                                                 pImage->getHeight(),
                                                 CCSizeMake(pImage->getWidth(), pImage->getHeight())))
    {
        pMutableTex->autorelease();
    }
    else
    {
        return originalSprite;
    }
    
    // 给 Mutable 纹理混合模糊
    BlurTextureFilter Filter;
    Filter.blur(pMutableTex, 20);
    
    // 显示 Mutable 纹理
    
    CCSprite* pBlurSprite = CCSprite::createWithTexture( pMutableTex );
    
    //显示最终效果
    return pBlurSprite;
}

void MainLayer::onEnter()
{
//    CCLOG("%s","MainLayer:onEnter");
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void MainLayer::onExit()
{
//    CCLOG("%s","MainLayer:onExit");
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
    
}

bool MainLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("MainLayer::ccTouchBegan");
    CCSprite* mapTest = (CCSprite*)this->getChildByTag(tag_mapTest);
//    mapTest->setPosition(pTouch->getLocation());
    CCSprite* mBlurSprite = blurSprite(mapTest);
    mBlurSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    mBlurSprite->setOpacity(0);
    addChild(mBlurSprite);
    mBlurSprite->runAction(CCFadeIn::create(1));
    return true;
}

void MainLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("MainLayer::ccTouchMoved");
}

void MainLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("MainLayer::ccTouchEnded");
}