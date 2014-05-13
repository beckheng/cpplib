//
//  util.cpp
//  FlyingTigerServer
//
//  Created by beckheng on 14-4-24.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#include "util.h"

#include <stdio.h>
#include <sys/time.h>
#include <locale>
#include <sstream>

long getMilliSecond()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void stringReplace(std::string &s, const std::string &search, const std::string &replace)
{
	const size_t psize = search.size();
	const size_t nsize = replace.size();
	
	for (size_t pos = s.find(search, 0); pos != std::string::npos; pos = s.find(search, pos+nsize)) {
		s.replace(pos, psize, replace);
	}
}

std::vector<std::string> split(const std::string &s, const std::string &sep)
{
	using namespace std;
	
	vector<string> v;
	
	string::size_type i = 0;
	string::size_type j = s.find(sep, i);
	
	long sepLen = sep.size();
	
	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		
		i = j + sepLen;
		j = s.find(sep, i);
	}
	
	if (j == string::npos)
	{
		v.push_back(s.substr(i, s.size()));
	}
	
	return v;
}

std::string formatDateTime(const char*format)
{
	time_t now = time(NULL);
	tm* t = localtime(&now);
	
	return formatDateTime(t, format);
}

std::string formatDateTime(const struct tm *t, const char *format)
{
	char buffer[80];
	
	strftime(buffer, 80-1, format, t);
	
	std::string s = buffer;
	
	return s;
}
