//
//  util.cpp
//
//  Created by beckheng on 14-6-24.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#include "util.h"

#include <string.h>
#include <stdio.h>
#include <sstream>

USING_NS_CC;

MoveTo* getAvgMoveToAction(Point orig, Point moveto, float time)
{
	return getAvgMoveToAction(orig.x, orig.y, moveto.x, moveto.y, time);
}

MoveTo* getAvgMoveToAction(float origx, float origy, float movetoX, float movetoY, float time)
{
	float offRealX = abs(movetoX - origx);
	float offRealY = abs(movetoY - origy);
	float distance = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
	
	// 移动到新位置
	MoveTo* action = MoveTo::create(distance/time, Point(movetoX, movetoY));
	
	return action;
}

void addAnimationFrame(Vector<SpriteFrame*> &vectorFrames, Texture2D * texture2d, int frames)
{
	float width = texture2d->getContentSize().width/frames;
	
	for (int i = 0; i < frames; i++) {
		SpriteFrame *frame = SpriteFrame::createWithTexture(texture2d, Rect(i * width, 0, width, texture2d->getContentSize().height));
		vectorFrames.pushBack(frame);
	}
}

Animate* getFrameAnimation(Vector<SpriteFrame*> &vectorFrames, float delayPerUnit)
{
	Animation* animation = Animation::createWithSpriteFrames(vectorFrames);
	animation->setDelayPerUnit(delayPerUnit);
	Animate* animate = Animate::create(animation);
	
	return animate;
}

SpriteFrame* getSpriteFrame(std::string file)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
	Rect bounds = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
	
	return SpriteFrame::createWithTexture(texture, bounds);
}

Vector<SpriteFrame*> getSpriteFrames(std::string file, int width, int height)
{
	Vector<SpriteFrame*> ret;

	Texture2D *texture2d = Director::getInstance()->getTextureCache()->addImage(file);
	
	int startWidth = 0, startHeight = 0;
	for (; startHeight < texture2d->getContentSize().height; startHeight += height) {
		for (startWidth = 0; startWidth < texture2d->getContentSize().width; startWidth += width) {
			SpriteFrame *frame = SpriteFrame::createWithTexture(texture2d, Rect(startWidth, startHeight, width, height));
			ret.pushBack(frame);
		}
	}
	
	return ret;
}

void resetPhysicsBody(Sprite *sprite, PhysicsShape *shape)
{
	PhysicsBody *body = sprite->getPhysicsBody();
	if (body != NULL)
	{
		body->removeAllShapes();
	}
	else
	{
		body = PhysicsBody::create();
		sprite->setPhysicsBody(body);
	}
		
	body->addShape(shape);
}

void repeatBackground(Node *bgNode, std::string file)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	float startHeight, startWidth, spriteHeight;
	
	startHeight = 0;
	startWidth = 0;
	
	while (startHeight < visibleSize.height) {
		while (startWidth < visibleSize.width) {
			Sprite *bgSprite = Sprite::create(file);
			bgSprite->setAnchorPoint(Point::ZERO);
			bgSprite->setPosition(startWidth, startHeight);
			bgNode->addChild(bgSprite);
			
			startWidth += bgSprite->getContentSize().width;
			
			spriteHeight = bgSprite->getContentSize().height;
		}
		
		startWidth = 0;
		startHeight += spriteHeight;
	}
}
