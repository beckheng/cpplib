//
//  ScrollBg.h
//
//  Created by beckheng on 14-7-3.
//
//

#ifndef __yaoheng__ScrollBg__
#define __yaoheng__ScrollBg__

#include "cocos2d.h"

USING_NS_CC;

// Current support move left & move down

/*
 example:
 Vector<Sprite*> bgs;
 bgs.pushBack(bgSprite);
 ScrollBg *scrollBg = ScrollBg::create(); // 初始化
 scrollBg->setBg(bgs, -30, 0); // 添加背景, 指定每帧滚动距离基数
 scrollBg->setPosition(0, 290); // 设置位置
 this->addChild(scrollBg); // 显示背景
 scrollBg->scroll(); // 滚动,默认帧率
 or
 scrollBg->scroll(1); // 滚动,指定间隔
 */

class ScrollBg : public cocos2d::Node
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ScrollBg);
	
	// 添加背景，指定每帧滚动距离基数
	void setBg(Vector<Sprite*> &bgs, float pOffsetX, float pOffsetY);
	
	// 以指定的速度开始滚动，可以指定回调间隔，不执行此调用，则背景是静止的
	void scroll();
	void scroll(float dt);
	
private:
	void addBgChild(Sprite* it, Point pos);
	
	void updateBg(float dt);
	
	void initParameter(float _offsetX, float _offsetY);
	Point getOffsetPoint(float offset);
	float getNewOffset(Sprite *sprite);
	
	Size visibleSize;
	
	float offsetX, offsetY, absOffsetX, absOffsetY;
	int direction;
	
	float scrollOffsetX, scrollOffsetY;
	
	bool isSwapingSprite;
	
	Vector<Sprite*> bgSprites;
};

#endif /* defined(__yaoheng__ScrollBg__) */
