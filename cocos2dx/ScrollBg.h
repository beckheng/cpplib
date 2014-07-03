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

enum BG_DIRECTION{BG_VERTICAL, BG_HORIZONTAL};

/*
 example:
 Vector<Sprite*> bgs;
 bgs.pushBack(bgSprite);
 ScrollBg *scrollBg = ScrollBg::create(); // 初始化
 scrollBg->addBg(bgs, BG_HORIZONTAL); // 添加背景
 scrollBg->setPosition(0, 290); // 设置位置
 this->addChild(scrollBg); // 显示背景
 scrollBg->scroll(-3, 0); // 向左滚动
 */

class ScrollBg : public cocos2d::Node
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ScrollBg);
	
	// 添加背景，纵向/横向
	void addBg(Vector<Sprite*> &bgs, BG_DIRECTION direction);
	
	// 以指定的速度开始滚动，可以指定回调间隔，不执行此调用，则背景是静止的
	void scroll(float offsetX, float offsetY);
	void scroll(float offsetX, float offsetY, float dt);
	
private:
	void addBgChild(Sprite* it, Point pos);
	
	void updateBg(float dt);
	
	Size visibleSize;
	
	float offsetX, offsetY;
	
	bool isSwapingSprite;
	
	Vector<Sprite*> bgSprites;
};

#endif /* defined(__yaoheng__ScrollBg__) */
