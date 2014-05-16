//
//  util.h
//  FlyingTigerServer
//
//  Created by beckheng on 14-4-24.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#ifndef __FlyingTigerServer__util__
#define __FlyingTigerServer__util__

#include <iostream>
#include <vector>

double getMilliSecond();
double getMicroSecond();

void stringReplace(std::string &s, const std::string &search, const std::string &replace);
std::vector<std::string> split(const std::string &s, const std::string &sep);

std::string formatDateTime(const char*format);
std::string formatDateTime(const struct tm *t, const char *format);

#endif /* defined(__FlyingTigerServer__util__) */
