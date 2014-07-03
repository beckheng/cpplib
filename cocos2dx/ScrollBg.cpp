//
//  ScrollBg.cpp
//
//  Created by beckheng on 14-7-3.
//
//

#include "ScrollBg.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ScrollBg::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();

	this->offsetX = 0;
	this->offsetY = 0;
		
    return true;
}

void ScrollBg::addBg(Vector<Sprite*> &bgs, BG_DIRECTION direction)
{
	bgSprites = bgs;
	
	float tmpOffset = 0, bg = 0;
	for (int i = 0; i < bgSprites.size(); i++) {
		Point p = (direction == BG_VERTICAL) ? Point(0, tmpOffset) : Point(tmpOffset, 0);
		Sprite *it = bgSprites.at(i);
		this->addBgChild(it, p);
		
		tmpOffset += ((direction == BG_VERTICAL) ? it->getContentSize().height : it->getContentSize().width);
		
		bg = tmpOffset;
	}
	
	int origSpriteCount = bgSprites.size();
	float maxSize = ((direction == BG_VERTICAL) ? visibleSize.height : visibleSize.width) * 3;
	while (bg < maxSize)
	{
		for (int i = 0; i < origSpriteCount; i++) {
			Point p = (direction == BG_VERTICAL) ? Point(0, tmpOffset) : Point(tmpOffset, 0);
			Sprite *it = Sprite::createWithSpriteFrame(bgSprites.at(i)->getSpriteFrame());
			this->addBgChild(it, p);
			bgSprites.pushBack(it);
			
			tmpOffset += ((direction == BG_VERTICAL) ? it->getContentSize().height : it->getContentSize().width);
			
			bg = tmpOffset;
		}
	}
}

void ScrollBg::addBgChild(Sprite* it, Point pos)
{
	it->removeFromParentAndCleanup(true); // 为避免出现重复添加的异常，这里先移除一次
	
	it->setAnchorPoint(Point::ZERO);
	it->setPosition(pos);
	this->addChild(it);
}

void ScrollBg::scroll(float _offsetX, float _offsetY)
{
	this->offsetX = _offsetX;
	this->offsetY = _offsetY;
	
	if ((offsetX != 0) || (offsetY != 0))
	{
		schedule(schedule_selector(ScrollBg::updateBg));
	}
}

void ScrollBg::scroll(float _offsetX, float _offsetY, float dt)
{
	this->offsetX = _offsetX;
	this->offsetY = _offsetY;
	
	isSwapingSprite = false;
	
	if ((offsetX != 0) || (offsetY != 0))
	{
		schedule(schedule_selector(ScrollBg::updateBg), dt);
	}
}


void ScrollBg::updateBg(float dt)
{
	if (isSwapingSprite)
	{
		return;
	}
	
	int size = bgSprites.size();
	for (int i = 0; i < size; i++) {
		Sprite* it = bgSprites.at(i);
		Point n = it->getPosition();
		n.x += offsetX;
		n.y += offsetY;
		
		it->setPosition(n);
	}
	
	if (offsetX != 0)
	{
		if (bgSprites.at(0)->getPositionX() + bgSprites.at(0)->getContentSize().width <= 0)
		{
			isSwapingSprite = true;
			bgSprites.at(0)->setPositionX(bgSprites.at(size-1)->getPositionX() + bgSprites.at(size-1)->getContentSize().width);
			bgSprites.pushBack(bgSprites.at(0));
			bgSprites.erase(bgSprites.begin());
			isSwapingSprite = false;
		}
	}
	else if (offsetY != 0)
	{
		if (bgSprites.at(0)->getPositionY() + bgSprites.at(0)->getContentSize().height <= 0)
		{
			isSwapingSprite = true;
			bgSprites.at(0)->setPositionY(bgSprites.at(size-1)->getPositionY() + bgSprites.at(size-1)->getContentSize().height);
			bgSprites.pushBack(bgSprites.at(0));
			bgSprites.erase(bgSprites.begin());
			isSwapingSprite = false;
		}
	}
}
