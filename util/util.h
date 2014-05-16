//
//  util.h
//
//  Created by beckheng on 14-4-24.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#ifndef __FlyingTigerServer__util__
#define __FlyingTigerServer__util__

#include <iostream>
#include <vector>

double getMilliSecond(); // 取毫秒
double getMicroSecond(); // 取微秒

// 字符串替换
void stringReplace(std::string &s, const std::string &search, const std::string &replace);

// 字符串分割
std::vector<std::string> split(const std::string &s, const std::string &sep);

// 格式化日期显示，以当前时间格式化
std::string formatDateTime(const char*format);

// 格式化日期显示，指定时间格式化
std::string formatDateTime(const struct tm *t, const char *format);

#endif
