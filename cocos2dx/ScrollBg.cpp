//
//  ScrollBg.cpp
//
//  Created by beckheng on 14-7-3.
//
//

#include "ScrollBg.h"

USING_NS_CC;

#define BG_MOVE_LEFT  1
#define BG_MOVE_RIGHT 2
#define BG_MOVE_UP 4
#define BG_MOVE_DOWN 8

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

	initParameter(0, 0);
	
    return true;
}

void ScrollBg::setBg(Vector<Sprite*> &bgs, float pOffsetX, float pOffsetY)
{
	bgSprites = bgs;
	
	initParameter(pOffsetX, pOffsetY);
	
	if (pOffsetX < 0)
	{
		direction |= BG_MOVE_LEFT;
	}
	else if (pOffsetX > 0)
	{
		direction |= BG_MOVE_RIGHT;
	}
	
	if (pOffsetY < 0)
	{
		direction |= BG_MOVE_DOWN;
	}
	else if (pOffsetY > 0)
	{
		direction |= BG_MOVE_UP;
	}
	
	float tmpOffset = 0, bg = 0;
	for (int i = 0; i < bgSprites.size(); i++) {
		Point p = getOffsetPoint(tmpOffset);

		Sprite *it = bgSprites.at(i);
		this->addBgChild(it, p);
		
		tmpOffset += getNewOffset(it);
				
		bg = tmpOffset;
	}
	
	int origSpriteCount = bgSprites.size();
	float maxSize;
	if ((direction == BG_MOVE_DOWN) || (direction == BG_MOVE_UP))
	{
		maxSize = visibleSize.height * 3;
	}
	else
	{
		maxSize = visibleSize.width * 3;
	}
	
	while (bg < maxSize)
	{
		for (int i = 0; i < origSpriteCount; i++) {
			Point p = getOffsetPoint(tmpOffset);
			
			Sprite *it = Sprite::createWithSpriteFrame(bgSprites.at(i)->getSpriteFrame());
			this->addBgChild(it, p);
			bgSprites.pushBack(it);
			
			tmpOffset += getNewOffset(it);
						
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

void ScrollBg::initParameter(float _offsetX, float _offsetY)
{
	this->offsetX = _offsetX;
	this->offsetY = _offsetY;
	
	absOffsetX = (offsetX < 0) ? -offsetX : offsetX;
	absOffsetY = (offsetY < 0) ? -offsetY : offsetY;
		
	scrollOffsetX = 0;
	scrollOffsetY = 0;
	
	isSwapingSprite = false;
	
	direction = 0;
}

Point ScrollBg::getOffsetPoint(float offset)
{
	if ((direction == BG_MOVE_DOWN) || (direction == BG_MOVE_UP))
	{
		return Point(0, offset);
	}
	else
	{
		return Point(offset, 0);
	}
}

float ScrollBg::getNewOffset(cocos2d::Sprite *sprite)
{
	if ((direction == BG_MOVE_DOWN) || (direction == BG_MOVE_UP))
	{
		return sprite->getContentSize().height;
	}
	else
	{
		return sprite->getContentSize().width;
	}
}

void ScrollBg::scroll()
{
	if ((offsetX != 0) || (offsetY != 0))
	{
		schedule(schedule_selector(ScrollBg::updateBg));
	}
}

void ScrollBg::scroll(float dt)
{
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
//	for (int i = 0; i < size; i++) {
//		Sprite* it = bgSprites.at(i);
//		Point n = it->getPosition();
//		n.x += offsetX;
//		n.y += offsetY;
//		
//		it->setPosition(n);
//	}
	
	Point n = this->getPosition();
	n.x += offsetX;
	n.y += offsetY;
	this->setPosition(n);
	
	scrollOffsetX += absOffsetX;
	scrollOffsetY += absOffsetY;
	
	if (offsetX != 0)
	{
//		if (bgSprites.at(0)->getPositionX() + bgSprites.at(0)->getContentSize().width <= 0)
		if (scrollOffsetX >= bgSprites.at(0)->getContentSize().width)
		{
			isSwapingSprite = true;

			scrollOffsetX = scrollOffsetX - bgSprites.at(0)->getContentSize().width;
			
			bgSprites.at(0)->setPositionX(bgSprites.at(size-1)->getPositionX() + bgSprites.at(size-1)->getContentSize().width);
			bgSprites.pushBack(bgSprites.at(0));
			bgSprites.erase(bgSprites.begin());
			isSwapingSprite = false;
		}
	}
	else if (offsetY != 0)
	{
//		if (bgSprites.at(0)->getPositionY() + bgSprites.at(0)->getContentSize().height <= 0)
		if (scrollOffsetY >= bgSprites.at(0)->getContentSize().height)
		{
			isSwapingSprite = true;

			scrollOffsetY = scrollOffsetY - bgSprites.at(0)->getContentSize().height;
			
			bgSprites.at(0)->setPositionY(bgSprites.at(size-1)->getPositionY() + bgSprites.at(size-1)->getContentSize().height);
			bgSprites.pushBack(bgSprites.at(0));
			bgSprites.erase(bgSprites.begin());
			isSwapingSprite = false;
		}
	}
}
