//
//  util.h
//
//  Created by beckheng on 14-6-24.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#ifndef __yaoheng_cocos2dx__util__
#define __yaoheng_cocos2dx__util__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "cocos2d.h"

USING_NS_CC;

// 平均速度移动action
MoveTo* getAvgMoveToAction(Point orig, Point moveto, float time);
MoveTo* getAvgMoveToAction(float origx, float origy, float movetoX, float movetoY, float time);

// 添加帖动画序列
void addAnimationFrame(Vector<SpriteFrame*> &vectorFrames, Texture2D * texture2d, int frames);
// 帖动画action
Animate* getFrameAnimation(Vector<SpriteFrame*> &vectorFrames, float delayPerUnit);

SpriteFrame* getSpriteFrame(std::string file);

// 读入spritesheet文件，适用于非plist格式的文件
Vector<SpriteFrame*> getSpriteFrames(std::string file, int width, int height);

// 重新设置Sprite的刚体形状，适用于单个形状情形
void resetPhysicsBody(Sprite *sprite, PhysicsShape *shape);

// 以单个图片，重复显示作为整个显示区域背景，从左下往右上方向显示
void repeatBackground(Node *bgNode, std::string file);

#endif
