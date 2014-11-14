//
//  MainScene.cpp
//  ShaderTools
//
//  Created by Tyrion on 14/11/6.
//
//

#include "MainScene.h"
#include "MainLayer.h"
#include "ActiveGrassLayer.h"
CCScene* MainScene::scene()
{
    CCScene* scene = CCScene::create();
    
    
    ActiveGrassLayer *layer = ActiveGrassLayer::create();
    scene->addChild(layer);
    return scene;
}
